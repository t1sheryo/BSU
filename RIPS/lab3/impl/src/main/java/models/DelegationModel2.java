package models;

import interfaces.IDelegationModel;
import interfaces.ITask;

import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.CopyOnWriteArrayList;

public class DelegationModel2 implements IDelegationModel {

    @Override
    public <T> List<T> solve(ITask<T> task, int rangeStart, int rangeEnd, int threadCount, int subTaskCount) {
        int totalElements = rangeEnd - rangeStart + 1;
        int chunkSize = (int) Math.ceil((double) totalElements / subTaskCount);

        Queue<int[]> taskQueue = new ConcurrentLinkedQueue<>();

        for (int i = 0; i < subTaskCount; i++) {
            int start = rangeStart + i * chunkSize;
            int end = Math.min(start + chunkSize - 1, rangeEnd);
            if (start <= rangeEnd) {
                taskQueue.add(new int[]{start, end});
            }
        }

        List<T> results = new CopyOnWriteArrayList<>();
        List<Thread> threads = new ArrayList<>();

        for (int i = 0; i < threadCount; i++) {
            Thread t = new Thread(() -> {
                while (true) {
                    int[] range = taskQueue.poll();

                    if (range == null) {
                        break;
                    }

                    T result = task.execute(range[0], range[1]);
                    if (result != null) {
                        results.add(result);
                    }
                }
            });
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

        return new ArrayList<>(results);
    }
}