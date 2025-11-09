package org.example.dao;

import org.example.dbConnection.ConnectionPool;
import org.example.model.Service;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class ServiceDAO {
    private static final Logger logger = LoggerFactory.getLogger(ServiceDAO.class);

    private static final String SELECT_ALL_SERVICES =
            "SELECT id, name, monthly_fee FROM services";

    private final ConnectionPool connectionPool;

    public ServiceDAO() {
        this.connectionPool = ConnectionPool.getInstance();
        logger.debug("ServiceDAO initialized");
    }

    public List<Service> getAllServices() {
        logger.debug("Getting all services");
        List<Service> services = new ArrayList<>();
        Connection conn = null;

        try {
            conn = connectionPool.getConnection();
            PreparedStatement ps = conn.prepareStatement(SELECT_ALL_SERVICES);
            ResultSet rs = ps.executeQuery();

            while (rs.next()) {
                Service service = new Service(
                        rs.getInt("id"),
                        rs.getString("name"),
                        rs.getDouble("monthly_fee")
                );
                services.add(service);
            }

            logger.info("Retrieved {} services", services.size());
            return services;

        } catch (Exception e) {
            logger.error("Failed to get all services", e);
            throw new RuntimeException("Database error while retrieving services", e);
        } finally {
            if (conn != null) {
                connectionPool.returnConnection(conn);
            }
        }
    }
}