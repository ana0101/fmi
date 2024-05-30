package threads.synchronize;

public class TestCounter {

    public static void main(String[] args) {
        SynchronizedCounter counter = new SynchronizedCounter();
        Thread thread1 = new Thread(counter);
        thread1.setName("Thread 1");
        Thread thread2 = new Thread(counter);
        thread2.setName("Thread 2");
        thread1.start();
        thread2.start();
    }
}
