package immutability;

public class ImmutableLaptop {
    private final String name;
    private final OperatingSystem operatingSystem;

    public ImmutableLaptop(String name, OperatingSystem operatingSystem) {
        this.name = name;
        OperatingSystem cloneOperatingSystem = new OperatingSystem();
        cloneOperatingSystem.setName(operatingSystem.getName());
        cloneOperatingSystem.setVersion(operatingSystem.getVersion());
        this.operatingSystem = cloneOperatingSystem;
    }

    public String getName() {
        return name;
    }

    public OperatingSystem getOperatingSystem() {
        OperatingSystem cloneOperatingSystem = new OperatingSystem();
        cloneOperatingSystem.setName(operatingSystem.getName());
        cloneOperatingSystem.setVersion(operatingSystem.getVersion());
        return cloneOperatingSystem;
    }

    @Override
    public String toString() {
        return "ImmutableLaptop{" +
                "name='" + name + '\'' +
                ", operatingSystem=" + operatingSystem +
                '}';
    }
}
