package com.app.lab8.repository;

import com.app.lab8.entity.Bill;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

public interface BillRepository extends JpaRepository<Bill, Long> {
    Page<Bill> findBySubscriberId(Long subscriberId, Pageable pageable);

    @Query("SELECT b FROM Bill b")
    Page<Bill> findAllBillsWithPagination(Pageable pageable);

    Iterable<Bill> findByIsPaidFalse();
}
