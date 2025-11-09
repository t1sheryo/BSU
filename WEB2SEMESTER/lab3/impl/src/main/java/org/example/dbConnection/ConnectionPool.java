package org.example.dbConnection;

import lombok.extern.slf4j.Slf4j;

import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

@Slf4j
public class ConnectionPool {
    private static ConnectionPool instance;
    private final BlockingQueue<Connection> connections;
    private final String url;
    private final String username;
    private final String password;
    private final int poolSize;

    private ConnectionPool() {
        try {
            Properties props = new Properties();
            try (InputStream input = JdbcConnector.class
                    .getClassLoader()
                    .getResourceAsStream("application.properties")) {
                props.load(input);
            }
            this.url = props.getProperty("db.url");
            this.username = props.getProperty("db.user");
            this.password = props.getProperty("db.password");
            this.poolSize = Integer.parseInt(props.getProperty("db.pool.size", "10"));

            this.connections = new ArrayBlockingQueue<>(poolSize);
            initializePool();
            log.atInfo()
                    .addArgument(poolSize)
                    .log("Connection pool initialized with size: {}");

        } catch (Exception e) {
            log.atError()
                    .addArgument(e)
                    .log("Failed to initialize connection pool: {}");
            throw new RuntimeException("Failed to initialize connection pool", e);
        }
    }

    public static synchronized ConnectionPool getInstance() {
        if (instance == null) {
            instance = new ConnectionPool();
        }
        return instance;
    }

    private void initializePool() throws SQLException {
        for (int i = 0; i < poolSize; i++) {
            Connection conn = DriverManager.getConnection(url, username, password);
            connections.offer(conn);
        }

        log.atDebug()
                .addArgument(poolSize)
                .log("Initialized {} connections");
    }

    public Connection getConnection() {
        try {
            log.atDebug()
                    .addArgument(connections.size())
                    .log("Getting connection from pool. Available: {}");
            return connections.take(); // Блокирует пока connection не будет доступен
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            log.atError()
                    .addArgument(e)
                    .log("Interrupted while waiting for connection {}");
            throw new RuntimeException("Interrupted while waiting for connection", e);
        }
    }

    public void returnConnection(Connection conn) {
        if (conn != null) {
            try {
                if (!conn.isClosed()) {
                    connections.offer(conn);
                    log.atDebug()
                            .addArgument(connections.size())
                            .log("Connection returned to pool. Available: {}");
                } else {
                    Connection newConn = DriverManager.getConnection(url, username, password);
                    connections.offer(newConn);
                    log.atWarn().log("Closed connection replaced with new one");
                }
            } catch (SQLException e) {
                log.atError()
                        .addArgument(e)
                        .log("Failed to return connection to pool");
                throw new RuntimeException("Failed to return connection to pool", e);
            }
        }
    }

    public void closeAll() {
        log.atInfo().log("Closing all connections in pool");
        for (Connection conn : connections) {
            try {
                if (!conn.isClosed()) {
                    conn.close();
                }
            } catch (SQLException e) {
                log.atWarn()
                        .addArgument(e)
                        .log("Error closing connection");
            }
        }
        connections.clear();
    }
}