package org.example.dbConnection;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

public class JdbcConnector {
    private static Connection connection;

    public static Connection getConnection() throws SQLException, IOException {
        if (connection == null || connection.isClosed()) {
            Properties props = new Properties();
            try (InputStream input = JdbcConnector.class
                    .getClassLoader()
                    .getResourceAsStream("application.properties")) {
                props.load(input);
            }

            final String url = props.getProperty("db.url");
            final String username = props.getProperty("db.user");
            final String password = props.getProperty("db.password");

            connection = DriverManager.getConnection(url, username, password);
        }
        return connection;
    }
}
