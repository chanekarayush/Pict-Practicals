
/**
 * # JDBC with MySQL
 * This program connects java with mysql server to perform `CRUD` operations
 */

import java.util.Scanner;
import java.sql.*; // duh 😂

public class JDBC {

    public static void main(String[] args) {
        Connection db = null;
        String[] propertyStrings = GetProperties.getProperties("./src/.env");
        Scanner sc = new Scanner(System.in);
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            db = DriverManager.getConnection(propertyStrings[0], propertyStrings[1], propertyStrings[2]);
            if (db != null)
                System.out.println("Connected to Database Successfully");

            // Create
            insertFields(sc, db);

            // Read
            readFields(sc, db);

            // Update

            // Delete

            db.close();
        } catch (SQLException e) {
            System.err.println("Something went wrong with SQL.");
            e.printStackTrace();
        } catch (Exception e) {
            System.err.println("Something went wrong!");
            e.printStackTrace();
        } finally {
            sc.close();
        }
    }

    /**
     * <h3>Reads all rows from SQL Table</h3>
     * 
     * @param sc Scanner Object
     * @param db Connection Object
     */

    private static void readFields(Scanner sc, Connection db) {
        try {
            String query = "SELECT * FROM john_wick_characters";
            PreparedStatement preparedStatement = db.prepareStatement(query);
            ResultSet resultSet = preparedStatement.executeQuery();
            System.out.println(
                    "| character_id \t| name \t\t\t| age | gender\t   | affiliation\t   | weapon_of_choice \t  | combat_skill_level\t\t\b\b| status\t   | bounty\t     |");
            System.out.println(
                    "+--------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
            while (resultSet.next()) {
                int character_id = resultSet.getInt(1);
                String name = resultSet.getString(2);
                int age = resultSet.getInt(3);
                String gender = resultSet.getString(4);
                String affiliation = resultSet.getString(5);
                String weapon_of_choice = resultSet.getString("weapon_of_choice");
                int combat_skill_level = resultSet.getInt("combat_skill_level");
                String status = resultSet.getString("status");
                float bounty = resultSet.getFloat("bounty");
                System.out.printf("| %-13s | %-21s | %-3s | %-10s | %-21s | %-20s | %-25s | %-10s | %-15s |\n",
                        character_id, name, age, gender, affiliation, weapon_of_choice, combat_skill_level, status,
                        bounty);
            }
        } catch (SQLException e) {
            System.err.println("An error occured with MySQL!");
            e.printStackTrace();
        } catch (Exception e) {
            System.err.println("Something went wrong!");
            e.printStackTrace();
        }
    }

    /**
     * <h3>Inserts Rows into SQL Database</h3>
     * 
     * @param sc Scanner Object
     * @param db Connection Object
     */

    private static void insertFields(Scanner sc, Connection db) {

        try {
            String name, gender, affiliation, weapon_of_choice, status;
            int age, combat_skill_level;
            float bounty;

            System.out.print("Enter the name: ");
            name = sc.nextLine();
            System.out.print("\nEnter the age: ");
            age = sc.nextInt();
            sc.nextLine();
            System.out.print("\nEnter gender: ");
            gender = sc.next();
            sc.nextLine();
            System.out.print("\nEnter affiliation(organisation): ");
            affiliation = sc.nextLine();
            // sc.nextLine();
            System.out.print("\nEnter Weapon of choice: ");
            weapon_of_choice = sc.nextLine();
            // sc.nextLine();
            System.out.print("\nEnter Combat Skill Level: ");
            combat_skill_level = sc.nextInt();
            sc.nextLine();

            System.out.print("\nEnter Status(dead/alive): ");
            status = sc.next();

            System.out.print("\nEnter Bounty: ");
            bounty = sc.nextFloat();
            sc.nextLine();

            String query = "INSERT INTO john_wick_characters"
                    + "(name, age, gender, affiliation, weapon_of_choice, combat_skill_level, status, bounty)"
                    + "values (?, ?, ?, ?, ?, ?, ?, ?)";
            PreparedStatement preparedStatement = db.prepareStatement(query);
            preparedStatement.setString(1, name);
            preparedStatement.setInt(2, age);
            preparedStatement.setString(3, gender);
            preparedStatement.setString(4, affiliation);
            preparedStatement.setString(5, weapon_of_choice);
            preparedStatement.setInt(6, combat_skill_level);
            preparedStatement.setString(7, status);
            preparedStatement.setFloat(8, bounty);

            int updatedRows = preparedStatement.executeUpdate();
            if (updatedRows > 0)
                System.out.println("(" + updatedRows + ") row(s) updated successfully!");

        } catch (SQLException e) {
            System.err.println("An error occured with MySQL!");
            e.printStackTrace();
        } catch (Exception e) {
            System.err.println("Something went wrong!");
            e.printStackTrace();
        }

    }
}