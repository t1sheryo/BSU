package com.app.impl.repository;

import com.app.impl.entity.Bill;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import java.util.List;

public interface BillRepository extends CrudRepository<Bill, Long> {
    List<Bill> findBySubscriberId(Long subscriberId);

    List<Bill> findByIsPaidFalse();

    // Просроченные счета (dueDate < now)
    @Query("SELECT b FROM com.app.impl.entity.Bill b WHERE b.isPaid = false AND b.dueDate < CURRENT_TIMESTAMP")
    List<Bill> findOverdue();
}