package models;

import interfaces.IDelegationModel;
import interfaces.ITask;

import java.util.ArrayList;
import java.util.List;

public class DelegationModel1 implements IDelegationModel {

    @Override
    public <T> List<T> solve(ITask<T> task, int rangeStart, int rangeEnd, int threadCount, int subTaskCount) {
        List<T> results = new ArrayList<>();
        int totalElements = rangeEnd - rangeStart + 1;
        int chunkSize = (int) Math.ceil((double) totalElements / subTaskCount);

        List<Worker<T>> workers = new ArrayList<>();
        for (int i = 0; i < threadCount; i++) {
            workers.add(new Worker<>(task));
        }

        for (int i = 0; i < subTaskCount; i++) {
            int start = rangeStart + i * chunkSize;
            int end = Math.min(start + chunkSize - 1, rangeEnd);

            if (start <= rangeEnd) {
                workers.get(i % threadCount).addSubTask(start, end);
            }
        }

        List<Thread> threads = new ArrayList<>();
        for (Worker<T> worker : workers) {
            Thread t = new Thread(worker);
            threads.add(t);
            t.start();
        }

        for (Thread t : threads) {
            try {
                t.join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        for (Worker<T> worker : workers) {
            results.addAll(worker.getResults());
        }

        return results;
    }

    private static class Worker<T> implements Runnable {
        private final ITask<T> task;
        private final List<int[]> subTasks = new ArrayList<>();
        private final List<T> results = new ArrayList<>();

        public Worker(ITask<T> task) {
            this.task = task;
        }

        public void addSubTask(int start, int end) {
            subTasks.add(new int[]{start, end});
        }

        public List<T> getResults() {
            return results;
        }

        @Override
        public void run() {
            for (int[] range : subTasks) {
                T result = task.execute(range[0], range[1]);
                results.add(result);
            }
        }
    }
}