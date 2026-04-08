package homework;

import java.util.Scanner;

public class Task11_Main {
    public static void main(String[] args) {
        Task11_PrimeWorker worker = new Task11_PrimeWorker();
        Thread workerThread = new Thread(worker);

        workerThread.start();

        System.out.println("Press ENTER to stop the computation thread...");
        Scanner scanner = new Scanner(System.in);
        scanner.nextLine();

        worker.requestStop();

        try {
            workerThread.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            System.err.println("Main thread was interrupted while waiting.");
        }

        System.out.println("Main thread finished.");
    }
}