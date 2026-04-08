package by.bsu.tiokrs.lab5.app;

import by.bsu.tiokrs.lab5.geometry.Point2D;
import by.bsu.tiokrs.lab5.geometry.QuadrilateralAnalysisResult;
import by.bsu.tiokrs.lab5.geometry.QuadrilateralAnalyzer;
import by.bsu.tiokrs.lab5.geometry.Quadrilateral;
import by.bsu.tiokrs.lab5.geometry.QuadrilateralGroupStats;
import by.bsu.tiokrs.lab5.geometry.QuadrilateralType;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Random;

public final class DemoApp {
    public static void main(String[] args) {
        int n = args.length > 0 ? Integer.parseInt(args[0]) : 30;
        long seed = args.length > 1 ? Long.parseLong(args[1]) : System.currentTimeMillis();

        Random random = new Random(seed);
        Quadrilateral[] items = new Quadrilateral[n];
        for (int i = 0; i < n; i++) {
            items[i] = randomQuadrilateral(random);
        }
        QuadrilateralAnalysisResult analysis = QuadrilateralAnalyzer.analyze(items);

        System.out.println("Seed: " + seed);
        System.out.println("Generated array size: " + items.length);
        System.out.println();

        for (QuadrilateralType type : QuadrilateralType.values()) {
            QuadrilateralGroupStats group = analysis.statsFor(type);
            System.out.println(type + ": " + group.count());
            if (group.isEmpty()) {
                System.out.println();
                continue;
            }

            System.out.printf("  min area: %.6f, perimeter: %.6f%n", group.minArea().area(), group.minArea().perimeter());
            System.out.printf("  max area: %.6f, perimeter: %.6f%n", group.maxArea().area(), group.maxArea().perimeter());
            System.out.printf("  min perimeter: %.6f, area: %.6f%n", group.minPerimeter().perimeter(), group.minPerimeter().area());
            System.out.printf("  max perimeter: %.6f, area: %.6f%n", group.maxPerimeter().perimeter(), group.maxPerimeter().area());
            System.out.println();
        }
    }

    private static Quadrilateral randomQuadrilateral(Random random) {
        double r = random.nextDouble();
        if (r < 0.25) return randomSquare(random);
        if (r < 0.50) return randomRectangle(random);
        if (r < 0.75) return randomRhombus(random);
        return randomConvexArbitrary(random);
    }

    private static Quadrilateral randomSquare(Random random) {
        double cx = randRange(random, -10, 10);
        double cy = randRange(random, -10, 10);
        double side = randRange(random, 0.5, 8.0);
        double angle = randRange(random, 0, Math.PI);

        return fromCenterSizeAndAngles(cx, cy, side, side, angle);
    }

    private static Quadrilateral randomRectangle(Random random) {
        double cx = randRange(random, -10, 10);
        double cy = randRange(random, -10, 10);
        double w = randRange(random, 0.8, 10.0);
        double h = randRange(random, 0.5, 8.0);
        if (Math.abs(w - h) < 0.2) w += 1.0;
        double angle = randRange(random, 0, Math.PI);

        return fromCenterSizeAndAngles(cx, cy, w, h, angle);
    }

    private static Quadrilateral randomRhombus(Random random) {
        double cx = randRange(random, -10, 10);
        double cy = randRange(random, -10, 10);
        double side = randRange(random, 0.8, 8.0);
        double acute = randRange(random, Math.PI / 6, 5 * Math.PI / 6);
        if (Math.abs(acute - Math.PI / 2) < 0.1) acute += 0.25;
        double angle = randRange(random, 0, Math.PI);

        // Construct rhombus as parallelogram with sides u and v of equal length and angle "acute" between them.
        double ux = side;
        double uy = 0;
        double vx = side * Math.cos(acute);
        double vy = side * Math.sin(acute);

        Point2D p0 = rotateTranslate(new Point2D(-0.5 * (ux + vx), -0.5 * (uy + vy)), angle, cx, cy);
        Point2D p1 = rotateTranslate(new Point2D(0.5 * (ux - vx), 0.5 * (uy - vy)), angle, cx, cy);
        Point2D p2 = rotateTranslate(new Point2D(0.5 * (ux + vx), 0.5 * (uy + vy)), angle, cx, cy);
        Point2D p3 = rotateTranslate(new Point2D(-0.5 * (ux - vx), -0.5 * (uy - vy)), angle, cx, cy);
        return new Quadrilateral(p0, p1, p2, p3);
    }

    private static Quadrilateral randomConvexArbitrary(Random random) {
        // Create 4 points around center and sort by angle to produce a simple polygon.
        // Retry on degenerate/self-intersecting cases.
        for (int attempt = 0; attempt < 1000; attempt++) {
            double cx = randRange(random, -10, 10);
            double cy = randRange(random, -10, 10);

            List<PointWithAngle> pts = new ArrayList<>(4);
            while (pts.size() < 4) {
                double x = cx + randRange(random, -7, 7);
                double y = cy + randRange(random, -7, 7);
                if (!Double.isFinite(x) || !Double.isFinite(y)) continue;
                double ang = Math.atan2(y - cy, x - cx);
                pts.add(new PointWithAngle(new Point2D(x, y), ang));
            }
            pts.sort(Comparator.comparingDouble(p -> p.angle));

            try {
                Quadrilateral q = new Quadrilateral(pts.get(0).p, pts.get(1).p, pts.get(2).p, pts.get(3).p);
                // If it accidentally becomes a known type, perturb slightly
                if (q.type() != QuadrilateralType.ARBITRARY) {
                    Point2D d = q.d();
                    q = new Quadrilateral(q.a(), q.b(), q.c(), new Point2D(d.x() + 0.37, d.y() + 0.19));
                }
                return q;
            } catch (RuntimeException ignored) {
                // retry
            }
        }
        throw new IllegalStateException("Failed to generate arbitrary quadrilateral");
    }

    private static Quadrilateral fromCenterSizeAndAngles(double cx, double cy, double w, double h, double angle) {
        double hw = w / 2.0;
        double hh = h / 2.0;

        Point2D p0 = rotateTranslate(new Point2D(-hw, -hh), angle, cx, cy);
        Point2D p1 = rotateTranslate(new Point2D(hw, -hh), angle, cx, cy);
        Point2D p2 = rotateTranslate(new Point2D(hw, hh), angle, cx, cy);
        Point2D p3 = rotateTranslate(new Point2D(-hw, hh), angle, cx, cy);
        return new Quadrilateral(p0, p1, p2, p3);
    }

    private static Point2D rotateTranslate(Point2D p, double angle, double tx, double ty) {
        double ca = Math.cos(angle);
        double sa = Math.sin(angle);
        double x = p.x() * ca - p.y() * sa + tx;
        double y = p.x() * sa + p.y() * ca + ty;
        return new Point2D(x, y);
    }

    private static double randRange(Random random, double min, double max) {
        return min + random.nextDouble() * (max - min);
    }

    private record PointWithAngle(Point2D p, double angle) {
    }
}
