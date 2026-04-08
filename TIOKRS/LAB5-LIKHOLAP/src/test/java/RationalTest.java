

import math.Time;
import math.Data;

/**
 * Модульные тесты (10 сценариев), разработанные по методике TDD.
 */
public class RationalTest {
    public static void main(String[] args) {
        System.out.println("Запуск 10 модульных тестов (TDD)...\n");

        runPositiveTests();
        runNegativeTests();

        System.out.println("\nВсе тесты успешно пройдены!");
    }

    private static void runPositiveTests() {
        // 1. Создание времени
        Time t = new Time(14, 5, 1);
        assert t.toString().equals("14:05:01");

        // 2. Сложение времени
        assert t.add(60).toString().equals("14:06:01");

        // 3. Сравнение времени
        assert t.compareTo(new Time(15, 0, 0)) < 0;

        // 4. Создание даты
        Data d = new Data(1, 1, 2026);
        assert d.toString().equals("01-01-2026");

        // 5. Сравнение дат
        assert d.compareTo(new Data(1, 1, 2025)) > 0;

        System.out.println("Позитивные тесты (1-5): OK");
    }

    private static void runNegativeTests() {
        // 6. Неверные часы (25)
        try { new Time(25, 0, 0); assert false; } catch (IllegalArgumentException e) {}

        // 7. Отрицательные минуты
        try { new Time(10, -5, 0); assert false; } catch (IllegalArgumentException e) {}

        // 8. Неверный месяц (13)
        try { new Data(1, 13, 2026); assert false; } catch (IllegalArgumentException e) {}

        // 9. Нулевой день
        try { new Data(0, 1, 2026); assert false; } catch (IllegalArgumentException e) {}

        // 10. Некорректные секунды (60)
        try { new Time(10, 10, 60); assert false; } catch (IllegalArgumentException e) {}

        System.out.println("Негативные тесты (6-10): OK");
    }
}