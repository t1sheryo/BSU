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

public class SubscriberDAO {
    private static final Logger logger = LoggerFactory.getLogger(SubscriberDAO.class);

    private static final String SELECT_SERVICES_BY_SUBSCRIBER =
            "SELECT s.id, s.name, s.monthly_fee FROM services s " +
                    "JOIN subscriber_services ss ON s.id = ss.service_id " +
                    "WHERE ss.subscriber_id = ?";

    private static final String BLOCK_SUBSCRIBER =
            "UPDATE subscribers SET is_blocked = TRUE WHERE id = ?";

    private final ConnectionPool connectionPool;

    public SubscriberDAO() {
        this.connectionPool = ConnectionPool.getInstance();
        logger.debug("SubscriberDAO initialized");
    }

    public List<Service> getServicesBySubscriber(int subscriberId) {
        logger.debug("Getting services for subscriber ID: {}", subscriberId);
        List<Service> services = new ArrayList<>();
        Connection conn = null;

        try {
            conn = connectionPool.getConnection();
            PreparedStatement ps = conn.prepareStatement(SELECT_SERVICES_BY_SUBSCRIBER);
            ps.setInt(1, subscriberId);
            ResultSet rs = ps.executeQuery();

            while (rs.next()) {
                Service service = new Service(
                        rs.getInt("id"),
                        rs.getString("name"),
                        rs.getDouble("monthly_fee")
                );
                services.add(service);
            }

            logger.info("Retrieved {} services for subscriber ID: {}", services.size(), subscriberId);
            return services;

        } catch (Exception e) {
            logger.error("Failed to get services for subscriber ID: {}", subscriberId, e);
            throw new RuntimeException("Database error while retrieving subscriber services", e);
        } finally {
            if (conn != null) {
                connectionPool.returnConnection(conn);
            }
        }
    }

    public boolean blockSubscriber(int subscriberId) {
        logger.debug("Blocking subscriber ID: {}", subscriberId);
        Connection conn = null;

        try {
            conn = connectionPool.getConnection();
            PreparedStatement ps = conn.prepareStatement(BLOCK_SUBSCRIBER);
            ps.setInt(1, subscriberId);

            int rowsAffected = ps.executeUpdate();
            boolean success = rowsAffected > 0;

            if (success) {
                logger.info("Successfully blocked subscriber ID: {}", subscriberId);
            } else {
                logger.warn("Subscriber not found with ID: {}", subscriberId);
            }

            return success;

        } catch (Exception e) {
            logger.error("Failed to block subscriber ID: {}", subscriberId, e);
            throw new RuntimeException("Database error while blocking subscriber", e);
        } finally {
            if (conn != null) {
                connectionPool.returnConnection(conn);
            }
        }
    }
}