import java.util.Arrays;
import java.util.Comparator;
import java.util.Iterator;

public class Main {
    public static void main(String[] args) {
        Rectangle[] rectangles = {
                new Rectangle(new Point(0, 0), 4, 5, "red", "blue"),
                new Rectangle(new Point(1, 1), 2, 3, "green", "yellow"),
                new Rectangle(new Point(2, 2), 3, 4, "blue", "red")
        };

        for (Rectangle rect : rectangles) {
            System.out.print(rect);
            System.out.printf("; area: %f; perimeter: %f;\n", rect.area(), rect.perimeter());
        }

        int keyIndex = 0;
        Arrays.sort(rectangles, new RectangleComparatorGreater(keyIndex));

        System.out.println("\nSorted rectangles:");
        for (Rectangle rect : rectangles) {
            System.out.println(rect);
        }
    }
}