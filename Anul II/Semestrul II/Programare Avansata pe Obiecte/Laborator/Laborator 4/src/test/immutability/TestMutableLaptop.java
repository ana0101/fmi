package test.immutability;

import immutability.MutableLaptop;
import immutability.OperatingSystem;

public class TestMutableLaptop {
    public static void main(String[] args) {
        OperatingSystem operatingSystem = new OperatingSystem();
        operatingSystem.setName("Windows");
        operatingSystem.setVersion(11);
        MutableLaptop laptop = new MutableLaptop("hp", operatingSystem);
        System.out.println(laptop);

        operatingSystem.setVersion(10);
        System.out.println(laptop);
    }
}
