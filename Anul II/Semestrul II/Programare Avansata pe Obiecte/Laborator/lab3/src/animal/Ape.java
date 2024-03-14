package animal;

public class Ape extends Animal {
    private String size;

    public Ape() {
    }

    public Ape(String name, int numberOfLegs, String size) {
        super(name, numberOfLegs);  // call parent class constructor
        this.size = size;
    }

    @Override
    public void move() {
        System.out.println("I jump");
    }

    public String getSize() {
        return size;
    }

    public void setSize(String size) {
        this.size = size;
    }
}
