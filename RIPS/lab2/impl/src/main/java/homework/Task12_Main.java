package homework;

import java.util.Scanner;

public class Task12_Main {
    public static void main(String[] args) {
        Runnable workerTask = new Task12_PrimeWorker();
        Thread workerThread = new Thread(workerTask);

        workerThread.start();

        System.out.println("Press ENTER to interrupt the thread...");
        Scanner scanner = new Scanner(System.in);
        scanner.nextLine();

        System.out.println("Sending interrupt() signal...");
        workerThread.interrupt();

        try {
            workerThread.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        System.out.println("Main thread finished.");
    }
}