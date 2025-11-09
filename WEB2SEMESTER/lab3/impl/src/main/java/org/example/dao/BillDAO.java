package org.example.dao;

import org.example.dbConnection.JdbcConnector;
import org.example.model.Bill;

import java.sql.*;

public class BillDAO {
    private static final String SELECT_BILL_BY_SUBSCRIBER =
            "SELECT id, amount, is_paid FROM bills WHERE subscriber_id = ?";
    private static final String PAY_BILL =
            "UPDATE bills SET is_paid = TRUE WHERE id = ?";

    public Bill getBillBySubscriber(int subscriberId) throws Exception {
        try (Connection conn = JdbcConnector.getConnection();
             PreparedStatement ps = conn.prepareStatement(SELECT_BILL_BY_SUBSCRIBER)) {
            ps.setInt(1, subscriberId);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                return new Bill(
                        rs.getInt("id"),
                        subscriberId,
                        rs.getDouble("amount"),
                        rs.getBoolean("is_paid")
                );
            }
        }
        return null;
    }

    public void payBill(int billId) throws Exception {
        try (Connection conn = JdbcConnector.getConnection();
             PreparedStatement ps = conn.prepareStatement(PAY_BILL)) {
            ps.setInt(1, billId);
            ps.executeUpdate();
        }
    }
}
