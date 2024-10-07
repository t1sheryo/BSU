import java.util.Comparator;

public class RectangleComparatorGreater implements Comparator<Rectangle> {
    private final int keyIndex;

    public RectangleComparatorGreater(int keyIndex) {
        this.keyIndex = keyIndex;
    }

    @Override
    public int compare(Rectangle r1, Rectangle r2) {
        return Double.compare(getValue(r2), getValue(r1));
    }

    private double getValue(Rectangle rectangle) {
        return switch (keyIndex) {
            case 0 -> rectangle.area();
            case 1 -> rectangle.perimeter();
            default -> throw new IllegalArgumentException("Invalid key index");
        };
    }
}