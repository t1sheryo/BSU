import interfaces.IDelegationModel;
import models.DelegationModel1;
import models.DelegationModel2;
import tasks.PrimeNumberTask;
import utils.BenchmarkUtils;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

public class Main {

    public static void main(String[] args) {
        int rangeStart = 1;
        int rangeEnd = 5_000_000;
        int threadCount = Runtime.getRuntime().availableProcessors();

        PrimeNumberTask primeTask = new PrimeNumberTask();
        IDelegationModel model1 = new DelegationModel1();
        IDelegationModel model2 = new DelegationModel2();

        int[] subTaskCounts = {4, 10, 50, 100, 500, 1000};

        System.out.println("Preparing for experiments...");
        System.out.println("Range: " + rangeStart + " - " + rangeEnd);
        System.out.println("Number of threads: " + threadCount);

        System.out.println("Calculating sequential execution time (T_seq)...");
        long seqTime = BenchmarkUtils.measureTime(() ->
                model1.solve(primeTask, rangeStart, rangeEnd, 1, 1)
        );
        System.out.println("Sequential time: " + seqTime + " ms\n");

        System.out.println("Running experiments and writing to file...");

        try (PrintWriter writer = new PrintWriter(new File("results.csv"))) {

            writer.println("Subtask count;Model 1 Time (ms);Model 1 Speedup;Model 2 Time (ms);Model 2 Speedup");

            for (int subTasks : subTaskCounts) {

                long timeModel1 = BenchmarkUtils.measureTime(() ->
                        model1.solve(primeTask, rangeStart, rangeEnd, threadCount, subTasks)
                );
                double speedupModel1 = (double) seqTime / timeModel1;

                long timeModel2 = BenchmarkUtils.measureTime(() ->
                        model2.solve(primeTask, rangeStart, rangeEnd, threadCount, subTasks)
                );
                double speedupModel2 = (double) seqTime / timeModel2;

                writer.printf("%d;%d;%.2f;%d;%.2f%n",
                        subTasks, timeModel1, speedupModel1, timeModel2, speedupModel2);

                System.out.println("Processed for " + subTasks + " subtasks.");
            }

            System.out.println("\nExperiments completed. Results saved to results.csv file");

        } catch (FileNotFoundException e) {
            System.err.println("Error creating file: " + e.getMessage());
        }
    }
}