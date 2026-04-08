package com.app.servlet;

import com.app.controller.*;
import com.app.dao.ServiceDao;
import com.app.dao.UserDao;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.thymeleaf.TemplateEngine;
import org.thymeleaf.templatemode.TemplateMode;
import org.thymeleaf.templateresolver.WebApplicationTemplateResolver;
import org.thymeleaf.web.servlet.JakartaServletWebApplication;

import java.io.IOException;

public class AppDispatcherServlet extends HttpServlet {
    private static final Logger logger = LoggerFactory.getLogger(AppDispatcherServlet.class);

    private TemplateEngine templateEngine;
    private ServiceDao serviceDao;
    private UserDao userDao;
    private HomeController homeController;
    private ServiceController serviceController;
    private AuthController authController;
    private ErrorController errorController;

    @Override
    public void init() throws ServletException {
        super.init();
        logger.info("Initializing AppDispatcherServlet");

        try {
            // Thymeleaf initialization
            JakartaServletWebApplication application = JakartaServletWebApplication.buildApplication(getServletContext());
            WebApplicationTemplateResolver templateResolver = new WebApplicationTemplateResolver(application);
            templateResolver.setTemplateMode(TemplateMode.HTML);
            templateResolver.setPrefix("/WEB-INF/templates/");
            templateResolver.setSuffix(".html");
            templateResolver.setCharacterEncoding("UTF-8");
            templateResolver.setCacheable(false);

            templateEngine = new TemplateEngine();
            templateEngine.setTemplateResolver(templateResolver);

            // DAO initialization
            serviceDao = new ServiceDao();
            userDao = new UserDao();

            // Controller initialization
            homeController = new HomeController(templateEngine);
            serviceController = new ServiceController(serviceDao, templateEngine);
            authController = new AuthController(userDao, templateEngine);
            errorController = new ErrorController(templateEngine);

            logger.info("AppDispatcherServlet initialized successfully");
        } catch (Exception e) {
            logger.error("Error initializing AppDispatcherServlet", e);
            throw new ServletException("Failed to initialize servlet", e);
        }
    }

    @Override
    protected void service(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        try {
            // Set UTF-8 encoding for all requests
            request.setCharacterEncoding("UTF-8");
            response.setContentType("text/html; charset=UTF-8");
            response.setCharacterEncoding("UTF-8");

            // Request routing
            String path = request.getRequestURI().substring(request.getContextPath().length());
            logger.debug("Processing request: {}", path);

            if (path.equals("/home") || path.equals("/")) {
                homeController.handleHome(request, response);
            } else if (path.equals("/login")) {
                if ("POST".equals(request.getMethod())) {
                    authController.handleLogin(request, response);
                } else {
                    authController.handleLoginForm(request, response);
                }
            } else if (path.equals("/register")) {
                if ("POST".equals(request.getMethod())) {
                    authController.handleRegister(request, response);
                } else {
                    authController.handleRegisterForm(request, response);
                }
            } else if (path.equals("/logout")) {
                authController.handleLogout(request, response);
            } else if (path.equals("/services")) {
                serviceController.handleList(request, response);
            } else if (path.equals("/services/available")) {
                serviceController.handleAvailable(request, response);
            } else if (path.startsWith("/services/create")) {
                if ("POST".equals(request.getMethod())) {
                    serviceController.handleCreate(request, response);
                } else {
                    serviceController.handleCreateForm(request, response);
                }
            } else if (path.startsWith("/services/") && path.matches("/services/\\d+")) {
                Long id = Long.parseLong(path.substring("/services/".length()));
                serviceController.handleShow(request, response, id);
            } else if (path.equals("/error")) {
                Exception exception = (Exception) request.getAttribute("jakarta.servlet.error.exception");
                errorController.handleError(request, response, exception);
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
            }
        } catch (Exception e) {
            logger.error("Critical error processing request", e);
            request.setAttribute("jakarta.servlet.error.exception", e);
            request.setAttribute("jakarta.servlet.error.status_code", HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            errorController.handleError(request, response, e);
        }
    }
}