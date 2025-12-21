package com.app.lab8.controller;

import com.app.lab8.repository.SubscriberRepository;
import com.app.lab8.entity.Subscriber;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

@Controller
@RequestMapping("/subscribers")
public class SubscriberController {

    private final SubscriberRepository subscriberRepository;

    public SubscriberController(SubscriberRepository subscriberRepository) {
        this.subscriberRepository = subscriberRepository;
    }

    @GetMapping
    public String list(Model model) {
        model.addAttribute("subscribers", subscriberRepository.findAll());
        return "subscribers/list";
    }

    @GetMapping("/new")
    public String createForm(Model model) {
        model.addAttribute("subscriber", new Subscriber());
        return "subscribers/form";
    }

    @PostMapping
    public String create(@ModelAttribute Subscriber subscriber, RedirectAttributes redirectAttributes) {
        subscriberRepository.save(subscriber);
        redirectAttributes.addFlashAttribute("message", "Абонент создан");
        return "redirect:/subscribers";
    }

    @GetMapping("/{id}/edit")
    public String editForm(@PathVariable Long id, Model model) {
        Subscriber subscriber = subscriberRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("Subscriber not found: " + id));
        model.addAttribute("subscriber", subscriber);
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
