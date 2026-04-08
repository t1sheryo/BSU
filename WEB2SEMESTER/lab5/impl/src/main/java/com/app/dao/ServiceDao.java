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
            logger.error("Ошибка загрузки драйвера БД", e);
            throw new RuntimeException("Не удалось загрузить драйвер БД", e);
        }
    }

    private static void initializeDatabase() {
        try (Connection conn = getConnection();
             Statement stmt = conn.createStatement()) {
            
            // Создание таблицы
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

            // Вставка тестовых данных
            String insertData = """
                INSERT INTO services (name, description, price, available) VALUES
                ('Исходящие звонки', 'Возможность совершать исходящие звонки', 10.50, TRUE),
                ('Входящие звонки', 'Прием входящих звонков', 5.00, TRUE),
                ('SMS', 'Отправка и прием SMS сообщений', 3.00, TRUE),
                ('Интернет', 'Доступ в интернет', 15.00, TRUE),
                ('Роуминг', 'Звонки в роуминге', 25.00, FALSE)
            """;
            stmt.execute(insertData);
            logger.info("База данных инициализирована");
        } catch (SQLException e) {
            logger.error("Ошибка инициализации БД", e);
            throw new RuntimeException("Не удалось инициализировать БД", e);
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
            logger.debug("Найдено сервисов: {}", services.size());
        } catch (SQLException e) {
            logger.error("Ошибка при получении списка сервисов", e);
            throw new RuntimeException("Не удалось получить список сервисов", e);
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
                    logger.debug("Найден сервис с id: {}", id);
                    return mapRowToService(rs);
                }
            }
        } catch (SQLException e) {
            logger.error("Ошибка при поиске сервиса по id: {}", id, e);
            throw new RuntimeException("Не удалось найти сервис", e);
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
            logger.debug("Найдено доступных сервисов: {}", services.size());
        } catch (SQLException e) {
            logger.error("Ошибка при получении доступных сервисов", e);
            throw new RuntimeException("Не удалось получить список доступных сервисов", e);
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
            logger.info("Сервис сохранен: {}", service.getName());
        } catch (SQLException e) {
            logger.error("Ошибка при сохранении сервиса", e);
            throw new RuntimeException("Не удалось сохранить сервис", e);
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
            logger.info("Сервис обновлен: id={}", service.getId());
        } catch (SQLException e) {
            logger.error("Ошибка при обновлении сервиса", e);
            throw new RuntimeException("Не удалось обновить сервис", e);
        }
    }

    public void delete(Long id) {
        String sql = "DELETE FROM services WHERE id = ?";
        
        try (Connection conn = getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setLong(1, id);
            pstmt.executeUpdate();
            logger.info("Сервис удален: id={}", id);
        } catch (SQLException e) {
            logger.error("Ошибка при удалении сервиса", e);
            throw new RuntimeException("Не удалось удалить сервис", e);
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

