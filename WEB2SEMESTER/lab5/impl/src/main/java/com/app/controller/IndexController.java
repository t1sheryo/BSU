package com.app.controller;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.WebContext;
import org.thymeleaf.web.servlet.JakartaServletWebApplication;

import java.io.IOException;

public class IndexController {
    private static final Logger logger = LoggerFactory.getLogger(IndexController.class);
    private final TemplateEngine templateEngine;

    public IndexController(TemplateEngine templateEngine) {
        this.templateEngine = templateEngine;
    }

    public void handleIndex(HttpServletRequest request, HttpServletResponse response) throws IOException {
        logger.debug("Обработка запроса главной страницы");
        response.setContentType("text/html; charset=UTF-8");
        response.setCharacterEncoding("UTF-8");
        
        WebContext context = new WebContext(
            JakartaServletWebApplication.buildApplication(request.getServletContext())
                .buildExchange(request, response)
        );
        
        templateEngine.process("index", context, response.getWriter());
    }
}

