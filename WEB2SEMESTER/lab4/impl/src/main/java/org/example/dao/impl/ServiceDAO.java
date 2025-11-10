package org.example.dao.impl;

import org.example.dao.GenericDAO;
import org.example.entity.Service;
import jakarta.persistence.EntityManager;
import jakarta.persistence.TypedQuery;
import org.example.util.JPAUtil;

import java.util.List;

public class ServiceDAO extends GenericDAO<Service, Long> {
    private final EntityManager entityManager;

    public ServiceDAO() {
        super(Service.class);
        this.entityManager = JPAUtil.getEntityManager();
    }

    @Override
    protected EntityManager getEntityManager() {
        return entityManager;
    }

    public List<Service> findActiveServices() {
        try {
            TypedQuery<Service> query = entityManager.createNamedQuery("Service.findActive", Service.class);
            return query.getResultList();
        } catch (Exception e) {
            throw new RuntimeException("Error finding active services", e);
        }
    }

    public List<Service> findServicesBySubscriber(Long subscriberId) {
        try {
            TypedQuery<Service> query = entityManager.createNamedQuery("Service.findBySubscriber", Service.class);
            query.setParameter("subscriberId", subscriberId);
            return query.getResultList();
        } catch (Exception e) {
            throw new RuntimeException("Error finding services by subscriber", e);
        }
    }
}