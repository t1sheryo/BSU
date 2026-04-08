package com.app.lab8.repository;

import com.app.lab8.entity.Subscriber;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.util.Optional;

public interface SubscriberRepository extends JpaRepository<Subscriber, Long> {
    Optional<Subscriber> findByPhoneNumber(String phoneNumber);

    @Query("SELECT s FROM Subscriber s")
    Page<Subscriber> findAllSubscribersWithPagination(Pageable pageable);
}
