package util;

/**
 * Главный класс приложения для демонстрации работы с векторами.
 * Создает массив векторов, выводит их и проверяет компланарность.
 *
 * @version 1.0
 * @author Timofey Cheberuk
 */
public class Main {
    /**
     * Точка входа в приложение.
     * Демонстрирует создание векторов, их вывод и проверку компланарности.
     *
     * @param args аргументы командной строки (не используются)
     */
    public static void main(String[] args) {
        // Создание массива векторов
        Vector[] vectors = {
                new Vector(1, 2, 3),
                new Vector(4, 4, 6),
                new Vector(1, 1, 1)
        };

        // Вывод всех векторов
        System.out.println("Vectors:");
        for (Vector vector : vectors) {
            System.out.println(vector);
        }

        // Проверка компланарности трех векторов
        boolean coplanar = Vector.areCoplanar(vectors[0], vectors[1], vectors[2]);
        System.out.println("Vectors complanar: " + coplanar);
    }
}