package org.example.model;

public record Bill(
        int id,
        int subscriberId,
        double amount,
        boolean isPaid
) { }
