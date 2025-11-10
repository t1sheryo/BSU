package org.example;

import org.example.dao.impl.BillDAO;
import org.example.dao.impl.ServiceDAO;
import org.example.dao.impl.SubscriberDAO;
import lombok.extern.java.Log;
import org.example.entity.Bill;
import org.example.entity.Service;
import org.example.entity.Subscriber;
import org.example.util.JPAUtil;

import java.util.List;
import java.util.Optional;
import java.util.Scanner;

@Log
public class Main {
    private final Scanner scanner = new Scanner(System.in);
    private final SubscriberDAO subscriberDAO = new SubscriberDAO();
    private final ServiceDAO serviceDAO = new ServiceDAO();
    private final BillDAO billDAO = new BillDAO();

    public static void main(String[] args) {
        Main app = new Main();
        app.run();
    }

    public void run() {
        JPAUtil.printDatabaseInfo();

        // Проверка подключения к PostgreSQL
        if (!JPAUtil.testConnection()) {
            System.out.println("❌ Не удалось подключиться к PostgreSQL!");
            System.out.println("Проверьте:");
            System.out.println("1. Запущен ли PostgreSQL сервер");
            System.out.println("2. Правильность настроек в persistence.xml");
            System.out.println("3. Существует ли база данных 'phone_station'");
            System.out.println("4. Правильность имени пользователя и пароля");
            return;
        }

        System.out.println("✅ Подключение к PostgreSQL успешно!");

        boolean running = true;

        while (running) {
            printMenu();
            int choice = getIntInput("Выберите действие: ");

            switch (choice) {
                case 1 -> showSubscriberServices();
                case 2 -> showSubscriberBills();
                case 3 -> showAvailableServices();
                case 4 -> payBill();
                case 5 -> blockSubscriber();
                case 6 -> showUnpaidBills();
                case 7 -> createTestData();
                case 0 -> running = false;
                default -> System.out.println("Неверный выбор!");
            }
        }

        JPAUtil.close();
        System.out.println("Программа завершена.");
    }

    private void printMenu() {
        System.out.println("\n=== ТЕЛЕФОННАЯ СТАНЦИЯ ===");
        System.out.println("1. Услуги абонента");
        System.out.println("2. Счета абонента");
        System.out.println("3. Доступные услуги");
        System.out.println("4. Оплатить счет");
        System.out.println("5. Заблокировать абонента");
        System.out.println("6. Просмотреть неоплаченные счета");
        System.out.println("7. Создать тестовые данные");
        System.out.println("0. Выход");
    }

    private void showSubscriberServices() {
        String phoneNumber = getStringInput("Введите номер телефона абонента: ");
        Optional<Subscriber> subscriberOpt = subscriberDAO.findByPhoneNumber(phoneNumber);

        if (subscriberOpt.isPresent()) {
            Subscriber subscriber = subscriberOpt.get();
            List<Service> services = serviceDAO.findServicesBySubscriber(subscriber.getId());

            System.out.println("\nУслуги абонента " + subscriber.getFirstName() + " " + subscriber.getLastName() + ":");
            if (services.isEmpty()) {
                System.out.println("У абонента нет подключенных услуг.");
            } else {
                services.forEach(service ->
                        System.out.printf("- %s (%.2f руб./мес.) - %s%n",
                                service.getName(), service.getMonthlyFee(), service.getDescription()));
            }
        } else {
            System.out.println("Абонент не найден!");
        }
    }

    private void showSubscriberBills() {
        String phoneNumber = getStringInput("Введите номер телефона абонента: ");
        Optional<Subscriber> subscriberOpt = subscriberDAO.findByPhoneNumber(phoneNumber);

        if (subscriberOpt.isPresent()) {
            Subscriber subscriber = subscriberOpt.get();
            List<Bill> bills = billDAO.findBillsBySubscriber(subscriber.getId());

            System.out.println("\nСчета абонента " + subscriber.getFirstName() + " " + subscriber.getLastName() + ":");
            if (bills.isEmpty()) {
                System.out.println("У абонента нет счетов.");
            } else {
                bills.forEach(bill ->
                        System.out.printf("- Счет #%d: %.2f руб. | Выдан: %s | Срок: %s | Статус: %s%n",
                                bill.getId(), bill.getAmount(),
                                bill.getIssueDate().toLocalDate(),
                                bill.getDueDate().toLocalDate(),
                                bill.getIsPaid() ? "Оплачен" : "Не оплачен"));
            }
        } else {
            System.out.println("Абонент не найден!");
        }
    }

