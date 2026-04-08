package com.app.lab8.controller;

import com.app.lab8.entity.Service;
import com.app.lab8.repository.ServiceRepository;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/services")
@CrossOrigin(origins = "http://localhost:4200")
public class ServiceRestController {

    private final ServiceRepository serviceRepository;

    public ServiceRestController(ServiceRepository serviceRepository) {
        this.serviceRepository = serviceRepository;
    }

    public record ServiceDto(Long id, String description, Double price) {
    }

    @GetMapping
    public List<ServiceDto> getAll() {
        return serviceRepository.findAll().stream().map(ServiceRestController::toDto).toList();
    }

    @GetMapping("/{id}")
    public ResponseEntity<ServiceDto> getById(@PathVariable Long id) {
        return serviceRepository.findById(id)
                .map(ServiceRestController::toDto)
                .map(ResponseEntity::ok)
                .orElseGet(() -> ResponseEntity.notFound().build());
    }

    @PostMapping
    public ResponseEntity<ServiceDto> add(@RequestBody ServiceDto dto) {
        Service created = new Service();
        created.setName(dto.description());
        created.setDescription(dto.description());
        created.setMonthlyFee(dto.price());
        created.setIsActive(true);

        Service saved = serviceRepository.save(created);
        return ResponseEntity.status(HttpStatus.CREATED).body(toDto(saved));
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> delete(@PathVariable Long id) {
        if (!serviceRepository.existsById(id)) {
            return ResponseEntity.notFound().build();
        }
        serviceRepository.deleteById(id);
        return ResponseEntity.noContent().build();
    }

    private static ServiceDto toDto(Service entity) {
        String description = entity.getDescription();
        if (description == null || description.isBlank()) {
            description = entity.getName();
        }
        return new ServiceDto(entity.getId(), description, entity.getMonthlyFee());
    }
}
