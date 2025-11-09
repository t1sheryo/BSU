package org.example.entity;

import lombok.*;
import jakarta.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Entity
@Table(name = "subscribers")
@NamedQueries({
        @NamedQuery(name = "Subscriber.findAll", query = "SELECT s FROM Subscriber s"),
        @NamedQuery(name = "Subscriber.findByPhoneNumber",
                query = "SELECT s FROM Subscriber s WHERE s.phoneNumber = :phoneNumber"),
        @NamedQuery(name = "Subscriber.findBlocked",
                query = "SELECT s FROM Subscriber s WHERE s.isBlocked = true"),
        @NamedQuery(name = "Subscriber.findWithUnpaidBills",
                query = "SELECT s FROM Subscriber s WHERE EXISTS " +
                        "(SELECT b FROM Bill b WHERE b.subscriber = s AND b.isPaid = false)")
})
@NoArgsConstructor
@AllArgsConstructor
@Data
public class Subscriber {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "first_name", nullable = false)
    private String firstName;

    @Column(name = "last_name", nullable = false)
    private String lastName;

    @Column(name = "phone_number", unique = true, nullable = false)
    private String phoneNumber;

    @Column(name = "address")
    private String address;

    @Column(name = "is_blocked")
    private Boolean isBlocked = false;

    @OneToMany(mappedBy = "subscriber", cascade = CascadeType.ALL, fetch = FetchType.LAZY)
    @ToString.Exclude
    private List<Bill> bills = new ArrayList<>();

    @ManyToMany(fetch = FetchType.LAZY)
    @JoinTable(
            name = "subscriber_services",
            joinColumns = @JoinColumn(name = "subscriber_id"),
            inverseJoinColumns = @JoinColumn(name = "service_id")
    )
    @ToString.Exclude
    private List<Service> services = new ArrayList<>();

    public Subscriber(String firstName, String lastName, String phoneNumber, String address) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.phoneNumber = phoneNumber;
        this.address = address;
    }
}