package homework;

import java.util.concurrent.atomic.AtomicLong;

public class Task3 {

    private static final AtomicLong currentNumber = new AtomicLong(2);
    private static final AtomicLong totalPrimesFound = new AtomicLong(0);
    private static final long MAX_NUMBER = 1_000_000;

    public static void main(String[] args) throws InterruptedException {
        int numThreads = Runtime.getRuntime().availableProcessors();
        System.out.println("Number of available threads (cores): " + numThreads);

        Thread[] threads = new Thread[numThreads];
        long startTime = System.currentTimeMillis();

        for (int i = 0; i < numThreads; i++) {
            PrimeWorker worker = new PrimeWorker(i + 1);
            threads[i] = new Thread(worker);
            threads[i].start();
        }

        for (Thread thread : threads) {
            thread.join();
        }

        long endTime = System.currentTimeMillis();

        System.out.println("\n--- Analysis Results ---");
        System.out.println("Prime numbers found: " + totalPrimesFound.get());
        System.out.println("Execution time: " + (endTime - startTime) + " ms");
        System.out.println("Distribution method: Dynamic (via AtomicLong)");
    }

    private static class PrimeWorker implements Runnable {
        private final int threadId;
        private int localPrimeCount = 0;

        public PrimeWorker(int threadId) {
            this.threadId = threadId;
        }

        @Override
        public void run() {
            while (true) {
                long candidate = currentNumber.getAndIncrement();

                if (candidate > MAX_NUMBER) {
                    break;
                }

                if (isPrime(candidate)) {
                    localPrimeCount++;
                }
            }

            totalPrimesFound.addAndGet(localPrimeCount);
            System.out.println("Thread " + threadId + " finished. Numbers found: " + localPrimeCount);
        }

        private boolean isPrime(long n) {
            if (n < 2) return false;
            if (n == 2 || n == 3) return true;
            if (n % 2 == 0 || n % 3 == 0) return false;

            for (long i = 5; i * i <= n; i += 6) {
                if (n % i == 0 || n % (i + 2) == 0) {
                    return false;
                }
            }
            return true;
        }
    }
}