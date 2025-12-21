package com.app.lab8.controller;

import com.app.lab8.repository.ServiceRepository;
import com.app.lab8.entity.Service;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

@Controller
@RequestMapping("/services")
public class ServiceController {

    private final ServiceRepository serviceRepository;

    public ServiceController(ServiceRepository serviceRepository) {
        this.serviceRepository = serviceRepository;
    }

    @GetMapping
    public String list(Model model) {
        model.addAttribute("services", serviceRepository.findAll());
        return "services/list";
    }

    @GetMapping("/new")
    public String createForm(Model model) {
        model.addAttribute("service", new Service());
        return "services/form";
    }

    @PostMapping
    public String create(@ModelAttribute Service service, RedirectAttributes redirectAttributes) {
        serviceRepository.save(service);
        redirectAttributes.addFlashAttribute("message", "Услуга создана");
        return "redirect:/services";
    }

    @GetMapping("/{id}/edit")
    public String editForm(@PathVariable Long id, Model model) {
        Service service = serviceRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("Service not found: " + id));
        model.addAttribute("service", service);
        return "services/form";
    }

    @PostMapping("/{id}")
    public String update(@PathVariable Long id, @ModelAttribute Service service, RedirectAttributes redirectAttributes) {
        service.setId(id);
        serviceRepository.save(service);
        redirectAttributes.addFlashAttribute("message", "Услуга обновлена");
        return "redirect:/services";
    }

    @PostMapping("/{id}/delete")
    public String delete(@PathVariable Long id, RedirectAttributes redirectAttributes) {
        serviceRepository.deleteById(id);
        redirectAttributes.addFlashAttribute("message", "Услуга удалена");
        return "redirect:/services";
    }
}
