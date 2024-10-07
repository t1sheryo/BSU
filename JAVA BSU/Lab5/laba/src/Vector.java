import java.util.Arrays;

public class Vector {
    private final double x;
    private final double y;
    private final double z;

    public Vector(double x, double y, double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public Vector(double[] coordinates) {
        if (coordinates.length != 3) {
            throw new IllegalArgumentException("Array must contain exactly 3 elements.");
        }
        this.x = coordinates[0];
        this.y = coordinates[1];
        this.z = coordinates[2];
    }

    public Vector add(Vector other) {
        return new Vector(this.x + other.x, this.y + other.y, this.z + other.z);
    }

    public Vector subtract(Vector other) {
        return new Vector(this.x - other.x, this.y - other.y, this.z - other.z);
    }

    public double ScalarMultiplication(Vector other) {
        return this.x * other.x + this.y * other.y + this.z * other.z;
    }

    public Vector VectorMultiplication(Vector other) {
        return new Vector(
                this.y * other.z - this.z * other.y,
                this.z * other.x - this.x * other.z,
                this.x * other.y - this.y * other.x
        );
    }

    public boolean equals(Vector other) {
        return this.x == other.x && this.y == other.y && this.z == other.z;
    }

    @Override
    public String toString() {
        return "Vector(" + x + ", " + y + ", " + z + ")";
    }

    public static boolean areCoplanar(Vector v1, Vector v2, Vector v3) {
        Vector VectorMultiplication = v1.VectorMultiplication(v2);
        double ScalarMultiplication = VectorMultiplication.ScalarMultiplication(v3);
        return Math.abs(ScalarMultiplication) < 1e-10;
    }
}