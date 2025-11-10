package org.example.dao.impl;

import org.example.dao.GenericDAO;
import org.example.entity.Subscriber;
import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityTransaction;
import jakarta.persistence.TypedQuery;
import org.example.util.JPAUtil;

import java.util.List;
import java.util.Optional;

public class SubscriberDAO extends GenericDAO<Subscriber, Long> {
    private final EntityManager entityManager;

    public SubscriberDAO() {
        super(Subscriber.class);
        this.entityManager = JPAUtil.getEntityManager();
    }

    @Override
    protected EntityManager getEntityManager() {
        return entityManager;
    }

    public Optional<Subscriber> findByPhoneNumber(String phoneNumber) {
        try {
            TypedQuery<Subscriber> query = entityManager.createNamedQuery("Subscriber.findByPhoneNumber", Subscriber.class);
            query.setParameter("phoneNumber", phoneNumber);
            return query.getResultStream().findFirst();
        } catch (Exception e) {
            throw new RuntimeException("Error finding subscriber by phone number", e);
        }
    }

    public List<Subscriber> findBlockedSubscribers() {
        try {
            TypedQuery<Subscriber> query = entityManager.createNamedQuery("Subscriber.findBlocked", Subscriber.class);
            return query.getResultList();
        } catch (Exception e) {
            throw new RuntimeException("Error finding blocked subscribers", e);
        }
    }

    public List<Subscriber> findSubscribersWithUnpaidBills() {
        try {
            TypedQuery<Subscriber> query = entityManager.createNamedQuery("Subscriber.findWithUnpaidBills", Subscriber.class);
            return query.getResultList();
        } catch (Exception e) {
            throw new RuntimeException("Error finding subscribers with unpaid bills", e);
        }
    }

    public void blockSubscriber(Long subscriberId) {
        EntityTransaction transaction = null;
        try {
            transaction = entityManager.getTransaction();
            transaction.begin();
            Subscriber subscriber = entityManager.find(Subscriber.class, subscriberId);
            if (subscriber != null) {
                subscriber.setIsBlocked(true);
                entityManager.merge(subscriber);
            }
            transaction.commit();
        } catch (Exception e) {
            if (transaction != null && transaction.isActive()) {
                transaction.rollback();
            }
            throw new RuntimeException("Error blocking subscriber", e);
        }
    }

    public void unblockSubscriber(Long subscriberId) {
        EntityTransaction transaction = null;
        try {
            transaction = entityManager.getTransaction();
            transaction.begin();
            Subscriber subscriber = entityManager.find(Subscriber.class, subscriberId);
            if (subscriber != null) {
                subscriber.setIsBlocked(false);
                entityManager.merge(subscriber);
            }
            transaction.commit();
        } catch (Exception e) {
            if (transaction != null && transaction.isActive()) {
                transaction.rollback();
            }
            throw new RuntimeException("Error unblocking subscriber", e);
        }
    }
}