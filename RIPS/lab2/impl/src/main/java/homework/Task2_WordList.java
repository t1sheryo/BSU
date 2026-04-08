package homework;

import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Task2_WordList {
    private ArrayList<String> words;
    private Lock myLock;
    private boolean isSorted;

    public Task2_WordList(Scanner in) {
        words = new ArrayList<String>();
        myLock = new ReentrantLock();
        isSorted = false;
        while (in.hasNext()) words.add(in.next());
    }

    private class Swapper implements Runnable {
        public void run() {
            while (true) {
                myLock.lock();
                try {
                    int i = 0;
                    while (i < words.size() - 1 && words.get(i).compareTo(words.get(i + 1)) <= 0) {
                        i++;
                    }

                    if (i == words.size() - 1) {
                        isSorted = true;
                        break;
                    } else {
                        String word1 = words.get(i);
                        String word2 = words.get(i + 1);
                        words.set(i, word2);
                        words.set(i + 1, word1);
                    }
                } finally {
                    myLock.unlock();
                }
            }
        }
    }

    private class DupeRemover implements Runnable {
        public void run() {
            while (true) {
                myLock.lock();
                try {
                    int i = 0;
                    while (i < words.size() - 1 && !words.get(i).equals(words.get(i + 1))) {
                        i++;
                    }

                    if (i == words.size() - 1) {
                        if (isSorted) {
                            break;
                        }
                    } else {
                        words.remove(i);
                    }
                } finally {
                    myLock.unlock();
                }
            }
        }
    }

    public void slowSort() throws InterruptedException {
        Runnable r1 = new Swapper();
        Runnable r2 = new DupeRemover();
        Thread t1 = new Thread(r1);
        Thread t2 = new Thread(r2);

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        System.out.println(words);
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        Scanner in = new Scanner(new FileReader("data.txt"));
        Task2_WordList list = new Task2_WordList(in);
        list.slowSort();
    }
}