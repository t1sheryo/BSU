package com.app.controller;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.WebContext;
import org.thymeleaf.web.servlet.JakartaServletWebApplication;

import java.io.IOException;

public class ErrorController {
    private static final Logger logger = LoggerFactory.getLogger(ErrorController.class);
    private final TemplateEngine templateEngine;

    public ErrorController(TemplateEngine templateEngine) {
        this.templateEngine = templateEngine;
    }

    public void handleError(HttpServletRequest request, HttpServletResponse response, Exception exception) throws IOException {
        logger.error("Обработка ошибки", exception);
        response.setContentType("text/html; charset=UTF-8");
        response.setCharacterEncoding("UTF-8");
        
        WebContext context = new WebContext(
            JakartaServletWebApplication.buildApplication(request.getServletContext())
                .buildExchange(request, response)
        );
        
        String errorMessage = "Произошла ошибка при обработке запроса";
        if (exception != null) {
            errorMessage = exception.getMessage();
            if (errorMessage == null || errorMessage.isEmpty()) {
                errorMessage = exception.getClass().getSimpleName();
            }
        }
        
        Integer statusCode = (Integer) request.getAttribute("jakarta.servlet.error.status_code");
        if (statusCode == null) {
            statusCode = HttpServletResponse.SC_INTERNAL_SERVER_ERROR;
        }
        
        context.setVariable("errorMessage", errorMessage);
        context.setVariable("statusCode", statusCode);
        context.setVariable("exception", exception);
        
        response.setStatus(statusCode);
        templateEngine.process("error", context, response.getWriter());
    }
}

