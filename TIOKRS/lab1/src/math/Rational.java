package math;

import java.util.Comparator;
import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Класс, представляющий рациональную (несократимую) дробь.
 * Дробь представляется парой целых чисел (a, b), где a - числитель, b - знаменатель.
 * Класс реализует арифметические операции, сравнение, итерацию по полям,
 * а также парсинг из строки.
 *
 * @author Fiodor Likholap
 * @version 1.0
 */
public class Rational implements Comparable<Rational>, Iterable<Integer> {

    /**
     * Числитель дроби.
     */
    private final int a;

    /**
     * Знаменатель дроби. Всегда положительный для нормализованной дроби.
     */
    private final int b;

    /**
     * Конструктор для создания рациональной дроби.
     * Автоматически сокращает дробь и нормализует знак (знаменатель всегда положительный).
     *
     * @param a числитель
     * @param b знаменатель
     * @throws IllegalArgumentException если знаменатель равен нулю
     */
    public Rational(int a, int b) {
        if (b == 0) {
            throw new IllegalArgumentException("Знаменатель не может быть равен нулю.");
        }

        // Использование assert для дополнительной проверки в режиме отладки (флаг -ea)
        assert b != 0 : "Знаменатель равен 0, что недопустимо";

        if (b < 0) {
            a = -a;
            b = -b;
        }

        int gcd = gcd(Math.abs(a), b);
        this.a = a / gcd;
        this.b = b / gcd;
    }

    /**
     * Конструктор для инициализации объекта из строки текста.
     * Ожидаемый формат строки соответствует результату метода toString(): "a/b".
     * Если дробь целая, допускается формат "a".
     *
     * @param str строковое представление дроби
     * @throws IllegalArgumentException если строка имеет неверный формат
     * @throws NumberFormatException если компоненты строки не являются целыми числами
     */
    public Rational(String str) {
        if (str == null || str.trim().isEmpty()) {
            throw new IllegalArgumentException("Строка не может быть пустой.");
        }
        String[] parts = str.split("/");
        if (parts.length == 1) {
            this.a = Integer.parseInt(parts[0].trim());
            this.b = 1;
        } else if (parts.length == 2) {
            int tempA = Integer.parseInt(parts[0].trim());
            int tempB = Integer.parseInt(parts[1].trim());
            if (tempB == 0) {
                throw new IllegalArgumentException("Знаменатель не может быть равен нулю.");
            }
            if (tempB < 0) {
                tempA = -tempA;
                tempB = -tempB;
            }
            int gcd = gcd(Math.abs(tempA), tempB);
            this.a = tempA / gcd;
            this.b = tempB / gcd;
        } else {
            throw new IllegalArgumentException("Неверный формат строки для Rational: " + str);
        }
    }

    /**
     * Алгоритм Евклида для нахождения наибольшего общего делителя (НОД).
     * Используется для сокращения дробей.
     *
     * @param a первое число (положительное)
     * @param b второе число (положительное)
     * @return наибольший общий делитель чисел a и b
     */
    private int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    /**
     * Сложение двух рациональных дробей.
     *
     * @param other дробь, которую нужно прибавить
     * @return новый объект Rational, представляющий сумму
     */
    public Rational add(Rational other) {
        int newNum = this.a * other.b + other.a * this.b;
        int newDen = this.b * other.b;
        return new Rational(newNum, newDen);
    }

    /**
     * Вычитание рациональной дроби.
     *
     * @param other дробь, которую нужно вычесть
     * @return новый объект Rational, представляющий разность
     */
    public Rational subtract(Rational other) {
        int newNum = this.a * other.b - other.a * this.b;
        int newDen = this.b * other.b;
        return new Rational(newNum, newDen);
    }

    /**
     * Умножение двух рациональных дробей.
     *
     * @param other дробь, на которую нужно умножить
     * @return новый объект Rational, представляющий произведение
     */
    public Rational multiply(Rational other) {
        return new Rational(this.a * other.a, this.b * other.b);
    }

    /**
     * Деление на рациональную дробь.
     *
     * @param other дробь, на которую нужно разделить
     * @return новый объект Rational, представляющий частное
     * @throws IllegalArgumentException если делитель равен нулю (числитель второй дроби = 0)
     */
    public Rational divide(Rational other) {
        if (other.a == 0) {
            throw new IllegalArgumentException("Деление на ноль невозможно.");
        }
        return new Rational(this.a * other.b, this.b * other.a);
    }

    /**
     * Сравнение данной дроби с другой (естественная сортировка).
     * Реализует интерфейс Comparable. Сравнение происходит путем приведения к общему знаменателю.
     *
     * @param o дробь для сравнения
     * @return отрицательное число, ноль или положительное число, если данная дробь
     * соответственно меньше, равна или больше указанной
     */
    @Override
    public int compareTo(Rational o) {
        long left = (long) this.a * o.b;
        long right = (long) o.a * this.b;
        return Long.compare(left, right);
    }

    /**
     * Возвращает строковое представление дроби в формате "a/b".
     * Если знаменатель равен 1, возвращается только числитель.
     *
     * @return строковое представление объекта
     */
    @Override
    public String toString() {
        if (b == 1) return String.valueOf(a);
        return a + "/" + b;
    }

    /**
     * Итератор для обхода полей объекта (индексатор).
     * Реализует интерфейс Iterable. Сначала возвращает числитель, затем знаменатель.
     *
     * @return итератор по целочисленным полям дроби
     */
    @Override
    public Iterator<Integer> iterator() {
        return new Iterator<Integer>() {
            private int currentIndex = 0;

            @Override
            public boolean hasNext() {
                return currentIndex < 2;
            }

            @Override
            public Integer next() {
                if (currentIndex == 0) {
                    currentIndex++;
                    return a;
                } else if (currentIndex == 1) {
                    currentIndex++;
                    return b;
                }
                throw new NoSuchElementException("Больше нет полей для итерации.");
            }
        };
    }

    /**
     * Перечисление полей, по которым можно производить сортировку через Компаратор.
     */
    public enum SortField {
        NUMERATOR, DENOMINATOR
    }

    /**
     * Компаратор для сортировки массива объектов Rational по выбранному полю.
     */
    public static class FieldComparator implements Comparator<Rational> {
        private final SortField field;

        /**
         * Конструктор компаратора.
         *
         * @param field поле для сравнения (NUMERATOR или DENOMINATOR)
         */
        public FieldComparator(SortField field) {
            this.field = field;
        }

        @Override
        public int compare(Rational r1, Rational r2) {
            if (field == SortField.NUMERATOR) {
                return Integer.compare(r1.a, r2.a);
            } else {
                return Integer.compare(r1.b, r2.b);
            }
        }
    }
}