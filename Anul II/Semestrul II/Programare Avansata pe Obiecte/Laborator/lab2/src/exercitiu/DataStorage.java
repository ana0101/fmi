package exercitiu;

import java.util.ArrayList;
import java.util.Objects;

public class DataStorage {
    static ArrayList<User> userList = new ArrayList<User>();

    public void createUser(String username, Double sold) {
        userList.add(new User(username, sold));
    }

    public void printAllUsers() {
        for (User user: userList) {
            user.printUser();
        }
    }

    public void updateUserSold(String username, double sold) {
        for (User user: userList) {
            if (Objects.equals(user.getUsername(), username)) {
                user.setSold(sold);
                break;
            }
        }
    }

    public void deleteUser(String username) {
        for (int i = 0; i < userList.size(); i ++) {
            if (Objects.equals(userList.get(i).getUsername(), username)) {
                userList.remove(i);
                break;
            }
        }
    }

    public boolean userExists(String username) {
        for (User user: userList) {
            if (Objects.equals(user.getUsername(), username)) {
                return true;
            }
        }
        return false;
    }
}
