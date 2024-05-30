package interfaces.ex2.people;

public interface Person2 extends BasePerson {
    default boolean hasMoney() {
        return false;
    }
}
