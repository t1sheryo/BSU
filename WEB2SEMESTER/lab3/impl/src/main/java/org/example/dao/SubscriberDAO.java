package org.example.dao;

import org.example.dbConnection.JdbcConnector;
import org.example.model.Service;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class SubscriberDAO {
    private static final String SELECT_SERVICES_BY_SUBSCRIBER =
            "SELECT s.id, s.name, s.monthly_fee FROM services s " +
                    "JOIN subscriber_services ss ON s.id = ss.service_id " +
                    "WHERE ss.subscriber_id = ?";

    private static final String BLOCK_SUBSCRIBER =
            "UPDATE subscribers SET is_blocked = TRUE WHERE id = ?";

    public List<Service> getServicesBySubscriber(int subscriberId) throws Exception {
        List<Service> services = new ArrayList<>();
        try (Connection conn = JdbcConnector.getConnection();
             PreparedStatement ps = conn.prepareStatement(SELECT_SERVICES_BY_SUBSCRIBER)) {
            ps.setInt(1, subscriberId);
            ResultSet rs = ps.executeQuery();
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

    public void blockSubscriber(int subscriberId) throws Exception {
        try (Connection conn = JdbcConnector.getConnection();
             PreparedStatement ps = conn.prepareStatement(BLOCK_SUBSCRIBER)) {
            ps.setInt(1, subscriberId);
            ps.executeUpdate();
        }
    }
}
