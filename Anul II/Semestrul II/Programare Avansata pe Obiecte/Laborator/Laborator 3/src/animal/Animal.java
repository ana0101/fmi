package animal;

public class Animal {
    private String name;
    private int numberOfLegs;

    public Animal() {
    }

    // supraincarcare constructor (overloading)
    public Animal(String name, int numberOfLegs) {
        this.name = name;
        this.numberOfLegs = numberOfLegs;
    }

    public void move() {
        System.out.println("I move");
    }

    public void eat() {
        System.out.println("I eat");
    }

    // supraincarcare (overloading)
    public void eat(String food) {
        System.out.println("I eat " + food);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getNumberOfLegs() {
        return numberOfLegs;
    }

    public void setNumberOfLegs(int numberOfLegs) {
        this.numberOfLegs = numberOfLegs;
    }
}
