package by.bsu.tiokrs.lab5.geometry;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class QuadrilateralTest {
    private static final double EPS = 1e-9;

    private static Point2D translate(Point2D p, double dx, double dy) {
        return new Point2D(p.x() + dx, p.y() + dy);
    }

    private static Point2D rotate(Point2D p, double angleRad) {
        double ca = Math.cos(angleRad);
        double sa = Math.sin(angleRad);
        return new Point2D(p.x() * ca - p.y() * sa, p.x() * sa + p.y() * ca);
    }

    @Test
    void squareAreaAndPerimeter() {
        Quadrilateral q = new Quadrilateral(
                new Point2D(0, 0),
                new Point2D(2, 0),
                new Point2D(2, 2),
                new Point2D(0, 2)
        );

        assertEquals(8.0, q.perimeter(), 1e-12);
        assertEquals(4.0, q.area(), 1e-12);
        assertEquals(QuadrilateralType.SQUARE, q.type());
    }

    @Test
    void squareRotatedStillSquare() {
        double angle = Math.PI / 4.0;
        Point2D a = rotate(new Point2D(0, 0), angle);
        Point2D b = rotate(new Point2D(2, 0), angle);
        Point2D c = rotate(new Point2D(2, 2), angle);
        Point2D d = rotate(new Point2D(0, 2), angle);

        Quadrilateral q = new Quadrilateral(a, b, c, d);
        assertEquals(4.0, q.area(), 1e-9);
        assertEquals(8.0, q.perimeter(), 1e-9);
        assertEquals(QuadrilateralType.SQUARE, q.type());
    }

    @Test
    void rectangleDetectedButNotSquare() {
        Quadrilateral q = new Quadrilateral(
                new Point2D(0, 0),
                new Point2D(3, 0),
                new Point2D(3, 2),
                new Point2D(0, 2)
        );
        assertEquals(10.0, q.perimeter(), 1e-12);
        assertEquals(6.0, q.area(), 1e-12);
        assertEquals(QuadrilateralType.RECTANGLE, q.type());
    }

    @Test
    void rectangleRotatedStillRectangle() {
        double angle = 0.37;
        Point2D a = rotate(new Point2D(0, 0), angle);
        Point2D b = rotate(new Point2D(3, 0), angle);
        Point2D c = rotate(new Point2D(3, 2), angle);
        Point2D d = rotate(new Point2D(0, 2), angle);

        Quadrilateral q = new Quadrilateral(a, b, c, d);
        assertEquals(6.0, q.area(), 1e-9);
        assertEquals(10.0, q.perimeter(), 1e-9);
        assertEquals(QuadrilateralType.RECTANGLE, q.type());
    }

    @Test
    void rhombusDetectedButNotRectangle() {
        // Rhombus with side=5: points (0,0), (4,3), (8,0), (4,-3)
        Quadrilateral q = new Quadrilateral(
                new Point2D(0, 0),
                new Point2D(4, 3),
                new Point2D(8, 0),
                new Point2D(4, -3)
        );

        assertEquals(20.0, q.perimeter(), 1e-12);
        assertEquals(24.0, q.area(), 1e-12);
        assertEquals(QuadrilateralType.RHOMBUS, q.type());
    }

    @Test
    void rhombusRotatedStillRhombus() {
        double angle = 0.9;
        Point2D a = rotate(new Point2D(0, 0), angle);
        Point2D b = rotate(new Point2D(4, 3), angle);
        Point2D c = rotate(new Point2D(8, 0), angle);
        Point2D d = rotate(new Point2D(4, -3), angle);

        Quadrilateral q = new Quadrilateral(a, b, c, d);
        assertEquals(24.0, q.area(), 1e-8);
        assertEquals(20.0, q.perimeter(), 1e-8);
        assertEquals(QuadrilateralType.RHOMBUS, q.type());
    }

    @Test
    void arbitraryQuadrilateral() {
        Quadrilateral q = new Quadrilateral(
                new Point2D(0, 0),
                new Point2D(4, 1),
                new Point2D(3, 5),
                new Point2D(-1, 3)
        );
        assertEquals(QuadrilateralType.ARBITRARY, q.type());
        assertTrue(q.area() > EPS);
        assertTrue(q.perimeter() > EPS);
    }

    @Test
    void translationDoesNotChangeAreaOrPerimeterOrType() {
        Quadrilateral q1 = new Quadrilateral(
                new Point2D(0, 0),
                new Point2D(4, 1),
                new Point2D(3, 5),
                new Point2D(-1, 3)
        );
        double dx = 10.25;
        double dy = -7.75;
        Quadrilateral q2 = new Quadrilateral(
                translate(q1.a(), dx, dy),
                translate(q1.b(), dx, dy),
                translate(q1.c(), dx, dy),
                translate(q1.d(), dx, dy)
        );
        assertEquals(q1.area(), q2.area(), 1e-9);
        assertEquals(q1.perimeter(), q2.perimeter(), 1e-9);
        assertEquals(q1.type(), q2.type());
    }

    @Test
    void reversingVertexOrderKeepsAreaAndPerimeter() {
        Quadrilateral q1 = new Quadrilateral(
                new Point2D(0, 0),
                new Point2D(3, 0),
                new Point2D(3, 2),
                new Point2D(0, 2)
        );
        Quadrilateral q2 = new Quadrilateral(q1.a(), q1.d(), q1.c(), q1.b());
        assertEquals(q1.area(), q2.area(), 1e-12);
        assertEquals(q1.perimeter(), q2.perimeter(), 1e-12);
        assertEquals(q1.type(), q2.type());
    }

    @Test
    void concaveQuadrilateralIsArbitrary() {
        // Simple concave quadrilateral
        Quadrilateral q = new Quadrilateral(
                new Point2D(0, 0),
                new Point2D(4, 0),
                new Point2D(1, 1),
                new Point2D(0, 3)
        );
        assertEquals(QuadrilateralType.ARBITRARY, q.type());
    }

    @Test
    void parallelogramButNotRectangleOrRhombusIsArbitrary() {
        // Parallelogram: (0,0)->(4,0)->(6,2)->(2,2)
        Quadrilateral q = new Quadrilateral(
                new Point2D(0, 0),
                new Point2D(4, 0),
                new Point2D(6, 2),
                new Point2D(2, 2)
        );
        assertEquals(QuadrilateralType.ARBITRARY, q.type());
        assertEquals(8.0, q.area(), 1e-12);
    }

    @Test
    void kiteIsArbitrary() {
        Quadrilateral q = new Quadrilateral(
                new Point2D(0, 0),
                new Point2D(2, 1),
                new Point2D(0, 4),
                new Point2D(-2, 1)
        );
        assertEquals(QuadrilateralType.ARBITRARY, q.type());
        assertTrue(q.area() > EPS);
    }

    @Test
    void rejectsNonFinitePointCoordinates() {
        assertThrows(IllegalArgumentException.class, () -> new Point2D(Double.NaN, 0.0));
        assertThrows(IllegalArgumentException.class, () -> new Point2D(0.0, Double.POSITIVE_INFINITY));
    }

    @Test
    void rejectsNullVertices() {
        assertThrows(NullPointerException.class, () -> new Quadrilateral(
                new Point2D(0, 0),
                null,
                new Point2D(1, 1),
                new Point2D(0, 1)
        ));
    }

    @Test
    void arrayConstructorCreatesEquivalentQuadrilateral() {
        Quadrilateral q = new Quadrilateral(new Point2D[]{
                new Point2D(0, 0),
                new Point2D(2, 0),
                new Point2D(2, 2),
                new Point2D(0, 2)
        });

        assertEquals(4.0, q.area(), 1e-12);
        assertEquals(8.0, q.perimeter(), 1e-12);
        assertEquals(QuadrilateralType.SQUARE, q.type());
    }

    @Test
    void coordinateConstructorCreatesEquivalentQuadrilateral() {
        Quadrilateral q = new Quadrilateral(0, 0, 3, 0, 3, 2, 0, 2);

        assertEquals(6.0, q.area(), 1e-12);
        assertEquals(10.0, q.perimeter(), 1e-12);
        assertEquals(QuadrilateralType.RECTANGLE, q.type());
    }

    @Test
    void verticesMethodReturnsAllVerticesInOriginalOrder() {
        Quadrilateral q = new Quadrilateral(0, 0, 3, 0, 3, 2, 0, 2);

        Point2D[] vertices = q.vertices();
        assertEquals(4, vertices.length);
        assertEquals(0.0, vertices[0].x(), 1e-12);
        assertEquals(0.0, vertices[0].y(), 1e-12);
        assertEquals(0.0, vertices[3].x(), 1e-12);
        assertEquals(2.0, vertices[3].y(), 1e-12);
    }

    @Test
    void rejectsDuplicateVertices() {
        assertThrows(IllegalArgumentException.class, () -> new Quadrilateral(
                new Point2D(0, 0),
                new Point2D(1, 0),
                new Point2D(1, 0),
                new Point2D(0, 1)
        ));
    }

    @Test
    void rejectsWrongVertexCountInArrayConstructor() {
        assertThrows(IllegalArgumentException.class, () -> new Quadrilateral(new Point2D[]{
                new Point2D(0, 0),
                new Point2D(1, 0),
                new Point2D(1, 1)
        }));
    }

    @Test
    void rejectsSelfIntersectingQuadrilateral() {
        // Bow-tie: edges cross
        assertThrows(IllegalArgumentException.class, () -> new Quadrilateral(
                new Point2D(0, 0),
                new Point2D(2, 2),
                new Point2D(0, 2),
                new Point2D(2, 0)
        ));
    }

    @Test
    void rejectsCrossedOrderOfRectangleVertices() {
        // Same rectangle vertices, but with a crossed order.
        assertThrows(IllegalArgumentException.class, () -> new Quadrilateral(
                new Point2D(0, 0),
                new Point2D(3, 2),
                new Point2D(3, 0),
                new Point2D(0, 2)
        ));
    }

    @Test
    void rejectsZeroArea() {
        // All points collinear
        assertThrows(IllegalArgumentException.class, () -> new Quadrilateral(
                new Point2D(0, 0),
                new Point2D(1, 0),
                new Point2D(2, 0),
                new Point2D(3, 0)
        ));
    }
}
