package util;

/**
 * Класс, представляющий трехмерный вектор в декартовой системе координат.
 * Предоставляет основные операции векторной алгебры: сложение, вычитание,
 * скалярное и векторное произведение, проверку компланарности.
 *
 * <p>Все векторы являются неизменяемыми (immutable) - операции создания
 * новых векторов всегда возвращают новый объект, не изменяя исходный.</p>
 *
 * @version 1.0
 * @author Timofey Cheberuk
 */
public class Vector {
    /** Координата X вектора */
    private final double x;

    /** Координата Y вектора */
    private final double y;

    /** Координата Z вектора */
    private final double z;

    /**
     * Создает вектор с заданными координатами.
     *
     * @param x координата X
     * @param y координата Y
     * @param z координата Z
     */
    public Vector(double x, double y, double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    /**
     * Создает вектор из массива координат.
     * Массив должен содержать ровно три элемента.
     *
     * @param coordinates массив из трех координат [x, y, z]
     * @throws IllegalArgumentException если массив содержит не 3 элемента
     */
    public Vector(double[] coordinates) {
        if (coordinates.length != 3) {
            throw new IllegalArgumentException("Array must contain exactly 3 elements.");
        }
        this.x = coordinates[0];
        this.y = coordinates[1];
        this.z = coordinates[2];
    }

    /**
     * Возвращает координату X вектора.
     *
     * @return координата X
     */
    public double getX() {
        return x;
    }

    /**
     * Возвращает координату Y вектора.
     *
     * @return координата Y
     */
    public double getY() {
        return y;
    }

    /**
     * Возвращает координату Z вектора.
     *
     * @return координата Z
     */
    public double getZ() {
        return z;
    }

    /**
     * Возвращает массив координат вектора [x, y, z].
     *
     * @return массив из трех координат
     */
    public double[] getCoordinates() {
        return new double[]{x, y, z};
    }

    /**
     * Возвращает сумму текущего вектора с другим вектором.
     * Вычисляется покоординатно: (x1+x2, y1+y2, z1+z2).
     *
     * @param other вектор для сложения
     * @return новый вектор, являющийся суммой двух векторов
     */
    public Vector add(Vector other) {
        return new Vector(this.x + other.x, this.y + other.y, this.z + other.z);
    }

    /**
     * Возвращает разность текущего вектора и другого вектора.
     * Вычисляется покоординатно: (x1-x2, y1-y2, z1-z2).
     *
     * @param other вычитаемый вектор
     * @return новый вектор, являющийся разностью двух векторов
     */
    public Vector subtract(Vector other) {
        return new Vector(this.x - other.x, this.y - other.y, this.z - other.z);
    }

    /**
     * Вычисляет скалярное произведение текущего вектора с другим вектором.
     * Скалярное произведение = x1*x2 + y1*y2 + z1*z2.
     *
     * @param other второй вектор для скалярного произведения
     * @return скалярное произведение двух векторов
     */
    public double scalarMultiplication(Vector other) {
        return this.x * other.x + this.y * other.y + this.z * other.z;
    }

    /**
     * Вычисляет векторное произведение текущего вектора на другой вектор.
     * Результат - вектор, перпендикулярный обоим исходным векторам.
     *
     * <p>Формула вычисления:</p>
     * <pre>
     * result.x = y1*z2 - z1*y2
     * result.y = z1*x2 - x1*z2
     * result.z = x1*y2 - y1*x2
     * </pre>
     *
     * @param other второй вектор для векторного произведения
     * @return новый вектор - результат векторного произведения
     */
    public Vector vectorMultiplication(Vector other) {
        return new Vector(
                this.y * other.z - this.z * other.y,
                this.z * other.x - this.x * other.z,
                this.x * other.y - this.y * other.x
        );
    }

    /**
     * Сравнивает текущий вектор с другим вектором на равенство координат.
     *
     * @param other вектор для сравнения
     * @return true если все координаты векторов совпадают, false в противном случае
     */
    public boolean equals(Vector other) {
        if (other == null) return false;
        return this.x == other.x && this.y == other.y && this.z == other.z;
    }

    /**
     * Возвращает строковое представление вектора в формате "Vector(x, y, z)".
     *
     * @return строковое представление вектора
     */
    @Override
    public String toString() {
        return "Vector(" + x + ", " + y + ", " + z + ")";
    }

    /**
     * Проверяет компланарность трех векторов.
     * Векторы компланарны, если их смешанное произведение равно нулю
     * (с учетом погрешности вычислений с плавающей точкой).
     *
     * <p>Алгоритм:</p>
     * <ol>
     *   <li>Вычисляем векторное произведение v1 и v2</li>
     *   <li>Вычисляем скалярное произведение полученного вектора на v3</li>
     *   <li>Сравниваем модуль результата с epsilon = 1e-10</li>
     * </ol>
     *
     * @param v1 первый вектор
     * @param v2 второй вектор
     * @param v3 третий вектор
     * @return true если векторы компланарны, false в противном случае
     */
    public static boolean areCoplanar(Vector v1, Vector v2, Vector v3) {
        Vector vectorMultiplication = v1.vectorMultiplication(v2);
        double scalarMultiplication = vectorMultiplication.scalarMultiplication(v3);
        return Math.abs(scalarMultiplication) < 1e-10;
    }
}