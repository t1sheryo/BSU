package com.app.lab8.controller;

import com.app.lab8.repository.BillRepository;
import com.app.lab8.repository.SubscriberRepository;
import com.app.lab8.entity.Bill;
import com.app.lab8.entity.Subscriber;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;

@Controller
@RequestMapping("/bills")
public class BillController {

    private final BillRepository billRepository;
    private final SubscriberRepository subscriberRepository;

    public BillController(BillRepository billRepository, SubscriberRepository subscriberRepository) {
        this.billRepository = billRepository;
        this.subscriberRepository = subscriberRepository;
    }

    @GetMapping
    public String list(@RequestParam(name = "subscriberId", required = false) Long subscriberId, Model model) {
        if (subscriberId != null) {
            model.addAttribute("bills", billRepository.findBySubscriberId(subscriberId));
            model.addAttribute("subscriberId", subscriberId);
        } else {
            model.addAttribute("bills", billRepository.findAll());
            model.addAttribute("subscriberId", null);
        }
        model.addAttribute("subscribers", subscriberRepository.findAll());
        return "bills/list";
    }

    @GetMapping("/new")
    public String createForm(Model model) {
        model.addAttribute("bill", new Bill());
        model.addAttribute("subscribers", subscriberRepository.findAll());
        return "bills/form";
    }

    @PostMapping
    public String create(@RequestParam("subscriberId") Long subscriberId,
                         @RequestParam("amount") Double amount,
                         @RequestParam(name = "dueDate", required = false) String dueDate,
                         RedirectAttributes redirectAttributes) {
        Subscriber subscriber = subscriberRepository.findById(subscriberId)
                .orElseThrow(() -> new IllegalArgumentException("Subscriber not found: " + subscriberId));

        Bill bill = new Bill();
        bill.setSubscriber(subscriber);
        bill.setAmount(amount);

        if (dueDate != null && !dueDate.isBlank()) {
            bill.setDueDate(parseLocalDateTime(dueDate));
        }

        billRepository.save(bill);
        redirectAttributes.addFlashAttribute("message", "Счет создан");
        return "redirect:/bills";
    }

    private static LocalDateTime parseLocalDateTime(String value) {
        try {
            return LocalDateTime.parse(value, DateTimeFormatter.ISO_LOCAL_DATE_TIME);
        } catch (DateTimeParseException ignored) {
            return LocalDateTime.parse(value, DateTimeFormatter.ofPattern("yyyy-MM-dd'T'HH:mm"));
        }
    }

    @PostMapping("/{id}/pay")
    public String pay(@PathVariable Long id, RedirectAttributes redirectAttributes) {
        Bill bill = billRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("Bill not found: " + id));
        bill.setIsPaid(true);
        bill.setPaymentDate(LocalDateTime.now());
        billRepository.save(bill);
        redirectAttributes.addFlashAttribute("message", "Счет оплачен");
        return "redirect:/bills";
    }

    @PostMapping("/{id}/delete")
    public String delete(@PathVariable Long id, RedirectAttributes redirectAttributes) {
        billRepository.deleteById(id);
        redirectAttributes.addFlashAttribute("message", "Счет удален");
        return "redirect:/bills";
    }
}
