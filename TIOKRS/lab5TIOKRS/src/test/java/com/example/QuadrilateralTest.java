package com.example;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

@TestInstance(TestInstance.Lifecycle.PER_CLASS)
public class QuadrilateralTest {

    // Тестовые данные
    private Quadrilateral square;
    private Quadrilateral rectangle;
    private Quadrilateral rhombus;
    private Quadrilateral general;

    @BeforeEach
    void setUp() {
        // Квадрат
        square = new Quadrilateral(
            new Point(0, 0), new Point(2, 0),
            new Point(2, 2), new Point(0, 2)
        );

        // Прямоугольник
        rectangle = new Quadrilateral(
            new Point(0, 0), new Point(3, 0),
            new Point(3, 2), new Point(0, 2)
        );

        // Ромб
        rhombus = new Quadrilateral(
            new Point(0, 1), new Point(1, 0),
            new Point(2, 1), new Point(1, 2)
        );

        // Произвольный четырехугольник
        general = new Quadrilateral(
            new Point(0, 0), new Point(2, 0),
            new Point(3, 2), new Point(0, 1)
        );
    }

    // === Тесты для конструктора ===
    @Test
    @DisplayName("Constructor should create valid quadrilateral")
    void testConstructorValid() {
        assertDoesNotThrow(() -> new Quadrilateral(
            new Point(0, 0), new Point(1, 0),
            new Point(1, 1), new Point(0, 1)
        ));
    }

    @Test
    @DisplayName("Constructor should throw exception for null points")
    void testConstructorNullPoints() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Quadrilateral(null, new Point(1,0), new Point(1,1), new Point(0,1));
        });

        assertThrows(IllegalArgumentException.class, () -> {
            new Quadrilateral(new Point(0,0), null, new Point(1,1), new Point(0,1));
        });

        assertThrows(IllegalArgumentException.class, () -> {
            new Quadrilateral(new Point(0,0), new Point(1,0), null, new Point(0,1));
        });

        assertThrows(IllegalArgumentException.class, () -> {
            new Quadrilateral(new Point(0,0), new Point(1,0), new Point(1,1), null);
        });

        assertThrows(IllegalArgumentException.class, () -> {
            new Quadrilateral(null, null, null, null);
        });
    }

    @Test
    @DisplayName("Constructor should throw exception for degenerate quadrilateral")
    void testConstructorDegenerate() {

        // Две одинаковые точки
        assertThrows(IllegalArgumentException.class, () -> {
            new Quadrilateral(
                new Point(0, 0), new Point(0, 0),
                new Point(1, 1), new Point(0, 1)
            );
        });
    }

    // === Тесты для perimeter() ===
    @Test
    @DisplayName("Perimeter of square should be 8.0")
    void testPerimeterSquare() {
        assertEquals(8.0, square.perimeter(), 1e-10);
    }

    @Test
    @DisplayName("Perimeter of rectangle should be 10.0")
    void testPerimeterRectangle() {
        assertEquals(10.0, rectangle.perimeter(), 1e-10);
    }

    @Test
    @DisplayName("Perimeter of rhombus should be correct")
    void testPerimeterRhombus() {
        double expected = 4 * Math.sqrt(2); // Сторона = √2
        assertEquals(expected, rhombus.perimeter(), 1e-10);
    }

    // === Тесты для area() ===

    @Test
    @DisplayName("Area of rectangle should be 6.0")
    void testAreaRectangle() {
        assertEquals(6.0, rectangle.area(), 1e-10);
    }

    @Test
    @DisplayName("Area of rhombus should be 2.0")
    void testAreaRhombus() {
        assertEquals(2.0, rhombus.area(), 1e-10);
    }

    // === Тесты для type() ===
    @Test
    @DisplayName("Should identify square correctly")
    void testTypeSquare() {
        assertEquals("Square", square.type());
    }

    @Test
    @DisplayName("Should identify general quadrilateral correctly")
    void testTypeGeneral() {
        assertEquals("General", general.type());
    }

    // === Тесты для методов доступа ===
    @Test
    @DisplayName("getVertices should return copy of vertices")
    void testGetVertices() {
        Point[] vertices = square.getVertices();
        vertices[0] = new Point(10, 10);

        // Оригинальные вершины не должны измениться
        Point[] originalVertices = square.getVertices();
        assertEquals(0.0, originalVertices[0].x, 1e-10);
        assertEquals(0.0, originalVertices[0].y, 1e-10);
    }

    // === Тесты для toString() ===
    @Test
    @DisplayName("toString should contain type, perimeter and area")
    void testToString() {
        String str = square.toString();
        assertTrue(str.contains("Square"));
        assertTrue(str.contains("perimeter=8.00"));
        assertTrue(str.contains("area=4.00"));
    }
}