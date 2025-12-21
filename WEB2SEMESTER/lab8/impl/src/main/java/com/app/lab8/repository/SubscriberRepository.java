package com.app.lab8.repository;

import com.app.lab8.entity.Subscriber;
import org.springframework.data.repository.CrudRepository;

import java.util.Optional;

public interface SubscriberRepository extends CrudRepository<Subscriber, Long> {
    Optional<Subscriber> findByPhoneNumber(String phoneNumber);
}
