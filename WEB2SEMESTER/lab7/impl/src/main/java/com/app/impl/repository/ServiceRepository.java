package com.app.impl.repository;

import com.app.impl.entity.Service;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import java.util.List;

public interface ServiceRepository extends CrudRepository<Service, Long> {
    List<Service> findByIsActiveTrue();

    // Найти сервисы по id абонента (через связь many-to-many)
    @Query("SELECT s FROM com.app.impl.entity.Service s JOIN s.subscribers sub WHERE sub.id = :subscriberId")
    List<Service> findBySubscriberId(Long subscriberId);
}