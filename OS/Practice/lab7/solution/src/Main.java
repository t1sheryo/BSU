import java.util.*;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;

import static java.lang.Thread.sleep;

public class Main {
    private static final Object lockObject = new Object();
    private static List<Float> lst;
    private static int positiveCount = 0;
    private static boolean workThreadIsDone = false;
    private static boolean countThreadIsDone = false;

    public static void main(String[] args) throws InterruptedException {

        Semaphore semaphore = new Semaphore(1);
        ReentrantLock lock = new ReentrantLock();

        Thread work = new WorkThread(lock, semaphore);
        Thread count = new CountThread(lock, semaphore);

        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите размер массива: ");
        int n;
        n = scanner.nextInt();

        lst = new ArrayList<Float>();
        int choice = 0;
        do{
            System.out.println("Как заполнять массив: \n1) Вручную\n2) Генерация и заполнение случайными числами");
            choice = scanner.nextInt();
            switch (choice) {
                case 1:
                    for(int i = 0; i < n; ++i){
                        lst.add(scanner.nextFloat());
                    }
                    break;
                case 2:
                    generateList(n);
                    break;
                default:
                    System.out.println("Неправильный выбор! Введите заново");
            }
        } while(choice < 1 || choice > 2);

        System.out.println("Размер массива: " + n + "\nМассив: " + lst);

        work.start();
        sleep(2);
        synchronized(lockObject){
            while(!workThreadIsDone) {
                try {
                    lockObject.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            System.out.println("Result list: " + lst);
        }

        count.start();
        synchronized (lockObject){
            while(!countThreadIsDone) {
                try{
                    lockObject.wait();
                } catch(InterruptedException e){
                    e.printStackTrace();
                }
            }
            System.out.println("Amount of positive numbers in list: " + positiveCount + " from MainThread");
        }

        work.join();
        count.join();
    }

    private static void generateList(int size){
        Random rand = new Random();
        for(int i = 0; i < size; ++i){
            lst.add(rand.nextFloat(20) - 10);
        }
    }

    private static class WorkThread extends Thread {
        ReentrantLock lock;
        Semaphore semaphore;

        public WorkThread(ReentrantLock lock, Semaphore semaphore) {
            super("WorkThread");
            this.lock = lock;
            this.semaphore = semaphore;
        }

        public void run() {
            synchronized (lockObject) {

                System.out.print("Введите временной интервал:");
                Scanner scanner = new Scanner(System.in);
                int sleepTime = scanner.nextInt();

                List<Float> newList = new ArrayList<>();
                for (int i = 0; i < lst.size(); ++i) {
                    if (lst.get(i) > 0) {
                        newList.add((float) Math.floor(lst.get(i)));
                    }
                    try {
                        sleep(sleepTime);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }
                for(int i = 0; i < lst.size(); ++i){
                    newList.add(lst.get(i));
                    try {
                        sleep(sleepTime);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }

                lst = newList;

                workThreadIsDone = true;
                lockObject.notify();
            }
        }
    }

    private static class CountThread extends Thread {
        ReentrantLock lock;
        Semaphore semaphore;
        public CountThread(ReentrantLock lock, Semaphore semaphore) {
            super("CountThread");
            //this.lock = lock;
            //this.semaphore = semaphore;
        }

        public void run() {
            synchronized (lockObject) {
                int countPositive = 0;
                for (int i = 0; i < lst.size(); ++i) {
                    if (lst.get(i) > 0) {
                        ++countPositive;
                    }
                }

                System.out.println("Amount of positive numbers in list: " + countPositive + " from CountThread");
                positiveCount = countPositive;

                countThreadIsDone = true;
                lockObject.notify();
            }
        }
    }
}