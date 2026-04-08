package com.app.lab8.controller;

import com.app.lab8.repository.ServiceRepository;
import com.app.lab8.entity.Service;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.data.domain.Sort;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;
import java.util.Locale;

@Controller
@RequestMapping("/services")
public class ServiceController {

    private final ServiceRepository serviceRepository;

    public ServiceController(ServiceRepository serviceRepository) {
        this.serviceRepository = serviceRepository;
    }

    @GetMapping
    public String list(@RequestParam(defaultValue = "0") int page,
                       @RequestParam(defaultValue = "5") int size,
                       Locale locale, Model model) {
        Pageable pagingSort = PageRequest.of(page, size, Sort.by(Sort.Direction.ASC, "name"));
        Page<Service> servicesPage = serviceRepository.findAllServicesWithPagination(pagingSort);
        model.addAttribute("servicesPage", servicesPage);
        model.addAttribute("services", servicesPage.getContent());
        model.addAttribute("currentPage", page);
        model.addAttribute("pageSize", size);
        model.addAttribute("totalPages", servicesPage.getTotalPages());
        model.addAttribute("totalItems", servicesPage.getTotalElements());
        model.addAttribute("currentLocale", locale.toLanguageTag());
        return "services/list";
    }

    @GetMapping("/new")
    public String createForm(Locale locale, Model model) {
        model.addAttribute("service", new Service());
        model.addAttribute("currentLocale", locale.toLanguageTag());
        return "services/form";
    }

    @PostMapping
    public String create(@ModelAttribute Service service, RedirectAttributes redirectAttributes) {
        serviceRepository.save(service);
        redirectAttributes.addFlashAttribute("message", "Услуга создана");
        return "redirect:/services";
    }

    @GetMapping("/{id}/edit")
    public String editForm(@PathVariable Long id, Locale locale, Model model) {
        Service service = serviceRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("Service not found: " + id));
        model.addAttribute("service", service);
        model.addAttribute("currentLocale", locale.toLanguageTag());
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
