package org.example.dao.impl;

import org.example.dao.GenericDAO;
import org.example.entity.Bill;
import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityTransaction;
import jakarta.persistence.TypedQuery;
import org.example.util.JPAUtil;

import java.time.LocalDateTime;
import java.util.List;

public class BillDAO extends GenericDAO<Bill, Long> {
    private final EntityManager entityManager;

    public BillDAO() {
        super(Bill.class);
        this.entityManager = JPAUtil.getEntityManager();
    }

    @Override
    protected EntityManager getEntityManager() {
        return entityManager;
    }

    public List<Bill> findBillsBySubscriber(Long subscriberId) {
        try {
            TypedQuery<Bill> query = entityManager.createNamedQuery("Bill.findBySubscriber", Bill.class);
            query.setParameter("subscriberId", subscriberId);
            return query.getResultList();
        } catch (Exception e) {
            throw new RuntimeException("Error finding bills by subscriber", e);
        }
    }

    public List<Bill> findUnpaidBills() {
        try {
            TypedQuery<Bill> query = entityManager.createNamedQuery("Bill.findUnpaid", Bill.class);
            return query.getResultList();
        } catch (Exception e) {
            throw new RuntimeException("Error finding unpaid bills", e);
        }
    }

    public List<Bill> findOverdueBills() {
        try {
            TypedQuery<Bill> query = entityManager.createNamedQuery("Bill.findOverdue", Bill.class);
            return query.getResultList();
        } catch (Exception e) {
            throw new RuntimeException("Error finding overdue bills", e);
        }
    }

    public void payBill(Long billId) {
        EntityTransaction transaction = null;
        try {
            transaction = entityManager.getTransaction();
            transaction.begin();
            Bill bill = entityManager.find(Bill.class, billId);
            if (bill != null) {
                bill.setIsPaid(true);
                bill.setPaymentDate(LocalDateTime.now());
                entityManager.merge(bill);
            }
            transaction.commit();
        } catch (Exception e) {
            if (transaction != null && transaction.isActive()) {
                transaction.rollback();
            }
            throw new RuntimeException("Error paying bill", e);
        }
    }
}
