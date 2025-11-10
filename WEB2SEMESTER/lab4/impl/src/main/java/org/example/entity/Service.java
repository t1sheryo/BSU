package org.example.entity;

import lombok.*;
import jakarta.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Entity
@Table(name = "services_lab_4")
@NamedQueries({
        @NamedQuery(name = "Service.findAll", query = "SELECT s FROM Service s"),
        @NamedQuery(name = "Service.findActive", query = "SELECT s FROM Service s WHERE s.isActive = true"),
        @NamedQuery(name = "Service.findBySubscriber",
                query = "SELECT s FROM Service s JOIN s.subscribers sub WHERE sub.id = :subscriberId")
})
@NoArgsConstructor
@AllArgsConstructor
@Data
public class Service {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "name", nullable = false)
    private String name;

    @Column(name = "description")
    private String description;

    @Column(name = "monthly_fee")
    private Double monthlyFee;

    @Column(name = "is_active")
    private Boolean isActive = true;

    @ManyToMany(mappedBy = "services", fetch = FetchType.LAZY)
    @ToString.Exclude
    private List<Subscriber> subscribers = new ArrayList<>();

    public Service(String name, String description, Double monthlyFee) {
        this.name = name;
        this.description = description;
        this.monthlyFee = monthlyFee;
    }
}
