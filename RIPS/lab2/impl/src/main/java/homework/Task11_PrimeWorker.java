package homework;

public class Task11_PrimeWorker implements Runnable {
    private volatile boolean stopRequested = false;
    private long currentNumber = 2;
    private long primesFound = 0;

    public void requestStop() {
        stopRequested = true;
    }

    @Override
    public void run() {
        System.out.println("Computation thread started. Searching for prime numbers...");

        while (!stopRequested) {
            if (isPrime(currentNumber)) {
                primesFound++;
            }
            currentNumber++;
        }

        System.out.println("\n--- Computation thread stopped gracefully ---");
        System.out.println("State at the moment of stopping:");
        System.out.println("Last checked number: " + (currentNumber - 1));
        System.out.println("Total prime numbers found: " + primesFound);
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