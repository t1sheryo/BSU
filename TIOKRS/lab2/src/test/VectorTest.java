package test;

import util.Vector;
import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.*;

/**
 * Класс для тестирования функциональности класса Vector.
 * Содержит позитивные и негативные тесты для всех public и protected методов.
 *
 * @version 1.0
 * @author Timofey Cheberuk
 */
public class VectorTest {

    // ===================== ПОДГОТОВКА К ТЕСТАМ =====================

    private Vector v1;
    private Vector v2;
    private Vector v3;
    private Vector zero;
    private Vector negative;

    @BeforeEach
    void setUp() {
        // Инициализация векторов перед каждым тестом
        v1 = new Vector(1, 2, 3);
        v2 = new Vector(4, 5, 6);
        v3 = new Vector(1, 1, 1);
        zero = new Vector(0, 0, 0);
        negative = new Vector(-1, -2, -3);
    }

    // ===================== ТЕСТЫ ГЕТТЕРОВ =====================

    /**
     * Позитивный тест геттера getX.
     */
    @Test
    @DisplayName("Позитивный тест getX")
    void testGetX() {
        assertEquals(1.0, v1.getX(), "X координата должна быть 1.0");
        assertEquals(4.0, v2.getX(), "X координата должна быть 4.0");
        assertEquals(0.0, zero.getX(), "X координата нулевого вектора должна быть 0.0");
        assertEquals(-1.0, negative.getX(), "X координата должна быть -1.0");
    }

    /**
     * Позитивный тест геттера getY.
     */
    @Test
    @DisplayName("Позитивный тест getY")
    void testGetY() {
        assertEquals(2.0, v1.getY(), "Y координата должна быть 2.0");
        assertEquals(5.0, v2.getY(), "Y координата должна быть 5.0");
        assertEquals(0.0, zero.getY(), "Y координата нулевого вектора должна быть 0.0");
        assertEquals(-2.0, negative.getY(), "Y координата должна быть -2.0");
    }

    /**
     * Позитивный тест геттера getZ.
     */
    @Test
    @DisplayName("Позитивный тест getZ")
    void testGetZ() {
        assertEquals(3.0, v1.getZ(), "Z координата должна быть 3.0");
        assertEquals(6.0, v2.getZ(), "Z координата должна быть 6.0");
        assertEquals(0.0, zero.getZ(), "Z координата нулевого вектора должна быть 0.0");
        assertEquals(-3.0, negative.getZ(), "Z координата должна быть -3.0");
    }

    /**
     * Позитивный тест геттера getCoordinates.
     */
    @Test
    @DisplayName("Позитивный тест getCoordinates")
    void testGetCoordinates() {
        double[] coords1 = v1.getCoordinates();
        assertArrayEquals(new double[]{1.0, 2.0, 3.0}, coords1, 0.0001);

        double[] coords2 = v2.getCoordinates();
        assertArrayEquals(new double[]{4.0, 5.0, 6.0}, coords2, 0.0001);

        double[] coordsZero = zero.getCoordinates();
        assertArrayEquals(new double[]{0.0, 0.0, 0.0}, coordsZero, 0.0001);

        // Проверка на создание копии (не возвращать ссылку на внутренний массив)
        double[] coords = v1.getCoordinates();
        coords[0] = 999; // Изменяем полученный массив
        assertEquals(1.0, v1.getX(), "Оригинальный вектор не должен измениться");
    }

    // ===================== ТЕСТЫ КОНСТРУКТОРОВ =====================

    /**
     * Позитивный тест конструктора с тремя параметрами.
     * Проверяет создание вектора с корректными координатами.
     */
    @Test
    @DisplayName("Позитивный тест конструктора с тремя параметрами")
    void testConstructorWithThreeParamsPositive() {
        Vector vector = new Vector(2.5, -3.7, 4.1);
        assertEquals(2.5, vector.getX(), "X координата должна быть 2.5");
        assertEquals(-3.7, vector.getY(), "Y координата должна быть -3.7");
        assertEquals(4.1, vector.getZ(), "Z координата должна быть 4.1");
    }

    /**
     * Позитивный тест конструктора с массивом.
     * Проверяет создание вектора из корректного массива.
     */
    @Test
    @DisplayName("Позитивный тест конструктора с массивом")
    void testConstructorWithArrayPositive() {
        double[] coords = {2.5, -3.7, 4.1};
        Vector vector = new Vector(coords);
        assertEquals(2.5, vector.getX(), "X координата должна быть 2.5");
        assertEquals(-3.7, vector.getY(), "Y координата должна быть -3.7");
        assertEquals(4.1, vector.getZ(), "Z координата должна быть 4.1");
    }

