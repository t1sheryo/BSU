package math;

/**
 * Класс для работы с датой в формате dd-mm-yyyy. [cite: 5]
 * @author Лихолап Федор, 12 группа [cite: 5]
 */
public class Data implements Comparable<Data> {
    private final int day;
    private final int month;
    private final int year;

    public Data(int d, int m, int y) {
        if (d < 1 || d > 31 || m < 1 || m > 12) {
            throw new IllegalArgumentException("Некорректная дата: " + d + "-" + m + "-" + y);
        }
        this.day = d;
        this.month = m;
        this.year = y;
    }

    @Override
    public int compareTo(Data o) {
        if (this.year != o.year) return Integer.compare(this.year, o.year);
        if (this.month != o.month) return Integer.compare(this.month, o.month);
        return Integer.compare(this.day, o.day);
    }

    @Override
    public String toString() {
        return String.format("%02d-%02d-%04d", day, month, year);
    }
}