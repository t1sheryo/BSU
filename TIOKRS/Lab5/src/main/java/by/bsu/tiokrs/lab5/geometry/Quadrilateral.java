package by.bsu.tiokrs.lab5.geometry;

import java.util.Objects;

public final class Quadrilateral {
    private static final double EPS = 1e-9;

    private final Point2D a;
    private final Point2D b;
    private final Point2D c;
    private final Point2D d;

    public Quadrilateral(Point2D[] vertices) {
        this(requireVertex(vertices, 0), requireVertex(vertices, 1), requireVertex(vertices, 2), requireVertex(vertices, 3));
        if (vertices.length != 4) {
            throw new IllegalArgumentException("Quadrilateral must contain exactly 4 vertices");
        }
    }

    public Quadrilateral(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy) {
        this(new Point2D(ax, ay), new Point2D(bx, by), new Point2D(cx, cy), new Point2D(dx, dy));
    }

    public Quadrilateral(Point2D a, Point2D b, Point2D c, Point2D d) {
        this.a = Objects.requireNonNull(a, "a");
        this.b = Objects.requireNonNull(b, "b");
        this.c = Objects.requireNonNull(c, "c");
        this.d = Objects.requireNonNull(d, "d");

        validateDistinctVertices();
        validateSimple();
        if (area() <= EPS) {
            throw new IllegalArgumentException("Quadrilateral area must be positive");
        }
    }

    public Point2D a() {
        return a;
    }

    public Point2D b() {
        return b;
    }

    public Point2D c() {
        return c;
    }

    public Point2D d() {
        return d;
    }

    public Point2D[] vertices() {
        return new Point2D[]{a, b, c, d};
    }

    public double perimeter() {
        return a.distanceTo(b) + b.distanceTo(c) + c.distanceTo(d) + d.distanceTo(a);
    }

    public double area() {
        // Shoelace formula for polygon A->B->C->D
        double s = a.x() * b.y() - a.y() * b.x()
                + b.x() * c.y() - b.y() * c.x()
                + c.x() * d.y() - c.y() * d.x()
                + d.x() * a.y() - d.y() * a.x();
        return Math.abs(s) / 2.0;
    }

    public QuadrilateralType type() {
        if (!isConvex()) {
            return QuadrilateralType.ARBITRARY;
        }

        Vec ab = Vec.from(a, b);
        Vec bc = Vec.from(b, c);
        Vec cd = Vec.from(c, d);
        Vec da = Vec.from(d, a);

        double ab2 = ab.len2();
        double bc2 = bc.len2();
        double cd2 = cd.len2();
        double da2 = da.len2();

        boolean allSidesEqual = approxEq(ab2, bc2) && approxEq(bc2, cd2) && approxEq(cd2, da2);
        boolean rightAngles = approxZero(Vec.dot(ab, bc))
                && approxZero(Vec.dot(bc, cd))
                && approxZero(Vec.dot(cd, da))
                && approxZero(Vec.dot(da, ab));

        boolean parallelogram = approxZero(Vec.cross(ab, cd)) && approxZero(Vec.cross(bc, da));

        boolean isRhombus = parallelogram && allSidesEqual;
        boolean isRectangle = parallelogram && rightAngles;
        boolean isSquare = isRhombus && isRectangle;

        if (isSquare) return QuadrilateralType.SQUARE;
        if (isRectangle) return QuadrilateralType.RECTANGLE;
        if (isRhombus) return QuadrilateralType.RHOMBUS;
        return QuadrilateralType.ARBITRARY;
    }

    private void validateDistinctVertices() {
        if (samePoint(a, b) || samePoint(a, c) || samePoint(a, d) || samePoint(b, c) || samePoint(b, d) || samePoint(c, d)) {
            throw new IllegalArgumentException("Vertices must be distinct");
        }
    }

    private static Point2D requireVertex(Point2D[] vertices, int index) {
        Objects.requireNonNull(vertices, "vertices");
        if (vertices.length != 4) {
            throw new IllegalArgumentException("Quadrilateral must contain exactly 4 vertices");
        }
        return Objects.requireNonNull(vertices[index], "vertices[" + index + "]");
    }