    /**
     * Негативный тест конструктора с массивом.
     * Проверяет выброс исключения при неверной длине массива.
     */
    @Test
    @DisplayName("Негативный тест конструктора с массивом - неверная длина")
    void testConstructorWithArrayNegative() {
        double[] shortArray = {1, 2};
        double[] longArray = {1, 2, 3, 4};

        assertThrows(IllegalArgumentException.class, () -> new Vector(shortArray),
                "Должно быть исключение при массиве из 2 элементов");

        assertThrows(IllegalArgumentException.class, () -> new Vector(longArray),
                "Должно быть исключение при массиве из 4 элементов");

        assertThrows(NullPointerException.class, () -> new Vector((double[]) null),
                "Должно быть исключение при передаче null");
    }

    // ===================== ТЕСТЫ МЕТОДА ADD =====================

    /**
     * Позитивный тест метода add.
     * Проверяет сложение векторов с положительными координатами.
     */
    @Test
    @DisplayName("Позитивный тест add - положительные координаты")
    void testAddPositive() {
        Vector result = v1.add(v2);
        assertEquals(5, result.getX(), "1+4 = 5");
        assertEquals(7, result.getY(), "2+5 = 7");
        assertEquals(9, result.getZ(), "3+6 = 9");
    }

    /**
     * Позитивный тест метода add.
     * Проверяет сложение с нулевым вектором.
     */
    @Test
    @DisplayName("Позитивный тест add - с нулевым вектором")
    void testAddWithZero() {
        Vector result = v1.add(zero);
        assertEquals(v1.getX(), result.getX(), "1+0 = 1");
        assertEquals(v1.getY(), result.getY(), "2+0 = 2");
        assertEquals(v1.getZ(), result.getZ(), "3+0 = 3");
    }

    /**
     * Позитивный тест метода add.
     * Проверяет сложение с отрицательными координатами.
     */
    @Test
    @DisplayName("Позитивный тест add - с отрицательными координатами")
    void testAddWithNegative() {
        Vector result = v1.add(negative);
        assertEquals(0, result.getX(), "1 + (-1) = 0");
        assertEquals(0, result.getY(), "2 + (-2) = 0");
        assertEquals(0, result.getZ(), "3 + (-3) = 0");
    }

    /**
     * Негативный тест метода add.
     * Проверяет обработку null.
     */
    @Test
    @DisplayName("Негативный тест add - передача null")
    void testAddWithNull() {
        assertThrows(NullPointerException.class, () -> v1.add(null),
                "Должно быть исключение при передаче null");
    }

    // ===================== ТЕСТЫ МЕТОДА SUBTRACT =====================

    /**
     * Позитивный тест метода subtract.
     * Проверяет вычитание векторов.
     */
    @Test
    @DisplayName("Позитивный тест subtract")
    void testSubtractPositive() {
        Vector result = v2.subtract(v1);
        assertEquals(3, result.getX(), "4-1 = 3");
        assertEquals(3, result.getY(), "5-2 = 3");
        assertEquals(3, result.getZ(), "6-3 = 3");
    }

    /**
     * Позитивный тест метода subtract.
     * Проверяет вычитание самого себя (получаем нулевой вектор).
     */
    @Test
    @DisplayName("Позитивный тест subtract - вычитание самого себя")
    void testSubtractSelf() {
        Vector result = v1.subtract(v1);
        assertEquals(0, result.getX(), "1-1 = 0");
        assertEquals(0, result.getY(), "2-2 = 0");
        assertEquals(0, result.getZ(), "3-3 = 0");
    }

    // ===================== ТЕСТЫ СКАЛЯРНОГО ПРОИЗВЕДЕНИЯ =====================

    /**
     * Позитивный тест скалярного произведения.
     */
    @Test
    @DisplayName("Позитивный тест скалярного произведения")
    void testScalarMultiplicationPositive() {
        double result = v1.scalarMultiplication(v2);
        assertEquals(32, result, "1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32");

        result = v1.scalarMultiplication(v3);
        assertEquals(6, result, "1*1 + 2*1 + 3*1 = 6");
    }

