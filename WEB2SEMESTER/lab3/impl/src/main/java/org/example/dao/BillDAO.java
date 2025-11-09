package org.example.dao;

import org.example.dbConnection.ConnectionPool;
import org.example.model.Bill;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class BillDAO {
    private static final Logger logger = LoggerFactory.getLogger(BillDAO.class);

    private static final String SELECT_BILL_BY_SUBSCRIBER =
            "SELECT id, subscriber_id, amount, is_paid FROM bills WHERE subscriber_id = ?";

    private static final String PAY_BILL =
            "UPDATE bills SET is_paid = true WHERE id = ? AND is_paid = false";

    private final ConnectionPool connectionPool;

    public BillDAO() {
        this.connectionPool = ConnectionPool.getInstance();
        logger.debug("BillDAO initialized");
    }

    public Bill getBillBySubscriber(int subscriberId) {
        logger.debug("Getting bill for subscriber ID: {}", subscriberId);
        Connection conn = null;

        try {
            conn = connectionPool.getConnection();
            PreparedStatement ps = conn.prepareStatement(SELECT_BILL_BY_SUBSCRIBER);
            ps.setInt(1, subscriberId);
            ResultSet rs = ps.executeQuery();

            if (rs.next()) {
                Bill bill = new Bill(
                        rs.getInt("id"),
                        rs.getInt("subscriber_id"),
                        rs.getDouble("amount"),
                        rs.getBoolean("is_paid")
                );
                logger.info("Found bill for subscriber ID: {}", subscriberId);
                return bill;
            }

            logger.warn("No bill found for subscriber ID: {}", subscriberId);
            return null;

        } catch (Exception e) {
            logger.error("Failed to get bill for subscriber ID: {}", subscriberId, e);
            throw new RuntimeException("Database error while retrieving bill", e);
        } finally {
            if (conn != null) {
                connectionPool.returnConnection(conn);
            }
        }
    }

    public boolean payBill(int billId) {
        logger.debug("Paying bill ID: {}", billId);
        Connection conn = null;

        try {
            conn = connectionPool.getConnection();
            PreparedStatement ps = conn.prepareStatement(PAY_BILL);
            ps.setInt(1, billId);

            int rowsAffected = ps.executeUpdate();
            boolean success = rowsAffected > 0;

            if (success) {
                logger.info("Successfully paid bill ID: {}", billId);
            } else {
                logger.warn("Bill not found or already paid, ID: {}", billId);
            }

            return success;

        } catch (Exception e) {
            logger.error("Failed to pay bill ID: {}", billId, e);
            throw new RuntimeException("Database error while paying bill", e);
        } finally {
            if (conn != null) {
                connectionPool.returnConnection(conn);
            }
        }
    }
}