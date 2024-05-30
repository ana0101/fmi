package interfaces.ex2.jobs;

public interface Accountant extends BaseJob {
    @Override
    default void work() {
        System.out.println("I can account!");
    }
}