    /**
     * Позитивный тест скалярного произведения с нулевым вектором.
     */
    @Test
    @DisplayName("Позитивный тест скалярного произведения с нулевым вектором")
    void testScalarMultiplicationWithZero() {
        double result = v1.scalarMultiplication(zero);
        assertEquals(0, result, "Скалярное произведение с нулевым вектором = 0");
    }

    /**
     * Позитивный тест скалярного произведения с ортогональными векторами.
     */
    @Test
    @DisplayName("Позитивный тест скалярного произведения - ортогональные векторы")
    void testScalarMultiplicationOrthogonal() {
        Vector vX = new Vector(1, 0, 0);
        Vector vY = new Vector(0, 1, 0);
        Vector vZ = new Vector(0, 0, 1);

        assertEquals(0, vX.scalarMultiplication(vY), "X·Y = 0");
        assertEquals(0, vX.scalarMultiplication(vZ), "X·Z = 0");
        assertEquals(0, vY.scalarMultiplication(vZ), "Y·Z = 0");
    }

    // ===================== ТЕСТЫ ВЕКТОРНОГО ПРОИЗВЕДЕНИЯ =====================

    /**
     * Позитивный тест векторного произведения.
     */
    @Test
    @DisplayName("Позитивный тест векторного произведения")
    void testVectorMultiplicationPositive() {
        // (1,2,3) × (4,5,6)
        Vector result = v1.vectorMultiplication(v2);
        assertEquals(-3, result.getX(), "2*6 - 3*5 = 12 - 15 = -3");
        assertEquals(6, result.getY(), "3*4 - 1*6 = 12 - 6 = 6");
        assertEquals(-3, result.getZ(), "1*5 - 2*4 = 5 - 8 = -3");
    }

    /**
     * Позитивный тест векторного произведения - результат перпендикулярен исходным.
     */
    @Test
    @DisplayName("Позитивный тест векторного произведения - перпендикулярность")
    void testVectorMultiplicationPerpendicular() {
        Vector vX = new Vector(1, 0, 0);
        Vector vY = new Vector(0, 1, 0);

        Vector result = vX.vectorMultiplication(vY);
        assertEquals(0, result.getX(), "X-компонента");
        assertEquals(0, result.getY(), "Y-компонента");
        assertEquals(1, result.getZ(), "Z-компонента - должен быть (0,0,1)");

        // Проверка перпендикулярности через скалярное произведение
        assertEquals(0, result.scalarMultiplication(vX), "Результат перпендикулярен X");
        assertEquals(0, result.scalarMultiplication(vY), "Результат перпендикулярен Y");
    }

    /**
     * Позитивный тест векторного произведения коллинеарных векторов.
     */
    @Test
    @DisplayName("Позитивный тест векторного произведения коллинеарных векторов")
    void testVectorMultiplicationCollinear() {
        Vector v2x = new Vector(2, 4, 6); // 2 * v1

        Vector result = v1.vectorMultiplication(v2x);
        assertEquals(0, result.getX(), "Для коллинеарных векторов результат = 0");
        assertEquals(0, result.getY(), "Для коллинеарных векторов результат = 0");
        assertEquals(0, result.getZ(), "Для коллинеарных векторов результат = 0");
    }

    // ===================== ТЕСТЫ МЕТОДА EQUALS =====================

    /**
     * Позитивный тест equals - равные векторы.
     */
    @Test
    @DisplayName("Позитивный тест equals - равные векторы")
    void testEqualsPositive() {
        Vector v1Copy = new Vector(1, 2, 3);
        assertTrue(v1.equals(v1Copy), "Векторы с одинаковыми координатами должны быть равны");
        assertTrue(v1.equals(v1), "Вектор должен быть равен самому себе");
    }

    /**
     * Негативный тест equals - неравные векторы.
     */
    @Test
    @DisplayName("Негативный тест equals - неравные векторы")
    void testEqualsNegative() {
        assertFalse(v1.equals(v2), "Векторы с разными координатами не должны быть равны");
        assertFalse(v1.equals(zero), "Вектор не равен нулевому вектору");
    }

    /**
     * Негативный тест equals - сравнение с null.
     */
    @Test
    @DisplayName("Негативный тест equals - сравнение с null")
    void testEqualsWithNull() {
        assertFalse(v1.equals(null), "Сравнение с null должно вернуть false");
    }

    // ===================== ТЕСТЫ МЕТОДА TOSTRING =====================

