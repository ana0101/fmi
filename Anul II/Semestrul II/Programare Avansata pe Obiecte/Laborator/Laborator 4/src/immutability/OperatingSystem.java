package immutability;

public class OperatingSystem {
    private String name;
    private int version;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getVersion() {
        return version;
    }

    public void setVersion(int version) {
        this.version = version;
    }

    @Override
    public String toString() {
        return "OperatingSystem{" +
                "name='" + name + '\'' +
                ", version=" + version +
                '}';
    }
}
