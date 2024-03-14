package animal;

import java.util.Objects;

public class Duck extends Bird {
    private int length;

    public Duck() {
    }

    public Duck(String name, int numberOfLegs, String color, int length) {
        super(name, numberOfLegs, color);
        this.length = length;
    }

    @Override
    public void move() {
        System.out.println("I swim");
    }

    @Override
    public void sing() {
        System.out.println("I quack");
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;

        if (obj == null || getClass() != obj.getClass())
            return false;

        Duck duck = (Duck) obj;

        return Objects.equals(this.getName(), duck.getName()) &&
                this.getNumberOfLegs() == duck.getNumberOfLegs() &&
                Objects.equals(this.getColor(), duck.getColor()) &&
                Objects.equals(this.getLength(), duck.getLength());
    }

    @Override
    public int hashCode() {
        return Objects.hash(length, getName(), getColor(), getNumberOfLegs());
    }

    @Override
    public String toString() {
        return super.toString();
    }

    public int getLength() {
        return length;
    }

    public void setLength(int length) {
        this.length = length;
    }
}
