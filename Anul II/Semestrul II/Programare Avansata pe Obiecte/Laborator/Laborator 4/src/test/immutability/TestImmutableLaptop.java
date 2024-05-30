package test.immutability;

import immutability.OperatingSystem;
import immutability.ImmutableLaptop;

public class TestImmutableLaptop {
    public static void main(String[] args) {
        OperatingSystem operatingSystem = new OperatingSystem();
        operatingSystem.setName("Windows");
        operatingSystem.setVersion(11);
        ImmutableLaptop laptop = new ImmutableLaptop("hp", operatingSystem);
        System.out.println(laptop);

        operatingSystem.setVersion(10);
        System.out.println(laptop);
    }
}