    /**
     * Позитивный тест toString.
     */
    @Test
    @DisplayName("Позитивный тест toString")
    void testToStringPositive() {
        assertEquals("Vector(1.0, 2.0, 3.0)", v1.toString());
        assertEquals("Vector(0.0, 0.0, 0.0)", zero.toString());
        assertEquals("Vector(-1.0, -2.0, -3.0)", negative.toString());
    }

    // ===================== ТЕСТЫ МЕТОДА ARE_COPLANAR =====================

    /**
     * Позитивный тест areCoplanar - компланарные векторы.
     */
    @Test
    @DisplayName("Позитивный тест areCoplanar - компланарные векторы")
    void testAreCoplanarPositive() {
        // Векторы, лежащие в одной плоскости
        Vector a = new Vector(1, 0, 0);
        Vector b = new Vector(0, 1, 0);
        Vector c = new Vector(1, 1, 0); // в той же плоскости XY

        assertTrue(Vector.areCoplanar(a, b, c),
                "Векторы в плоскости XY должны быть компланарны");
    }

    /**
     * Негативный тест areCoplanar - некомпланарные векторы.
     */
    @Test
    @DisplayName("Негативный тест areCoplanar - некомпланарные векторы")
    void testAreCoplanarNegative() {
        Vector a = new Vector(1, 0, 0);
        Vector b = new Vector(0, 1, 0);
        Vector c = new Vector(0, 0, 1); // базисные векторы - не компланарны

        assertFalse(Vector.areCoplanar(a, b, c),
                "Базисные векторы не должны быть компланарны");
    }

    /**
     * Граничный тест areCoplanar - с нулевыми векторами.
     */
    @Test
    @DisplayName("Граничный тест areCoplanar - с нулевыми векторами")
    void testAreCoplanarWithZero() {
        // Любые два вектора с нулевым третьим - компланарны
        assertTrue(Vector.areCoplanar(v1, v2, zero),
                "С нулевым вектором всегда компланарны");

        // Нулевой вектор с любыми двумя
        assertTrue(Vector.areCoplanar(zero, v1, v2),
                "С нулевым вектором всегда компланарны");
    }

    /**
     * Граничный тест areCoplanar - с очень малыми значениями (проверка точности).
     */
    @Test
    @DisplayName("Граничный тест areCoplanar - проверка точности вычислений")
    void testAreCoplanarPrecision() {
        Vector a = new Vector(1, 0, 0);
        Vector b = new Vector(0, 1, 0);
        Vector almostInPlane = new Vector(1, 1, 1e-11); // очень близко к плоскости

        assertTrue(Vector.areCoplanar(a, b, almostInPlane),
                "Должно работать с погрешностью 1e-10");
    }

    // ===================== ТЕСТЫ ДОПОЛНИТЕЛЬНЫХ СИТУАЦИЙ =====================

    /**
     * Тест на неизменяемость объектов (immutable).
     */
    @Test
    @DisplayName("Тест на неизменяемость объектов")
    void testImmutability() {
        Vector original = new Vector(1, 2, 3);
        Vector result = original.add(new Vector(1, 1, 1));

        // Оригинал не должен измениться
        assertEquals(1, original.getX());
        assertEquals(2, original.getY());
        assertEquals(3, original.getZ());

        // Результат - новый объект
        assertNotSame(original, result);
    }

    /**
     * Тест работы с большими числами.
     */
    @Test
    @DisplayName("Тест работы с большими числами")
    void testLargeNumbers() {
        Vector large1 = new Vector(1e6, 1e6, 1e6);
        Vector large2 = new Vector(1e6, 1e6, 1e6);

        Vector sum = large1.add(large2);
        assertEquals(2e6, sum.getX(), 0.001);
        assertEquals(2e6, sum.getY(), 0.001);
        assertEquals(2e6, sum.getZ(), 0.001);
    }

    /**
     * Тест работы с очень малыми числами.
     */
    @Test
    @DisplayName("Тест работы с очень малыми числами")
    void testSmallNumbers() {
        Vector small1 = new Vector(1e-10, 1e-10, 1e-10);
        Vector small2 = new Vector(1e-10, 1e-10, 1e-10);

        Vector sum = small1.add(small2);
        assertEquals(2e-10, sum.getX(), 1e-20);
        assertEquals(2e-10, sum.getY(), 1e-20);
        assertEquals(2e-10, sum.getZ(), 1e-20);
    }
}