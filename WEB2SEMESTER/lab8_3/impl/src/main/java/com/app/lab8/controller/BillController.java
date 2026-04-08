package com.app.lab8.controller;

import com.app.lab8.repository.BillRepository;
import com.app.lab8.repository.SubscriberRepository;
import com.app.lab8.entity.Bill;
import com.app.lab8.entity.Subscriber;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.data.domain.Sort;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.Locale;

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
    public String list(@RequestParam(defaultValue = "0") int page,
                       @RequestParam(defaultValue = "5") int size,
                       @RequestParam(required = false) Long subscriberId,
                       Locale locale, Model model) {
        Pageable pagingSort = PageRequest.of(page, size, Sort.by(Sort.Direction.ASC, "id"));

        Page<Bill> billsPage;
        if (subscriberId != null) {
            billsPage = billRepository.findBySubscriberId(subscriberId, pagingSort);
            model.addAttribute("subscriberId", subscriberId);
        } else {
            billsPage = billRepository.findAllBillsWithPagination(pagingSort);
            model.addAttribute("subscriberId", null);
        }

        model.addAttribute("billsPage", billsPage);
        model.addAttribute("bills", billsPage.getContent());
        model.addAttribute("currentPage", page);
        model.addAttribute("pageSize", size);
        model.addAttribute("totalPages", billsPage.getTotalPages());
        model.addAttribute("totalItems", billsPage.getTotalElements());
        model.addAttribute("currentLocale", locale.toLanguageTag());
        model.addAttribute("subscribers", subscriberRepository.findAll());
        return "bills/list";
    }

    @GetMapping("/new")
    public String createForm(Locale locale, Model model) {
        model.addAttribute("bill", new Bill());
        model.addAttribute("subscribers", subscriberRepository.findAll());
        model.addAttribute("currentLocale", locale.toLanguageTag());
        return "bills/form";
    }

    @PostMapping
    public String create(@RequestParam("subscriberId") Long subscriberId,
                         @RequestParam("amount") Double amount,
                         @RequestParam(name = "dueDate", required = false) String dueDate,
                         Locale locale, RedirectAttributes redirectAttributes) {
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

    @GetMapping("/{id}/edit")
    public String editForm(@PathVariable Long id, Locale locale, Model model) {
        Bill bill = billRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("Bill not found: " + id));
        model.addAttribute("bill", bill);
        model.addAttribute("subscribers", subscriberRepository.findAll());
        model.addAttribute("currentLocale", locale.toLanguageTag());
        return "bills/form";
    }

    @PostMapping("/{id}/pay")
    public String pay(@PathVariable Long id, Locale locale, RedirectAttributes redirectAttributes) {
        Bill bill = billRepository.findById(id)
                .orElseThrow(() -> new IllegalArgumentException("Bill not found: " + id));
        bill.setIsPaid(true);
        bill.setPaymentDate(LocalDateTime.now());
        billRepository.save(bill);
        redirectAttributes.addFlashAttribute("message", "Счет оплачен");
        return "redirect:/bills";
    }

    @PostMapping("/{id}/delete")
    public String delete(@PathVariable Long id, Locale locale, RedirectAttributes redirectAttributes) {
        billRepository.deleteById(id);
        redirectAttributes.addFlashAttribute("message", "Счет удален");
        return "redirect:/bills";
    }
}
