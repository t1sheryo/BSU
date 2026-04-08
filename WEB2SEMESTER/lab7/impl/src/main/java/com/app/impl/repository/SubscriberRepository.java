package com.app.impl.repository;

import com.app.impl.entity.Subscriber;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import java.util.List;
import java.util.Optional;

public interface SubscriberRepository extends CrudRepository<Subscriber, Long> {
    Optional<Subscriber> findByPhoneNumber(String phoneNumber);

    List<Subscriber> findByIsBlockedTrue();

    @Query("SELECT s FROM Subscriber s WHERE EXISTS (SELECT b FROM com.app.impl.entity.Bill b WHERE b.subscriber = s AND b.isPaid = false)")
    List<Subscriber> findWithUnpaidBills();
}
