package math;

import java.util.Arrays;

/**
 * Тестовое приложение для демонстрации и проверки работы класса Rational.
 * @author Fiodor Likholap
 * @version 1.0
 */
public class Main {

    public static void main(String[] args) {
        System.out.println("=== Тестирование конструкторов и toString() ===");
        Rational r1 = new Rational(2, 4); // Должно сократиться до 1/2
        Rational r2 = new Rational("-6/-8"); // Парсинг из строки, должно стать 3/4
        Rational r3 = new Rational("5"); // Целое число, должно стать 5/1

        System.out.println("r1 (2/4) -> " + r1);
        System.out.println("r2 ('-6/-8') -> " + r2);
        System.out.println("r3 ('5') -> " + r3);

        System.out.println("\n=== Тестирование арифметических операций ===");
        System.out.println("r1 + r2: " + r1 + " + " + r2 + " = " + r1.add(r2));
        System.out.println("r2 - r1: " + r2 + " - " + r1 + " = " + r2.subtract(r1));
        System.out.println("r1 * r2: " + r1 + " * " + r2 + " = " + r1.multiply(r2));
        System.out.println("r2 / r1: " + r2 + " / " + r1 + " = " + r2.divide(r1));

        System.out.println("\n=== Тестирование Iterable (Итератор по полям) ===");
        System.out.print("Поля объекта r2 (" + r2 + "): ");
        for (Integer field : r2) {
            System.out.print(field + " ");
        }
        System.out.println();

        System.out.println("\n=== Тестирование обработки исключений и assert ===");
        try {
            Rational fail = new Rational(1, 0);
        } catch (IllegalArgumentException e) {
            System.out.println("Успешно перехвачено исключение при создании 1/0: " + e.getMessage());
        }

        try {
            r1.divide(new Rational(0, 1));
        } catch (IllegalArgumentException e) {
            System.out.println("Успешно перехвачено исключение при делении на 0: " + e.getMessage());
        }

        System.out.println("\n=== Тестирование сортировки массива ===");
        Rational[] array = {
            new Rational(3, 4),
            new Rational(1, 2),
            new Rational(7, 8),
            new Rational(1, 3),
            new Rational(5, 6)
        };

        System.out.println("Исходный массив: " + Arrays.toString(array));

        // Сортировка через Comparable (Естественная по значению дроби)
        Arrays.sort(array);
        System.out.println("Отсортировано по значению (Comparable): " + Arrays.toString(array));

        // Сортировка через Comparator по числителю
        Arrays.sort(array, new Rational.FieldComparator(Rational.SortField.NUMERATOR));
        System.out.println("Отсортировано по числителю (Comparator): " + Arrays.toString(array));

        // Сортировка через Comparator по знаменателю
        Arrays.sort(array, new Rational.FieldComparator(Rational.SortField.DENOMINATOR));
        System.out.println("Отсортировано по знаменателю (Comparator): " + Arrays.toString(array));
    }
}