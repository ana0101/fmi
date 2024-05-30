package csv;

public class Person {
    String name;
    String firstName;
    int age;
    String email;

    public Person(String name, String firstName, int age, String email) {
        this.name = name;
        this.firstName = firstName;
        this.age = age;
        this.email = email;
    }

    @Override
    public String toString() {
        return "Person{" +
                "name='" + name + '\'' +
                ", firstName='" + firstName + '\'' +
                ", age=" + age +
                ", email='" + email + '\'' +
                '}';
    }

    public String getName() {
        return name;
    }

    public String getFirstName() {
        return firstName;
    }

    public int getAge() {
        return age;
    }

    public String getEmail() {
        return email;
    }
}
