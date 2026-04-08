package test;

import util.Main;
import org.junit.jupiter.api.*;

import java.io.*;
import static org.junit.jupiter.api.Assertions.*;

/**
 * Класс для тестирования класса util.Main.
 * Тестирует метод main на корректный вывод.
 *
 * @version 1.0
 * @author Timofey Cheberuk
 */
public class MainTest {

    private final PrintStream standardOut = System.out;
    private final ByteArrayOutputStream outputStreamCaptor = new ByteArrayOutputStream();

    @BeforeEach
    void setUp() {
        // Перенаправляем System.out для захвата вывода
        System.setOut(new PrintStream(outputStreamCaptor));
    }

    @AfterEach
    void tearDown() {
        // Возвращаем стандартный вывод
        System.setOut(standardOut);
    }

    /**
     * Позитивный тест метода main.
     * Проверяет, что программа выводит ожидаемый результат.
     */
    @Test
    @DisplayName("Позитивный тест main - проверка вывода")
    void testMainPositive() {
        // Вызываем main метод
        Main.main(new String[]{});

        // Получаем вывод
        String output = outputStreamCaptor.toString().trim();

        // Проверяем, что вывод содержит ожидаемые строки
        assertTrue(output.contains("Vectors:"),
                "Вывод должен содержать 'Vectors:'");

        assertTrue(output.contains("Vector(1.0, 2.0, 3.0)"),
                "Вывод должен содержать первый вектор");

        assertTrue(output.contains("Vector(4.0, 4.0, 6.0)"),
                "Вывод должен содержать второй вектор");

        assertTrue(output.contains("Vector(1.0, 1.0, 1.0)"),
                "Вывод должен содержать третий вектор");

        assertTrue(output.contains("Vectors complanar: true"),
                "Вывод должен содержать результат проверки компланарности");
    }

    /**
     * Позитивный тест main с аргументами командной строки.
     * Проверяет, что программа игнорирует аргументы.
     */
    @Test
    @DisplayName("Позитивный тест main с аргументами")
    void testMainWithArguments() {
        // Вызываем main с аргументами
        util.Main.main(new String[]{"arg1", "arg2", "arg3"});

        // Получаем вывод
        String output = outputStreamCaptor.toString().trim();

        // Вывод должен быть таким же, как и без аргументов
        assertTrue(output.contains("Vectors:"));
        assertTrue(output.contains("Vector(1.0, 2.0, 3.0)"));
        assertTrue(output.contains("Vectors complanar: true"));
    }

    /**
     * Негативный тест - проверка, что программа не падает с ошибкой.
     * Фактически это позитивный тест стабильности.
     */
    @Test
    @DisplayName("Тест стабильности программы")
    void testProgramStability() {
        assertDoesNotThrow(() -> util.Main.main(new String[]{}),
                "Программа не должна выбрасывать исключения");

        assertDoesNotThrow(() -> util.Main.main(new String[]{"test"}),
                "Программа не должна падать с аргументами");

        assertDoesNotThrow(() -> util.Main.main(null),
                "Программа не должна падать с null аргументами");
    }

    /**
     * Тест формата вывода.
     */
    @Test
    @DisplayName("Тест формата вывода")
    void testOutputFormat() {
        util.Main.main(new String[]{});
        String output = outputStreamCaptor.toString();

        // Проверяем, что каждый вектор на отдельной строке
        String[] lines = output.split("\\r?\\n");

        assertEquals(5, lines.length, "Должно быть 5 строк вывода");
        assertEquals("Vectors:", lines[0].trim());
        assertTrue(lines[1].trim().startsWith("Vector("));
        assertTrue(lines[2].trim().startsWith("Vector("));
        assertTrue(lines[3].trim().startsWith("Vector("));
        assertTrue(lines[4].trim().startsWith("Vectors complanar:"));
    }
}