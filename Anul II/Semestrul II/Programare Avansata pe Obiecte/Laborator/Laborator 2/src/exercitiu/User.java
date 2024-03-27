package exercitiu;

public class User {
    private String username;
    private double sold;

    User(String username, double sold) {
        this.username = username;
        this.sold = sold;
    }

    // getters
    public String getUsername() {
        return this.username;
    }

    // setters
    public void setSold(double sold) {
        this.sold = sold;
    }

    public void printUser() {
        System.out.println("Username: " + username + ", Sold: " + sold);
    }
}
