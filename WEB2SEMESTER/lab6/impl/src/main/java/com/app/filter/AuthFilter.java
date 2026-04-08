package com.app.filter;

import com.app.model.User;
import jakarta.servlet.*;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.IOException;
import java.util.Arrays;
import java.util.List;

public class AuthFilter implements Filter {
    private static final Logger logger = LoggerFactory.getLogger(AuthFilter.class);

    // Paths accessible without authorization
    private static final List<String> PUBLIC_PATHS = Arrays.asList(
            "/home",
            "/login",
            "/register",
            "/services/available",
            "/css/"
    );

    // Paths accessible only to users and administrators
    private static final List<String> USER_PATHS = Arrays.asList(
            "/services"
    );

    // Paths accessible only to administrators
    private static final List<String> ADMIN_PATHS = Arrays.asList(
            "/services/create",
            "/admin"
    );

    // Static resource extensions
    private static final List<String> STATIC_EXTENSIONS = Arrays.asList(
            ".css", ".js", ".jpg", ".jpeg", ".png", ".gif", ".ico", ".svg", ".woff", ".woff2", ".ttf", ".eot"
    );

    @Override
    public void init(FilterConfig filterConfig) throws ServletException {
        logger.info("Initializing AuthFilter");
    }

    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
            throws IOException, ServletException {

        HttpServletRequest httpRequest = (HttpServletRequest) request;
        HttpServletResponse httpResponse = (HttpServletResponse) response;
        HttpSession session = httpRequest.getSession(false);

        String path = httpRequest.getRequestURI();
        String contextPath = httpRequest.getContextPath();
        String relativePath = path.substring(contextPath.length());

        // Skip static resources
        if (isStaticResource(relativePath)) {
            chain.doFilter(request, response);
            return;
        }

        // FIXED: Get user from session correctly
        User user = null;
        if (session != null) {
            Object userObj = session.getAttribute("user");
            if (userObj instanceof User) {
                user = (User) userObj;
            }
        }

        // If user is not authorized, create a guest
        if (user == null) {
            user = new User();
            user.setRole(User.Role.GUEST);
        }

        // Check access to the path
        if (isPublicPath(relativePath)) {
            chain.doFilter(request, response);
            return;
        }

        if (isAdminPath(relativePath)) {
            if (!user.isAdmin()) {
                logger.warn("Attempt to access admin panel without administrator rights: {}", relativePath);
                httpResponse.sendRedirect(contextPath + "/home?error=access_denied");
                return;
            }
            chain.doFilter(request, response);
            return;
        }

        if (isUserPath(relativePath)) {
            if (!user.isUser()) {
                logger.warn("Attempt to access protected resource without authorization: {}", relativePath);
                httpResponse.sendRedirect(contextPath + "/home?error=login_required");
                return;
            }
            chain.doFilter(request, response);
            return;
        }

        // For root path redirect to home
        if (relativePath.equals("/") || relativePath.isEmpty()) {
            httpResponse.sendRedirect(contextPath + "/home");
            return;
        }

        // By default pass the request
        chain.doFilter(request, response);
    }

    private boolean isStaticResource(String path) {
        if (path == null) {
            return false;
        }
        String lowerPath = path.toLowerCase();
        return STATIC_EXTENSIONS.stream().anyMatch(lowerPath::endsWith);
    }

    private boolean isPublicPath(String path) {
        return PUBLIC_PATHS.stream().anyMatch(path::startsWith);
    }

    private boolean isUserPath(String path) {
        return USER_PATHS.stream().anyMatch(path::startsWith);
    }

    private boolean isAdminPath(String path) {
        return ADMIN_PATHS.stream().anyMatch(path::startsWith);
    }

    @Override
    public void destroy() {
        logger.info("Destroying AuthFilter");
    }
}