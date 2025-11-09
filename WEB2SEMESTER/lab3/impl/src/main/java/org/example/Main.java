package org.example;

import org.example.dao.BillDAO;
import org.example.dao.ServiceDAO;
import org.example.dao.SubscriberDAO;
import org.example.migration.LiquibaseRunner;
import org.example.model.Bill;
import org.example.model.Service;

import java.sql.SQLException;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try {
            new LiquibaseRunner().run();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        Scanner sc = new Scanner(System.in);
        SubscriberDAO subscriberDAO = new SubscriberDAO();
        BillDAO billDAO = new BillDAO();
        ServiceDAO serviceDAO = new ServiceDAO();

        while (true) {
            System.out.println("""
                \n=== Телефонная станция ===
                1. Показать услуги абонента
                2. Показать счёт абонента
                3. Показать все доступные услуги
                4. Оплатить счёт
                5. Заблокировать абонента
                0. Выход
            Выберите действие: 
            """);

            int choice = sc.nextInt();
            if (choice == 0) break;

            try {
                switch (choice) {
                    case 1 -> {
                        System.out.print("ID абонента: ");
                        int id = sc.nextInt();
                        List<Service> services = subscriberDAO.getServicesBySubscriber(id);
                        services.forEach(System.out::println);
                    }
                    case 2 -> {
                        System.out.print("ID абонента: ");
                        int id = sc.nextInt();
                        Bill bill = billDAO.getBillBySubscriber(id);
                        System.out.println(bill != null ? bill : "Счёт не найден.");
                    }
                    case 3 -> {
                        List<Service> all = serviceDAO.getAllServices();
                        all.forEach(System.out::println);
                    }
                    case 4 -> {
                        System.out.print("ID счёта: ");
                        int id = sc.nextInt();
                        billDAO.payBill(id);
                        System.out.println("Счёт успешно оплачен.");
                    }
                    case 5 -> {
                        System.out.print("ID абонента: ");
                        int id = sc.nextInt();
                        subscriberDAO.blockSubscriber(id);
                        System.out.println("Абонент заблокирован.");
                    }
                }
            } catch (Exception e) {
                System.err.println("Ошибка: " + e.getMessage());
            }
        }
    }
}
