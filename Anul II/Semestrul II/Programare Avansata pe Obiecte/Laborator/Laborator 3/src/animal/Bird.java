package animal;

public class Bird extends Animal {
    private String color;

    public Bird() {
    }

    public Bird(String name, int numberOfLegs, String color) {
        super(name, numberOfLegs);
        this.color = color;
    }

    @Override
    public void move() {
        System.out.println("I fly");
    }

    public void sing() {
        System.out.println("I chirp");
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }
}
