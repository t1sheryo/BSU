package by.bsu.tiokrs.lab5.geometry;

import java.util.Objects;

public final class Point2D {
    private final double x;
    private final double y;

    public Point2D(double x, double y) {
        if (!Double.isFinite(x) || !Double.isFinite(y)) {
            throw new IllegalArgumentException("Coordinates must be finite");
        }
        this.x = x;
        this.y = y;
    }

    public double x() {
        return x;
    }

    public double y() {
        return y;
    }

    public double distanceTo(Point2D other) {
        Objects.requireNonNull(other, "other");
        return Math.hypot(x - other.x, y - other.y);
    }

    @Override
    public String toString() {
        return "Point2D{" + "x=" + x + ", y=" + y + '}';
    }
}

