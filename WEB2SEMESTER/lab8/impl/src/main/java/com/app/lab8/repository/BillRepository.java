package com.app.lab8.repository;

import com.app.lab8.entity.Bill;
import org.springframework.data.repository.CrudRepository;

public interface BillRepository extends CrudRepository<Bill, Long> {
    Iterable<Bill> findBySubscriberId(Long subscriberId);

    Iterable<Bill> findByIsPaidFalse();
}
