package com.app.servlet;

import com.app.controller.ErrorController;
import com.app.controller.IndexController;
import com.app.controller.ServiceController;
import com.app.dao.ServiceDao;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.Cookie;
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
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class DispatcherServlet extends HttpServlet {
    private static final Logger logger = LoggerFactory.getLogger(DispatcherServlet.class);
    
    private TemplateEngine templateEngine;
    private ServiceDao serviceDao;
    private IndexController indexController;
    private ServiceController serviceController;
    private ErrorController errorController;

    @Override
    public void init() throws ServletException {
        super.init();
        logger.info("Инициализация DispatcherServlet");
        
        try {
            // Инициализация Thymeleaf
            JakartaServletWebApplication application = JakartaServletWebApplication.buildApplication(getServletContext());
            WebApplicationTemplateResolver templateResolver = new WebApplicationTemplateResolver(application);
            templateResolver.setTemplateMode(TemplateMode.HTML);
            templateResolver.setPrefix("/WEB-INF/templates/");
            templateResolver.setSuffix(".html");
            templateResolver.setCharacterEncoding("UTF-8");
            templateResolver.setCacheable(false);
            
            templateEngine = new TemplateEngine();
            templateEngine.setTemplateResolver(templateResolver);
            
            // Инициализация DAO
            serviceDao = new ServiceDao();
            
            // Инициализация контроллеров
            indexController = new IndexController(templateEngine);
            serviceController = new ServiceController(serviceDao, templateEngine);
            errorController = new ErrorController(templateEngine);
            
            logger.info("DispatcherServlet успешно инициализирован");
        } catch (Exception e) {
            logger.error("Ошибка инициализации DispatcherServlet", e);
            throw new ServletException("Не удалось инициализировать сервлет", e);
        }
    }

    @Override
    protected void service(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        try {
            // Установка кодировки UTF-8 для всех запросов
            request.setCharacterEncoding("UTF-8");
            response.setContentType("text/html; charset=UTF-8");
            response.setCharacterEncoding("UTF-8");
            
            // Обработка сессии и cookies
            handleSessionAndCookies(request, response);
            
            // Маршрутизация запросов
            String path = request.getRequestURI().substring(request.getContextPath().length());
            logger.debug("Обработка запроса: {}", path);
            
            if (path.equals("/") || path.equals("/index")) {
                indexController.handleIndex(request, response);
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
            logger.error("Критическая ошибка при обработке запроса", e);
            request.setAttribute("jakarta.servlet.error.exception", e);
            request.setAttribute("jakarta.servlet.error.status_code", HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            errorController.handleError(request, response, e);
        }
    }

    private void handleSessionAndCookies(HttpServletRequest request, HttpServletResponse response) {
        // Работа с сессией
        var session = request.getSession(true);
        Integer visitCount = (Integer) session.getAttribute("visitCount");
        if (visitCount == null) {
            visitCount = 1;
        } else {
            visitCount++;
        }
        session.setAttribute("visitCount", visitCount);
        session.setAttribute("lastVisit", new Date());
        
        // Работа с cookies
        Cookie[] cookies = request.getCookies();
        Cookie lastVisitCookie = null;
        Cookie visitCountCookie = null;
        
        if (cookies != null) {
            for (Cookie cookie : cookies) {
                if ("lastVisit".equals(cookie.getName())) {
                    lastVisitCookie = cookie;
                } else if ("visitCount".equals(cookie.getName())) {
                    visitCountCookie = cookie;
                }
            }
        }
        
        // Обновление или создание cookie для последнего визита
        // Используем формат без пробелов, так как пробелы недопустимы в значениях cookie (RFC6265)
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd_HH:mm:ss", Locale.getDefault());
        String currentTime = sdf.format(new Date());
        
        if (lastVisitCookie == null) {
            lastVisitCookie = new Cookie("lastVisit", currentTime);
        } else {
            lastVisitCookie.setValue(currentTime);
        }
        lastVisitCookie.setMaxAge(60 * 60 * 24 * 30); // 30 дней
        lastVisitCookie.setPath("/");
        response.addCookie(lastVisitCookie);
        
        // Обновление или создание cookie для количества посещений
        int cookieVisitCount = 1;
        if (visitCountCookie != null) {
            try {
                cookieVisitCount = Integer.parseInt(visitCountCookie.getValue()) + 1;
            } catch (NumberFormatException e) {
                logger.warn("Неверный формат cookie visitCount", e);
            }
        }
        
        if (visitCountCookie == null) {
            visitCountCookie = new Cookie("visitCount", String.valueOf(cookieVisitCount));
        } else {
            visitCountCookie.setValue(String.valueOf(cookieVisitCount));
        }
        visitCountCookie.setMaxAge(60 * 60 * 24 * 30); // 30 дней
        visitCountCookie.setPath("/");
        response.addCookie(visitCountCookie);
        
        logger.debug("Сессия: visitCount={}, cookies: lastVisit={}, visitCount={}", 
            visitCount, currentTime, cookieVisitCount);
    }
}

