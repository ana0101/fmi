package immutability;

public final class MutableLaptop {
    private final String name;
    private final OperatingSystem operatingSystem;

    public MutableLaptop(String name, OperatingSystem operatingSystem) {
        this.name = name;
        this.operatingSystem = operatingSystem;
    }

    public String getName() {
        return name;
    }

    public OperatingSystem getOperatingSystem() { return this.operatingSystem; }

    @Override
    public String toString() {
        return "MutableLaptop{" +
                "name='" + name + '\'' +
                ", operatingSystem=" + operatingSystem +
                '}';
    }
}