    private void validateSimple() {
        // Disallow self-intersecting "bow-tie" quadrilateral:
        // (a,b) intersects (c,d) OR (b,c) intersects (d,a)
        if (segmentsIntersect(a, b, c, d) || segmentsIntersect(b, c, d, a)) {
            throw new IllegalArgumentException("Quadrilateral must be simple (non self-intersecting)");
        }
    }

    private boolean isConvex() {
        Vec ab = Vec.from(a, b);
        Vec bc = Vec.from(b, c);
        Vec cd = Vec.from(c, d);
        Vec da = Vec.from(d, a);

        double z1 = Vec.cross(ab, bc);
        double z2 = Vec.cross(bc, cd);
        double z3 = Vec.cross(cd, da);
        double z4 = Vec.cross(da, ab);

        // Allow tiny numerical noise
        z1 = zeroIfSmall(z1);
        z2 = zeroIfSmall(z2);
        z3 = zeroIfSmall(z3);
        z4 = zeroIfSmall(z4);

        int pos = 0;
        int neg = 0;
        if (z1 > 0) pos++; else if (z1 < 0) neg++;
        if (z2 > 0) pos++; else if (z2 < 0) neg++;
        if (z3 > 0) pos++; else if (z3 < 0) neg++;
        if (z4 > 0) pos++; else if (z4 < 0) neg++;

        return pos == 0 || neg == 0;
    }

    private static double zeroIfSmall(double v) {
        return Math.abs(v) <= EPS ? 0.0 : v;
    }

    private static boolean approxEq(double a, double b) {
        double scale = Math.max(1.0, Math.max(Math.abs(a), Math.abs(b)));
        return Math.abs(a - b) <= 1e-8 * scale;
    }

    private static boolean approxZero(double v) {
        return Math.abs(v) <= 1e-8;
    }

    private static boolean samePoint(Point2D p, Point2D q) {
        return Math.abs(p.x() - q.x()) <= EPS && Math.abs(p.y() - q.y()) <= EPS;
    }

    private static boolean segmentsIntersect(Point2D p1, Point2D p2, Point2D q1, Point2D q2) {
        // Proper intersection incl. touching at interior points; sharing endpoints is not expected here (distinct vertices).
        double o1 = orient(p1, p2, q1);
        double o2 = orient(p1, p2, q2);
        double o3 = orient(q1, q2, p1);
        double o4 = orient(q1, q2, p2);

        if (sign(o1) != sign(o2) && sign(o3) != sign(o4)) {
            return true;
        }

        // Collinear cases
        return (approxZero(o1) && onSegment(p1, p2, q1))
                || (approxZero(o2) && onSegment(p1, p2, q2))
                || (approxZero(o3) && onSegment(q1, q2, p1))
                || (approxZero(o4) && onSegment(q1, q2, p2));
    }

    private static int sign(double v) {
        if (v > EPS) return 1;
        if (v < -EPS) return -1;
        return 0;
    }

    private static double orient(Point2D a, Point2D b, Point2D c) {
        return (b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x());
    }

    private static boolean onSegment(Point2D a, Point2D b, Point2D p) {
        return p.x() >= Math.min(a.x(), b.x()) - EPS
                && p.x() <= Math.max(a.x(), b.x()) + EPS
                && p.y() >= Math.min(a.y(), b.y()) - EPS
                && p.y() <= Math.max(a.y(), b.y()) + EPS;
    }

    private record Vec(double x, double y) {
        static Vec from(Point2D from, Point2D to) {
            return new Vec(to.x() - from.x(), to.y() - from.y());
        }

        double len2() {
            return x * x + y * y;
        }

        static double dot(Vec u, Vec v) {
            return u.x * v.x + u.y * v.y;
        }

        static double cross(Vec u, Vec v) {
            return u.x * v.y - u.y * v.x;
        }
    }

    @Override
    public String toString() {
        return "Quadrilateral{"
                + "a=" + a
                + ", b=" + b
                + ", c=" + c
                + ", d=" + d
                + ", area=" + area()
                + ", perimeter=" + perimeter()
                + ", type=" + type()
                + '}';
    }
}
