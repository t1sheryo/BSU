import java.util.Comparator;

public class RectangleComparatorLess implements Comparator<Rectangle> {
    private final int keyIndex;

    public RectangleComparatorLess(int keyIndex) {
        this.keyIndex = keyIndex;
    }

    @Override
    public int compare(Rectangle r1, Rectangle r2) {
        return Double.compare(getValue(r1), getValue(r2));
    }

    private double getValue(Rectangle rectangle) {
        return switch (keyIndex) {
            case 0 -> rectangle.area();
            case 1 -> rectangle.perimeter();
            default -> throw new IllegalArgumentException("Invalid key index");
        };
    }
}