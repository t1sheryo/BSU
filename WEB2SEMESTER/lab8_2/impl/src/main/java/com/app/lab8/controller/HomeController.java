package com.app.lab8.controller;

import org.springframework.context.MessageSource;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.GetMapping;
import java.util.Locale;

@Controller
public class HomeController {

    private final MessageSource messageSource;

    public HomeController(MessageSource messageSource) {
        this.messageSource = messageSource;
    }

    @GetMapping("/")
    public String index(@RequestParam(value = "lang", required = false) String lang, Locale locale, Model model) {
        System.out.println(locale + lang);
        model.addAttribute("currentLocale", locale.toLanguageTag());
        model.addAttribute("requestLang", lang);
        model.addAttribute("resolvedPageHeading", messageSource.getMessage("page.heading", null, locale));
        return "index";
    }
}
