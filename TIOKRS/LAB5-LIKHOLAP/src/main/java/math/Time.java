package math;

/**
 * Класс для работы со временем.
 * Реализует основные арифметические операции и сравнение. [cite: 5]
 * @author Лихолап Федор, 12 группа [cite: 5]
 */
public class Time implements Comparable<Time> {
    private final int hours;
    private final int minutes;
    private final int seconds;

    /**
     * Конструктор с валидацией входных данных. [cite: 46]
     */
    public Time(int h, int m, int s) {
        if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59) {
            throw new IllegalArgumentException("Некорректное значение времени: " + h + ":" + m + ":" + s);
        }
        this.hours = h;
        this.minutes = m;
        this.seconds = s;
    }

    /**
     * Сложение времени с заданным количеством секунд. [cite: 8]
     */
    public Time add(int s) {
        int totalSeconds = this.hours * 3600 + this.minutes * 60 + this.seconds + s;
        return fromSeconds(totalSeconds);
    }

    private static Time fromSeconds(int s) {
        s = s % 86400; // Ограничение сутками
        if (s < 0) s += 86400;
        return new Time(s / 3600, (s % 3600) / 60, s % 60);
    }

    @Override
    public int compareTo(Time o) {
        if (this.hours != o.hours) return Integer.compare(this.hours, o.hours);
        if (this.minutes != o.minutes) return Integer.compare(this.minutes, o.minutes);
        return Integer.compare(this.seconds, o.seconds);
    }

    @Override
    public String toString() {
        return String.format("%02d:%02d:%02d", hours, minutes, seconds);
    }
}