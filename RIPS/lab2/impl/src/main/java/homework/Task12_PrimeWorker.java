package homework;

public class Task12_PrimeWorker implements Runnable {
    private long currentNumber = 2;
    private long primesFound = 0;

    @Override
    public void run() {
        System.out.println("Computation thread (Variant 2) started. Searching...");

        while (!Thread.currentThread().isInterrupted()) {
            if (isPrime(currentNumber)) {
                primesFound++;
            }
            currentNumber++;
        }

        System.out.println("\n--- Computation thread interrupted ---");
        System.out.println("State at the moment of interruption:");
        System.out.println("Last checked number: " + (currentNumber - 1));
        System.out.println("Prime numbers found: " + primesFound);
    }

    private boolean isPrime(long n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;

        for (long i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }
}