package com.app.lab8.controller;

import com.app.lab8.repository.SubscriberRepository;
import com.app.lab8.entity.Subscriber;
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
@RequestMapping("/subscribers")
public class SubscriberController {

    private final SubscriberRepository subscriberRepository;

    public SubscriberController(SubscriberRepository subscriberRepository) {
        this.subscriberRepository = subscriberRepository;
    }

    @GetMapping
    public String list(@RequestParam(defaultValue = "0") int page,
                       @RequestParam(defaultValue = "5") int size,
                       Locale locale, Model model) {
        Pageable pagingSort = PageRequest.of(page, size, Sort.by(Sort.Direction.ASC, "lastName"));
        Page<Subscriber> subscribersPage = subscriberRepository.findAllSubscribersWithPagination(pagingSort);
        model.addAttribute("subscribersPage", subscribersPage);
        model.addAttribute("subscribers", subscribersPage.getContent());
        model.addAttribute("currentPage", page);
        model.addAttribute("pageSize", size);
        model.addAttribute("totalPages", subscribersPage.getTotalPages());
        model.addAttribute("totalItems", subscribersPage.getTotalElements());
        model.addAttribute("currentLocale", locale.toLanguageTag());
        return "subscribers/list";
    }

    @GetMapping("/new")
    public String createForm(Locale locale, Model model) {
        model.addAttribute("subscriber", new Subscriber());
        model.addAttribute("currentLocale", locale.toLanguageTag());
        return "subscribers/form";
    }

    @PostMapping
    public String create(@ModelAttribute Subscriber subscriber, RedirectAttributes redirectAttributes) {
        subscriberRepository.save(subscriber);
        redirectAttributes.addFlashAttribute("message", "Абонент создан");
        return "redirect:/subscribers";
    }

    @GetMapping("/{id}/edit")
    public String editForm(@PathVariable Long id, Locale locale, Model model) {
        Subscriber subscriber = subscriberRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("Subscriber not found: " + id));
        model.addAttribute("subscriber", subscriber);
        model.addAttribute("currentLocale", locale.toLanguageTag());
        return "subscribers/form";
    }

    @PostMapping("/{id}")
    public String update(@PathVariable Long id, @ModelAttribute Subscriber subscriber, RedirectAttributes redirectAttributes) {
        subscriber.setId(id);
        subscriberRepository.save(subscriber);
        redirectAttributes.addFlashAttribute("message", "Абонент обновлен");
        return "redirect:/subscribers";
    }

    @PostMapping("/{id}/delete")
    public String delete(@PathVariable Long id, RedirectAttributes redirectAttributes) {
        subscriberRepository.deleteById(id);
        redirectAttributes.addFlashAttribute("message", "Абонент удален");
        return "redirect:/subscribers";
    }
}
