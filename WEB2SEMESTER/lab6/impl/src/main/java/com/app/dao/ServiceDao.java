package com.app.dao;

import com.app.model.Service;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ServiceDao {
    private static final Logger logger = LoggerFactory.getLogger(ServiceDao.class);
    private static final String DB_URL = "jdbc:h2:mem:testdb;DB_CLOSE_DELAY=-1;MODE=MySQL";
    private static final String DB_USER = "sa";
    private static final String DB_PASSWORD = "";

    static {
        try {
            Class.forName("org.h2.Driver");
            initializeDatabase();
        } catch (ClassNotFoundException e) {
            logger.error("Database driver loading error", e);
            throw new RuntimeException("Failed to load database driver", e);
        }
    }

    private static void initializeDatabase() {
        try (Connection conn = getConnection();
             Statement stmt = conn.createStatement()) {

            // Create table
            String createTable = """
                CREATE TABLE IF NOT EXISTS services (
                    id BIGINT AUTO_INCREMENT PRIMARY KEY,
                    name VARCHAR(255) NOT NULL,
                    description TEXT,
                    price DECIMAL(10, 2),
                    available BOOLEAN DEFAULT TRUE
                )
            """;
            stmt.execute(createTable);

            // Insert test data
            String insertData = """
                INSERT INTO services (name, description, price, available) VALUES
                ('Outgoing calls', 'Ability to make outgoing calls', 10.50, TRUE),
                ('Incoming calls', 'Receiving incoming calls', 5.00, TRUE),
                ('SMS', 'Sending and receiving SMS messages', 3.00, TRUE),
                ('Internet', 'Internet access', 15.00, TRUE),
                ('Roaming', 'Calls while roaming', 25.00, FALSE)
            """;
            stmt.execute(insertData);
            logger.info("Database initialized");
        } catch (SQLException e) {
            logger.error("Error initializing database", e);
            throw new RuntimeException("Failed to initialize database", e);
        }
    }

    private static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
    }

    public List<Service> findAll() {
        List<Service> services = new ArrayList<>();
        String sql = "SELECT * FROM services ORDER BY id";

        try (Connection conn = getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {

            while (rs.next()) {
                services.add(mapRowToService(rs));
            }
            logger.debug("Services found: {}", services.size());
        } catch (SQLException e) {
            logger.error("Error getting service list", e);
            throw new RuntimeException("Failed to get service list", e);
        }
        return services;
    }

    public Service findById(Long id) {
        String sql = "SELECT * FROM services WHERE id = ?";

        try (Connection conn = getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setLong(1, id);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    logger.debug("Service found with id: {}", id);
                    return mapRowToService(rs);
                }
            }
        } catch (SQLException e) {
            logger.error("Error searching for service by id: {}", id, e);
            throw new RuntimeException("Failed to find service", e);
        }
        return null;
    }

    public List<Service> findAvailable() {
        List<Service> services = new ArrayList<>();
        String sql = "SELECT * FROM services WHERE available = TRUE ORDER BY id";

        try (Connection conn = getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {

            while (rs.next()) {
                services.add(mapRowToService(rs));
            }
            logger.debug("Available services found: {}", services.size());
        } catch (SQLException e) {
            logger.error("Error getting available services", e);
            throw new RuntimeException("Failed to get available services list", e);
        }
        return services;
    }

    public void save(Service service) {
        String sql = "INSERT INTO services (name, description, price, available) VALUES (?, ?, ?, ?)";

        try (Connection conn = getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, service.getName());
            pstmt.setString(2, service.getDescription());
            pstmt.setDouble(3, service.getPrice());
            pstmt.setBoolean(4, service.getAvailable());
            pstmt.executeUpdate();
            logger.info("Service saved: {}", service.getName());
        } catch (SQLException e) {
            logger.error("Error saving service", e);
            throw new RuntimeException("Failed to save service", e);
        }
    }

    public void update(Service service) {
        String sql = "UPDATE services SET name = ?, description = ?, price = ?, available = ? WHERE id = ?";

        try (Connection conn = getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, service.getName());
            pstmt.setString(2, service.getDescription());
            pstmt.setDouble(3, service.getPrice());
            pstmt.setBoolean(4, service.getAvailable());
            pstmt.setLong(5, service.getId());
            pstmt.executeUpdate();
            logger.info("Service updated: id={}", service.getId());
        } catch (SQLException e) {
            logger.error("Error updating service", e);
            throw new RuntimeException("Failed to update service", e);
        }
    }

    public void delete(Long id) {
        String sql = "DELETE FROM services WHERE id = ?";

        try (Connection conn = getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setLong(1, id);
            pstmt.executeUpdate();
            logger.info("Service deleted: id={}", id);
        } catch (SQLException e) {
            logger.error("Error deleting service", e);
            throw new RuntimeException("Failed to delete service", e);
        }
    }

    private Service mapRowToService(ResultSet rs) throws SQLException {
        Service service = new Service();
        service.setId(rs.getLong("id"));
        service.setName(rs.getString("name"));
        service.setDescription(rs.getString("description"));
        service.setPrice(rs.getDouble("price"));
        service.setAvailable(rs.getBoolean("available"));
        return service;
    }
}