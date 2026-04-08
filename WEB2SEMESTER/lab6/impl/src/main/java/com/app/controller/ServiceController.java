package com.app.controller;

import com.app.dao.ServiceDao;
import com.app.model.Service;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.thymeleaf.TemplateEngine;
import org.thymeleaf.context.WebContext;
import org.thymeleaf.web.servlet.JakartaServletWebApplication;

import java.io.IOException;
import java.util.List;

public class ServiceController {
    private static final Logger logger = LoggerFactory.getLogger(ServiceController.class);
    private final ServiceDao serviceDao;
    private final TemplateEngine templateEngine;

    public ServiceController(ServiceDao serviceDao, TemplateEngine templateEngine) {
        this.serviceDao = serviceDao;
        this.templateEngine = templateEngine;
    }

    public void handleList(HttpServletRequest request, HttpServletResponse response) throws IOException {
        logger.debug("Processing services list request");
        response.setContentType("text/html; charset=UTF-8");
        response.setCharacterEncoding("UTF-8");

        List<Service> services = serviceDao.findAll();

        WebContext context = new WebContext(
                JakartaServletWebApplication.buildApplication(request.getServletContext())
                        .buildExchange(request, response)
        );
        context.setVariable("services", services);

        templateEngine.process("services/list", context, response.getWriter());
    }

    public void handleAvailable(HttpServletRequest request, HttpServletResponse response) throws IOException {
        logger.debug("Processing available services request");
        response.setContentType("text/html; charset=UTF-8");
        response.setCharacterEncoding("UTF-8");

        List<Service> services = serviceDao.findAvailable();

        WebContext context = new WebContext(
                JakartaServletWebApplication.buildApplication(request.getServletContext())
                        .buildExchange(request, response)
        );
        context.setVariable("services", services);

        templateEngine.process("services/available", context, response.getWriter());
    }

    public void handleShow(HttpServletRequest request, HttpServletResponse response, Long id) throws IOException {
        logger.debug("Processing service request with id: {}", id);
        response.setContentType("text/html; charset=UTF-8");
        response.setCharacterEncoding("UTF-8");

        Service service = serviceDao.findById(id);

        if (service == null) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
            return;
        }

        WebContext context = new WebContext(
                JakartaServletWebApplication.buildApplication(request.getServletContext())
                        .buildExchange(request, response)
        );
        context.setVariable("service", service);

        templateEngine.process("services/show", context, response.getWriter());
    }

    public void handleCreateForm(HttpServletRequest request, HttpServletResponse response) throws IOException {
        logger.debug("Processing service creation form request");
        response.setContentType("text/html; charset=UTF-8");
        response.setCharacterEncoding("UTF-8");

        WebContext context = new WebContext(
                JakartaServletWebApplication.buildApplication(request.getServletContext())
                        .buildExchange(request, response)
        );

        templateEngine.process("services/create", context, response.getWriter());
    }

    public void handleCreate(HttpServletRequest request, HttpServletResponse response) throws IOException {
        logger.debug("Processing service creation");
        request.setCharacterEncoding("UTF-8");

        Service service = new Service();
        service.setName(request.getParameter("name"));
        service.setDescription(request.getParameter("description"));

        try {
            service.setPrice(Double.parseDouble(request.getParameter("price")));
        } catch (NumberFormatException e) {
            logger.warn("Invalid price format: {}", request.getParameter("price"));
            service.setPrice(0.0);
        }

        service.setAvailable(request.getParameter("available") != null);

        serviceDao.save(service);
        response.sendRedirect(request.getContextPath() + "/services");
    }
}