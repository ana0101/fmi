package test;

import animal.Animal;
import animal.Ape;
import animal.Bird;
import animal.Duck;

public class TestAnimal {
    public static void main(String[] args) {
        Animal animal = new Animal();
        animal.move();

        Ape ape = new Ape();
        ape.move();

        Bird bird = new Bird();
        bird.move();
        bird.sing();

        Duck duck = new Duck();
        duck.move();
        duck.sing();
    }
}
