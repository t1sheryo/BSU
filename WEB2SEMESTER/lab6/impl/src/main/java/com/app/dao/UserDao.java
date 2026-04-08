package com.app.dao;

import com.app.model.User;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class UserDao {
    private static final Logger logger = LoggerFactory.getLogger(UserDao.class);
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

            // Create users table
            String createTable = """
                CREATE TABLE IF NOT EXISTS users (
                    id BIGINT AUTO_INCREMENT PRIMARY KEY,
                    username VARCHAR(255) NOT NULL UNIQUE,
                    password VARCHAR(255) NOT NULL,
                    email VARCHAR(255) NOT NULL,
                    role VARCHAR(50) DEFAULT 'USER'
                )
            """;
            stmt.execute(createTable);

            // Insert default administrator
            String checkAdmin = "SELECT COUNT(*) FROM users WHERE username = 'admin'";
            try (ResultSet rs = stmt.executeQuery(checkAdmin)) {
                if (rs.next() && rs.getInt(1) == 0) {
                    String insertAdmin = """
                        INSERT INTO users (username, password, email, role) VALUES
                        ('admin', 'admin123456', 'admin@phonestation.by', 'ADMIN')
                    """;
                    stmt.execute(insertAdmin);
                    logger.info("Default administrator created");
                }
            }
            logger.info("Users database initialized");
        } catch (SQLException e) {
            logger.error("Error initializing users database", e);
            throw new RuntimeException("Failed to initialize users database", e);
        }
    }

    private static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
    }

    public User findByUsername(String username) {
        String sql = "SELECT * FROM users WHERE username = ?";

        try (Connection conn = getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    logger.debug("User found: {}", username);
                    return mapRowToUser(rs);
                }
            }
        } catch (SQLException e) {
            logger.error("Error searching for user: {}", username, e);
            throw new RuntimeException("Failed to find user", e);
        }
        return null;
    }

    public User findById(Long id) {
        String sql = "SELECT * FROM users WHERE id = ?";

        try (Connection conn = getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setLong(1, id);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return mapRowToUser(rs);
                }
            }
        } catch (SQLException e) {
            logger.error("Error searching for user by id: {}", id, e);
            throw new RuntimeException("Failed to find user", e);
        }
        return null;
    }

    public List<User> findAll() {
        List<User> users = new ArrayList<>();
        String sql = "SELECT * FROM users ORDER BY id";

        try (Connection conn = getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {

            while (rs.next()) {
                users.add(mapRowToUser(rs));
            }
            logger.debug("Users found: {}", users.size());
        } catch (SQLException e) {
            logger.error("Error getting user list", e);
            throw new RuntimeException("Failed to get user list", e);
        }
        return users;
    }

    public void save(User user) {
        String sql = "INSERT INTO users (username, password, email, role) VALUES (?, ?, ?, ?)";

        try (Connection conn = getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, user.getUsername());
            pstmt.setString(2, user.getPassword());
            pstmt.setString(3, user.getEmail());
            pstmt.setString(4, user.getRole().name());
            pstmt.executeUpdate();
            logger.info("User saved: {}", user.getUsername());
        } catch (SQLException e) {
            logger.error("Error saving user", e);
            throw new RuntimeException("Failed to save user", e);
        }
    }

    public void update(User user) {
        String sql = "UPDATE users SET username = ?, password = ?, email = ?, role = ? WHERE id = ?";

        try (Connection conn = getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, user.getUsername());
            pstmt.setString(2, user.getPassword());
            pstmt.setString(3, user.getEmail());
            pstmt.setString(4, user.getRole().name());
            pstmt.setLong(5, user.getId());
            pstmt.executeUpdate();
            logger.info("User updated: id={}", user.getId());
        } catch (SQLException e) {
            logger.error("Error updating user", e);
            throw new RuntimeException("Failed to update user", e);
        }
    }

    public void delete(Long id) {
        String sql = "DELETE FROM users WHERE id = ?";

        try (Connection conn = getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setLong(1, id);
            pstmt.executeUpdate();
            logger.info("User deleted: id={}", id);
        } catch (SQLException e) {
            logger.error("Error deleting user", e);
            throw new RuntimeException("Failed to delete user", e);
        }
    }

    private User mapRowToUser(ResultSet rs) throws SQLException {
        User user = new User();
        user.setId(rs.getLong("id"));
        user.setUsername(rs.getString("username"));
        user.setPassword(rs.getString("password"));
        user.setEmail(rs.getString("email"));
        try {
            user.setRole(User.Role.valueOf(rs.getString("role")));
        } catch (IllegalArgumentException e) {
            user.setRole(User.Role.USER);
        }
        return user;
    }
}