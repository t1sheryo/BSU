package org.example.dao;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityTransaction;
import jakarta.persistence.TypedQuery;
import java.util.List;
import java.util.Optional;

public abstract class GenericDAO<T, ID> {
    private final Class<T> entityClass;

    public GenericDAO(Class<T> entityClass) {
        this.entityClass = entityClass;
    }

    protected abstract EntityManager getEntityManager();

    public T save(T entity) {
        EntityTransaction transaction = null;
        try {
            EntityManager em = getEntityManager();
            transaction = em.getTransaction();
            transaction.begin();
            em.persist(entity);
            transaction.commit();
            return entity;
        } catch (Exception e) {
            if (transaction != null && transaction.isActive()) {
                transaction.rollback();
            }
            throw new RuntimeException("Error saving entity", e);
        }
    }

    public Optional<T> findById(ID id) {
        try {
            T entity = getEntityManager().find(entityClass, id);
            return Optional.ofNullable(entity);
        } catch (Exception e) {
            throw new RuntimeException("Error finding entity by id", e);
        }
    }

    public List<T> findAll() {
        try {
            String queryString = "SELECT e FROM " + entityClass.getSimpleName() + " e";
            TypedQuery<T> query = getEntityManager().createQuery(queryString, entityClass);
            return query.getResultList();
        } catch (Exception e) {
            throw new RuntimeException("Error finding all entities", e);
        }
    }

    public T update(T entity) {
        EntityTransaction transaction = null;
        try {
            EntityManager em = getEntityManager();
            transaction = em.getTransaction();
            transaction.begin();
            T merged = em.merge(entity);
            transaction.commit();
            return merged;
        } catch (Exception e) {
            if (transaction != null && transaction.isActive()) {
                transaction.rollback();
            }
            throw new RuntimeException("Error updating entity", e);
        }
    }

    public void delete(ID id) {
        EntityTransaction transaction = null;
        try {
            EntityManager em = getEntityManager();
            transaction = em.getTransaction();
            transaction.begin();
            T entity = em.find(entityClass, id);
            if (entity != null) {
                em.remove(entity);
            }
            transaction.commit();
        } catch (Exception e) {
            if (transaction != null && transaction.isActive()) {
                transaction.rollback();
            }
            throw new RuntimeException("Error deleting entity", e);
        }
    }
}