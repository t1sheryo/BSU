package com.app.controller;

import com.app.dao.UserDao;
import com.app.model.User;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.WebContext;
import org.thymeleaf.web.servlet.JakartaServletWebApplication;

import java.io.IOException;

public class AuthController {
    private static final Logger logger = LoggerFactory.getLogger(AuthController.class);
    private final UserDao userDao;
    private final TemplateEngine templateEngine;

    public AuthController(UserDao userDao, TemplateEngine templateEngine) {
        this.userDao = userDao;
        this.templateEngine = templateEngine;
    }

    public void handleLoginForm(HttpServletRequest request, HttpServletResponse response) throws IOException {
        logger.debug("Processing login form request");
        response.setContentType("text/html; charset=UTF-8");
        response.setCharacterEncoding("UTF-8");

        WebContext context = new WebContext(
                JakartaServletWebApplication.buildApplication(request.getServletContext())
                        .buildExchange(request, response)
        );

        String error = request.getParameter("error");
        if (error != null) {
            context.setVariable("error", getErrorMessage(error));
        }

        templateEngine.process("auth/login", context, response.getWriter());
    }

    public void handleLogin(HttpServletRequest request, HttpServletResponse response) throws IOException {
        logger.debug("Processing user login");
        request.setCharacterEncoding("UTF-8");

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username == null || password == null ||
                username.trim().isEmpty() || password.trim().isEmpty()) {
            response.sendRedirect(request.getContextPath() + "/login?error=empty_fields");
            return;
        }

        User user = userDao.findByUsername(username);

        if (user != null && user.getPassword().equals(password)) {
            HttpSession session = request.getSession(true);
            session.setAttribute("user", user);
            logger.info("User {} successfully logged in", username);
            response.sendRedirect(request.getContextPath() + "/home?success=login");
        } else {
            logger.warn("Failed login attempt: {}", username);
            response.sendRedirect(request.getContextPath() + "/login?error=invalid_credentials");
        }
    }

    public void handleRegisterForm(HttpServletRequest request, HttpServletResponse response) throws IOException {
        logger.debug("Processing registration form request");
        response.setContentType("text/html; charset=UTF-8");
        response.setCharacterEncoding("UTF-8");

        WebContext context = new WebContext(
                JakartaServletWebApplication.buildApplication(request.getServletContext())
                        .buildExchange(request, response)
        );

        String error = request.getParameter("error");
        if (error != null) {
            context.setVariable("error", getErrorMessage(error));
        }

        templateEngine.process("auth/register", context, response.getWriter());
    }

    public void handleRegister(HttpServletRequest request, HttpServletResponse response) throws IOException {
        logger.debug("Processing user registration");
        request.setCharacterEncoding("UTF-8");

        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String email = request.getParameter("email");

        if (username == null || password == null || email == null ||
                username.trim().isEmpty() || password.trim().isEmpty() || email.trim().isEmpty()) {
            response.sendRedirect(request.getContextPath() + "/register?error=empty_fields");
            return;
        }

        // Check if user exists
        if (userDao.findByUsername(username) != null) {
            logger.warn("Registration attempt with existing username: {}", username);
            response.sendRedirect(request.getContextPath() + "/register?error=username_exists");
            return;
        }

        User user = new User(username, password, email);
        user.setRole(User.Role.USER);
        userDao.save(user);

        HttpSession session = request.getSession(true);
        session.setAttribute("user", user);
        logger.info("User {} successfully registered", username);
        response.sendRedirect(request.getContextPath() + "/home?success=register");
    }

    public void handleLogout(HttpServletRequest request, HttpServletResponse response) throws IOException {
        logger.debug("Processing user logout");
        HttpSession session = request.getSession(false);
        if (session != null) {
            User user = (User) session.getAttribute("user");
            if (user != null) {
                logger.info("User {} logged out", user.getUsername());
            }
            session.invalidate();
        }
        response.sendRedirect(request.getContextPath() + "/home?success=logout");
    }

    private String getErrorMessage(String errorCode) {
        return switch (errorCode) {
            case "empty_fields" -> "Fill in all fields";
            case "invalid_credentials" -> "Invalid username or password";
            case "username_exists" -> "User with this username already exists";
            case "access_denied" -> "Access denied. Insufficient permissions to perform the operation.";
            case "login_required" -> "You need to log in to access this section";
            default -> "An error occurred";
        };
    }
}