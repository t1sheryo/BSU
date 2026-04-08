package utils;

import java.util.function.Supplier;

public class BenchmarkUtils {

    /**
     * Измеряет время выполнения переданного блока кода.
     *
     * @param task блок кода для выполнения
     * @return время выполнения в миллисекундах
     */
    public static long measureTime(Supplier<?> task) {
        long startTime = System.currentTimeMillis();
        task.get();
        long endTime = System.currentTimeMillis();
        return endTime - startTime;
    }
}