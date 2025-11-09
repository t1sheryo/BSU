package org.example.dao;

import org.example.dbConnection.JdbcConnector;
import org.example.model.Service;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ServiceDAO {
    private static final String SELECT_ALL_SERVICES =
            "SELECT id, name, monthly_fee FROM services";

    public List<Service> getAllServices() throws Exception {
        List<Service> services = new ArrayList<>();
        try (Connection conn = JdbcConnector.getConnection();
             PreparedStatement ps = conn.prepareStatement(SELECT_ALL_SERVICES);
             ResultSet rs = ps.executeQuery()) {
            while (rs.next()) {
                services.add(new Service(
                        rs.getInt("id"),
                        rs.getString("name"),
                        rs.getDouble("monthly_fee")
                ));
            }
        }
        return services;
    }
}
