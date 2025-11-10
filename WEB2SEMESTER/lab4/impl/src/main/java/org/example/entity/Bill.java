package org.example.entity;

import lombok.*;
import jakarta.persistence.*;
import java.time.LocalDateTime;

@Entity
@Table(name = "bills_lab_4")
@NamedQueries({
        @NamedQuery(name = "Bill.findAll", query = "SELECT b FROM Bill b"),
        @NamedQuery(name = "Bill.findBySubscriber",
                query = "SELECT b FROM Bill b WHERE b.subscriber.id = :subscriberId"),
        @NamedQuery(name = "Bill.findUnpaid",
                query = "SELECT b FROM Bill b WHERE b.isPaid = false"),
        @NamedQuery(name = "Bill.findOverdue",
                query = "SELECT b FROM Bill b WHERE b.isPaid = false AND b.dueDate < CURRENT_DATE")
})
@NoArgsConstructor
@AllArgsConstructor
@Data
public class Bill {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "amount", nullable = false)
    private Double amount;

    @Column(name = "issue_date")
    private LocalDateTime issueDate;

    @Column(name = "due_date")
    private LocalDateTime dueDate;

    @Column(name = "is_paid")
    private Boolean isPaid = false;

    @Column(name = "payment_date")
    private LocalDateTime paymentDate;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "subscriber_id")
    @ToString.Exclude
    private Subscriber subscriber;

    @PrePersist
    protected void onCreate() {
        issueDate = LocalDateTime.now();
        if (dueDate == null) {
            dueDate = issueDate.plusDays(30);
        }
    }

    public Bill(Double amount, Subscriber subscriber) {
        this.amount = amount;
        this.subscriber = subscriber;
    }
}
