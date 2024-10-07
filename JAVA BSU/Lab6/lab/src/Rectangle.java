import java.util.Iterator;

public class Rectangle extends Figure implements Comparable<Rectangle>, Iterable<Object> {
    private final Point bottomLeft;
    private final double width;
    private final double height;
    private final String borderColor;
    private final String fillColor;

    public Rectangle(Point bottomLeft, double width, double height, String borderColor, String fillColor) {
        this.bottomLeft = bottomLeft;
        this.width = width;
        this.height = height;
        this.borderColor = borderColor;
        this.fillColor = fillColor;
    }

    @Override
    public double area() {
        return width * height;
    }

    @Override
    public double perimeter() {
        return 2 * (width + height);
    }

    @Override
    public String toString() {
        return "Rectangle(" + bottomLeft + ", " + width + ", " + height + ", " + borderColor + ", " + fillColor + ")";
    }

    public static Rectangle fromString(String str) {
        String[] parts = str.split(", ");
        Point bottomLeft = new Point(Double.parseDouble(parts[1].substring(6, parts[1].length() - 1)),
                Double.parseDouble(parts[2].substring(6, parts[2].length() - 1)));
        double width = Double.parseDouble(parts[3]);
        double height = Double.parseDouble(parts[4]);
        String borderColor = parts[5];
        String fillColor = parts[6];
        return new Rectangle(bottomLeft, width, height, borderColor, fillColor);
    }

    @Override
    public Iterator<Object> iterator() {
        return new Iterator<Object>() {
            private int index = 0;
            private final Object[] fields = {bottomLeft, width, height, borderColor, fillColor};

            @Override
            public boolean hasNext() {
                return index < fields.length;
            }

            @Override
            public Object next() {
                return fields[index++];
            }
        };
    }

    @Override
    public int compareTo(Rectangle other) {
        return Double.compare(this.area(), other.area());
    }
}