package exercitiu;

import java.util.Scanner;

public class ReadFromKeyboard {
    public static void main(String[] args) {
        Scanner scanner;
        scanner = new Scanner(System.in);

        boolean ok = true;
        DataStorage dataStorage = new DataStorage();

        dataStorage.createUser("user0", 30.4);
        dataStorage.createUser("user1", 20.5);
        dataStorage.createUser("user2", 40.2);

        while (ok) {
            System.out.println("Enter command: ");
            String command = scanner.nextLine();
            String username;
            double sold;

            switch(command) {
                case "create":
                    System.out.println("Command received: create");
                    System.out.println("Username: ");
                    username = scanner.nextLine();

                    // check if username not already used
                    if (dataStorage.userExists(username)) {
                        System.out.println("Invalid username: a user wih this username already exists");
                        break;
                    }

                    System.out.println("Sold: ");
                    sold = scanner.nextDouble();
                    scanner.nextLine();

                    dataStorage.createUser(username, sold);

                    System.out.println("A new user was created with username " + username + " and sold " + sold);
                    break;


                case "read":
                    System.out.println("Command received: read");
                    // print all users
                    dataStorage.printAllUsers();
                    break;


                case "update":
                    System.out.println("Command received: update");
                    System.out.println("Username: ");
                    username = scanner.nextLine();

                    // check if username exists
                    if (!dataStorage.userExists(username)) {
                        System.out.println("Invalid username: there is no user with this username");
                        break;
                    }

                    System.out.println("Sold: ");
                    sold = scanner.nextDouble();
                    scanner.nextLine();

                    dataStorage.updateUserSold(username, sold);

                    System.out.println("Updated sold of user " + username + " to " + sold);
                    break;


                case "delete":
                    System.out.println("Command received: delete");
                    System.out.println("Username: ");
                    username = scanner.nextLine();

                    // check if username exists
                    if (!dataStorage.userExists(username)) {
                        System.out.println("Invalid username: there is no user with this username");
                        break;
                    }

                    dataStorage.deleteUser(username);

                    System.out.println("Deleted user " + username);
                    break;


                case "help":
                    System.out.println("Command received: help");
                    System.out.println("Accepted commands:\n" +
                            "\t\tcreate: Create user. Can receive two parameters: username and sold.\n" +
                            "\t\tread: Print all users.\n" +
                            "\t\tupdate: Update data. Can receive two parameters: username and sold.\n" +
                            "\t\tdelete: Delete the user's data. Receive the username.\n" +
                            "\t\thelp: Instructions on how to use the application\n" +
                            "\t\tquit: Close the application.");
                    break;


                case "quit":
                    System.out.println("Command received: quit");
                    ok = false;
                    break;


                default:
                    System.out.println("Invalid command");
                    break;
            }
        }
    }
}
