package interfaces.ex2.jobs;

public interface Programmer extends BaseJob {
    @Override
    default void work() {
        System.out.println("I can write code!");
    }
}
