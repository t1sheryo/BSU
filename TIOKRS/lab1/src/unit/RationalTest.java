package unit;

import math.Rational;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import java.util.Iterator;
import java.util.NoSuchElementException;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Модульные тесты для класса Rational с использованием JUnit 5.
 *
 * @author Fiodor Likholap
 * @version 2.0
 */
class RationalTest {

    private Rational half;
    private Rational threeQuarters;
    private Rational five;

    @BeforeEach
    void setUp() {
        half = new Rational(1, 2);
        threeQuarters = new Rational("3/4");
        five = new Rational("5");
    }

    // ==================== ПОЗИТИВНЫЕ ТЕСТЫ ====================

    @Test
    @DisplayName("Конструктор (числитель, знаменатель)")
    void testConstructorWithNumeratorDenominator() {
        assertEquals("1/2", half.toString());
        assertEquals("3/4", threeQuarters.toString());
        assertEquals("5", five.toString());
    }

    @Test
    @DisplayName("Конструктор из строки")
    void testConstructorFromString() {
        Rational r1 = new Rational("2/3");
        Rational r2 = new Rational("7");
        assertEquals("2/3", r1.toString());
        assertEquals("7", r2.toString());
    }

    @Test
    @DisplayName("Конструктор из целого числа")
    void testConstructorFromInt() {
        Rational r = new Rational("10");
        assertEquals("10", r.toString());
    }

    @Test
    @DisplayName("Сложение дробей")
    void testAddition() {
        Rational result = half.add(threeQuarters);
        assertEquals("5/4", result.toString());
    }

    @Test
    @DisplayName("Вычитание дробей")
    void testSubtraction() {
        Rational result = threeQuarters.subtract(half);
        assertEquals("1/4", result.toString());
    }

    @Test
    @DisplayName("Умножение дробей")
    void testMultiplication() {
        Rational result = half.multiply(threeQuarters);
        assertEquals("3/8", result.toString());
    }

    @Test
    @DisplayName("Деление дробей")
    void testDivision() {
        Rational result = threeQuarters.divide(half);
        assertEquals("3/2", result.toString());
    }

    @Test
    @DisplayName("Сравнение (Comparable) - меньше")
    void testCompareToLess() {
        assertTrue(half.compareTo(threeQuarters) < 0);
    }

    @Test
    @DisplayName("Сравнение (Comparable) - больше")
    void testCompareToGreater() {
        assertTrue(threeQuarters.compareTo(half) > 0);
    }

    @Test
    @DisplayName("Сравнение (Comparable) - равно")
    void testCompareToEqual() {
        assertEquals(0, half.compareTo(new Rational(1, 2)));
    }

    @Test
    @DisplayName("Итератор - последовательный обход")
    void testIterator() {
        Iterator<Integer> it = half.iterator();
        assertTrue(it.hasNext());
        assertEquals(1, it.next());
        assertTrue(it.hasNext());
        assertEquals(2, it.next());
        assertFalse(it.hasNext());
    }

    @Test
    @DisplayName("Сокращение дроби")
    void testFractionReduction() {
        Rational r = new Rational(10, 20);
        assertEquals("1/2", r.toString());
    }

    @Test
    @DisplayName("Отрицательная дробь")
    void testNegativeFraction() {
        Rational r = new Rational(-3, 4);
        assertEquals("-3/4", r.toString());
    }

    @Test
    @DisplayName("Дробь с отрицательным знаменателем (нормализация)")
    void testNegativeDenominator() {
        Rational r = new Rational(3, -4);
        assertEquals("-3/4", r.toString());
    }



    // ==================== НЕГАТИВНЫЕ ТЕСТЫ ====================

    @Test
    @DisplayName("Конструктор с нулевым знаменателем - исключение")
    void testZeroDenominatorThrowsException() {
        assertThrows(IllegalArgumentException.class, () -> new Rational(1, 0));
    }

    @Test
    @DisplayName("Деление на ноль - исключение")
    void testDivideByZeroThrowsException() {
        Rational zero = new Rational(0, 1);
        assertThrows(IllegalArgumentException.class, () -> half.divide(zero));
    }

    @ParameterizedTest
    @ValueSource(strings = {"abc", "1/0", "", "1/2/3", "   ", "/5", "1//2", "a/b"})
    @DisplayName("Парсинг некорректных строк - исключение")
    void testInvalidStringParsingThrowsException(String invalidString) {
        assertThrows(IllegalArgumentException.class, () -> new Rational(invalidString));
    }

    @Test
    @DisplayName("Парсинг null строки - исключение")
    void testNullStringThrowsException() {
        assertThrows(IllegalArgumentException.class, () -> new Rational((String) null));
    }

    @Test
    @DisplayName("Итератор - выход за границы вызывает NoSuchElementException")
    void testIteratorOutOfBoundsThrowsException() {
        Iterator<Integer> it = half.iterator();
        it.next(); // числитель
        it.next(); // знаменатель
        assertThrows(NoSuchElementException.class, it::next);
    }



    @Test
    @DisplayName("Сравнение с null - NullPointerException")
    void testCompareToNull() {
        assertThrows(NullPointerException.class, () -> half.compareTo(null));
    }
}