    private void showAvailableServices() {
        List<Service> services = serviceDAO.findActiveServices();

        System.out.println("\nДоступные услуги:");
        if (services.isEmpty()) {
            System.out.println("Нет доступных услуг.");
        } else {
            services.forEach(service ->
                    System.out.printf("- %s: %.2f руб./мес. | %s%n",
                            service.getName(), service.getMonthlyFee(), service.getDescription()));
        }
    }

    private void payBill() {
        Long billId = getLongInput("Введите ID счета для оплаты: ");

        try {
            billDAO.payBill(billId);
            System.out.println("Счет успешно оплачен!");
        } catch (Exception e) {
            System.out.println("Ошибка при оплате счета: " + e.getMessage());
        }
    }

    private void blockSubscriber() {
        String phoneNumber = getStringInput("Введите номер телефона абонента для блокировки: ");
        Optional<Subscriber> subscriberOpt = subscriberDAO.findByPhoneNumber(phoneNumber);

        if (subscriberOpt.isPresent()) {
            Subscriber subscriber = subscriberOpt.get();
            subscriberDAO.blockSubscriber(subscriber.getId());
            System.out.println("Абонент заблокирован!");
        } else {
            System.out.println("Абонент не найден!");
        }
    }

    private void showUnpaidBills() {
        List<Bill> unpaidBills = billDAO.findUnpaidBills();

        System.out.println("\nНеоплаченные счета:");
        if (unpaidBills.isEmpty()) {
            System.out.println("Нет неоплаченных счетов.");
        } else {
            unpaidBills.forEach(bill ->
                    System.out.printf("- Счет #%d: %s %s | %.2f руб. | Телефон: %s%n",
                            bill.getId(),
                            bill.getSubscriber().getFirstName(),
                            bill.getSubscriber().getLastName(),
                            bill.getAmount(),
                            bill.getSubscriber().getPhoneNumber()));
        }
    }

    private void createTestData() {
        try {
            // Создаем услуги
            Service internet = new Service("Интернет", "Высокоскоростной интернет", 500.0);
            Service tv = new Service("Телевидение", "Цифровое ТВ", 300.0);
            Service phone = new Service("Телефония", "Городская связь", 100.0);

            serviceDAO.save(internet);
            serviceDAO.save(tv);
            serviceDAO.save(phone);

            // Создаем абонентов
            Subscriber subscriber1 = new Subscriber("Иван", "Петров", "+79161234567", "ул. Ленина, 1");
            Subscriber subscriber2 = new Subscriber("Мария", "Сидорова", "+79167654321", "ул. Мира, 15");

            subscriber1.getServices().add(internet);
            subscriber1.getServices().add(phone);
            subscriber2.getServices().add(tv);
            subscriber2.getServices().add(internet);

            subscriberDAO.save(subscriber1);
            subscriberDAO.save(subscriber2);

            // Создаем счета
            Bill bill1 = new Bill(600.0, subscriber1);
            Bill bill2 = new Bill(400.0, subscriber2);
            Bill bill3 = new Bill(800.0, subscriber1);
            bill3.setIsPaid(true);

            billDAO.save(bill1);
            billDAO.save(bill2);
            billDAO.save(bill3);

            System.out.println("Тестовые данные созданы успешно!");

        } catch (Exception e) {
            System.out.println("Ошибка при создании тестовых данных: " + e.getMessage());
        }
    }

    // Вспомогательные методы для ввода
    private String getStringInput(String prompt) {
        System.out.print(prompt);
        return scanner.nextLine();
    }

    private int getIntInput(String prompt) {
        while (true) {
            try {
                System.out.print(prompt);
                return Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) {
                System.out.println("Пожалуйста, введите целое число!");
            }
        }
    }

    private Long getLongInput(String prompt) {
        while (true) {
            try {
                System.out.print(prompt);
                return Long.parseLong(scanner.nextLine());
            } catch (NumberFormatException e) {
                System.out.println("Пожалуйста, введите число!");
            }
        }
    }
}