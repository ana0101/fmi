package interfaces.ex2.people;

public interface Person1 extends BasePerson {
    default boolean hasWillToLive() {
        return false;
    }
}
