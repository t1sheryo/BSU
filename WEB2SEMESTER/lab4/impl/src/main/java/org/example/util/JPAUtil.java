package org.example.util;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import jakarta.persistence.Persistence;
import lombok.extern.java.Log;
import java.util.HashMap;
import java.util.Map;

@Log
public class JPAUtil {
    private static final String PERSISTENCE_UNIT_NAME = "phone_station_pu";
    private static EntityManagerFactory entityManagerFactory;

    static {
        try {
            log.info("Initializing JPA EntityManagerFactory for PostgreSQL...");

            // Свойства для Hibernate
            Map<String, String> properties = new HashMap<>();
            properties.put("hibernate.show_sql", "true");
            properties.put("hibernate.format_sql", "true");
            properties.put("hibernate.hbm2ddl.auto", "create");

            entityManagerFactory = Persistence.createEntityManagerFactory(PERSISTENCE_UNIT_NAME, properties);
            log.info("JPA EntityManagerFactory for PostgreSQL initialized successfully");
        } catch (Exception e) {
            log.severe("Error initializing JPA for PostgreSQL: " + e.getMessage());
            e.printStackTrace();
            throw new RuntimeException("Error initializing JPA for PostgreSQL", e);
        }
    }

    public static EntityManager getEntityManager() {
        try {
            return entityManagerFactory.createEntityManager();
        } catch (Exception e) {
            log.severe("Error creating EntityManager: " + e.getMessage());
            throw new RuntimeException("Error creating EntityManager", e);
        }
    }

    public static void close() {
        if (entityManagerFactory != null && entityManagerFactory.isOpen()) {
            entityManagerFactory.close();
            log.info("JPA EntityManagerFactory closed");
        }
    }

    // Метод для проверки подключения к PostgreSQL
    public static boolean testConnection() {
        EntityManager em = null;
        try {
            em = getEntityManager();
            // Правильный синтаксис для native query
            Object result = em.createNativeQuery("SELECT 1").getSingleResult();
            boolean connected = result != null;
            log.info("PostgreSQL connection test: " + (connected ? "SUCCESS" : "FAILED"));
            return connected;
        } catch (Exception e) {
            log.severe("PostgreSQL connection test failed: " + e.getMessage());
            return false;
        } finally {
            if (em != null && em.isOpen()) {
                em.close();
            }
        }
    }

    // Метод для получения информации о БД
    public static void printDatabaseInfo() {
        EntityManager em = null;
        try {
            em = getEntityManager();
            String version = (String) em.createNativeQuery("SELECT version()").getSingleResult();
            String dbName = (String) em.createNativeQuery("SELECT current_database()").getSingleResult();

            log.info("PostgreSQL Version: " + version);
            log.info("Current Database: " + dbName);

            System.out.println("📊 PostgreSQL Version: " + version);
            System.out.println("🗄️ Current Database: " + dbName);
        } catch (Exception e) {
            log.severe("Error getting database info: " + e.getMessage());
        } finally {
            if (em != null && em.isOpen()) {
                em.close();
            }
        }
    }
}