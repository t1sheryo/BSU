package com.app.controller;

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
import java.util.Date;

public class HomeController {
    private static final Logger logger = LoggerFactory.getLogger(HomeController.class);
    private final TemplateEngine templateEngine;

    public HomeController(TemplateEngine templateEngine) {
        this.templateEngine = templateEngine;
    }

    public void handleHome(HttpServletRequest request, HttpServletResponse response) throws IOException {
        logger.debug("Processing homepage request");
        response.setContentType("text/html; charset=UTF-8");
        response.setCharacterEncoding("UTF-8");

        WebContext context = new WebContext(
                JakartaServletWebApplication.buildApplication(request.getServletContext())
                        .buildExchange(request, response)
        );

        // FIXED: Get user from session correctly
        User user = null;
        HttpSession session = request.getSession(false);
        if (session != null) {
            Object userObj = session.getAttribute("user");
            if (userObj instanceof User) {
                user = (User) userObj;
            }
        }

        if (user == null) {
            user = new User();
            user.setRole(User.Role.GUEST);
        }

        context.setVariable("user", user);

        // Processing messages
        String success = request.getParameter("success");
        String error = request.getParameter("error");

        if (success != null) {
            context.setVariable("successMessage", getSuccessMessage(success));
        }

        if (error != null) {
            context.setVariable("errorMessage", getErrorMessage(error));
        }

        // Session statistics
        var newSession = request.getSession(true);
        Integer visitCount = (Integer) newSession.getAttribute("visitCount");
        if (visitCount == null) {
            visitCount = 1;
        } else {
            visitCount++;
        }
        newSession.setAttribute("visitCount", visitCount);
        newSession.setAttribute("lastVisit", new Date());
        context.setVariable("visitCount", visitCount);
        context.setVariable("lastVisit", newSession.getAttribute("lastVisit"));

        templateEngine.process("home", context, response.getWriter());
    }

    private String getSuccessMessage(String successCode) {
        return switch (successCode) {
            case "login" -> "You have successfully logged in!";
            case "register" -> "Registration completed successfully!";
            case "logout" -> "You have logged out";
            default -> "";
        };
    }

    private String getErrorMessage(String errorCode) {
        return switch (errorCode) {
            case "access_denied" -> "Access denied. Insufficient permissions to perform the operation.";
            case "login_required" -> "You need to log in to access this section";
            default -> "";
        };
    }
}