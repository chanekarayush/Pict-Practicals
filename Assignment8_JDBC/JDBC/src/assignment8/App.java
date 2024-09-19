package assignment8;

import java.sql.*;
import java.util.*;
import java.sql.*;

@SuppressWarnings("unused")
public class App {
    public static void main(String[] args) throws Exception {
        String url = "jdbc:mysql://127.0.0.1:3306/assignment_8_dbms";
        String user = "root";
        String password = "Ayush_Chanekar23";
        Scanner sc = new Scanner(System.in);
        Connection db = null;
        // accept user, password and server name

        PreparedStatement ps;
        String query = "";

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");

            db = DriverManager.getConnection(url, user, password);

            Statement st1 = db.createStatement();
            if (db != null && !db.isClosed()) {
                System.out.println("Successfully Connected to database" + url + "! \n");
            } else {
                System.out.println("An Error Occured while opening the database");
                throw new SQLException("Invalid Database url or state");
            }

            char ctd = 'y';
            int ch, id, age;
            ResultSet rs1;
            String name, email;

            do {

                System.out.println("Enter:\n\r1. Display all records from table\n\r2. Insert new records"
                        + "\n\r3. Update existing records\n\r4. Delete existing records\n\r5. Truncate Table\n\r6. Exit");
                ch = sc.nextInt();
                switch (ch) {
                case 1:
                    // SELECT
                    query = "SELECT * FROM test";

                    rs1 = st1.executeQuery(query);
                    System.out.println(
                            "+-----------------------------------------------------------------------------------------------------+");
                    while (rs1.next()) {

                        // System.out.println(rs1.getInt(1) + "\t| " + rs1.getString(2) + "\t\t| " +
                        // rs1.getString(3)
                        // + "\t\t\t| " + rs1.getString(4));
                        System.out.println(String.format("| %-10s | %-25s | %-20s | %-35s |", rs1.getInt(1),
                                rs1.getString(2), rs1.getString(3), rs1.getString(4)));

                    }
                    System.out.println(
                            "+-----------------------------------------------------------------------------------------------------+");
                    break;
                case 2:
                    // INSERT

                    query = "INSERT INTO test VALUES(?,?,?,?)";
                    ps = db.prepareStatement(query);

                    System.out.print("Enter id: ");
                    id = sc.nextInt();
                    sc.nextLine();
                    System.out.print("\nEnter Name: ");
                    name = sc.nextLine();
                    System.out.print("\nEnter age: ");
                    age = sc.nextInt();
                    System.out.print("\nEnter email: ");
                    email = sc.next();
                    System.out.println();
                    sc.nextLine(); // clears input buffer

                    ps.setInt(1, id);
                    ps.setString(2, name);
                    ps.setInt(3, age);
                    ps.setString(4, email);

                    int rowsInserted = ps.executeUpdate();
                    System.out.println(rowsInserted + " Record(s) Inserted Sucessfully");

                    break;
                case 3:
                    // UPDATE

                    query = "UPDATE test SET name = ?, age = ?, email = ? WHERE id = ?";
                    ps = db.prepareStatement(query);

                    System.out.print("Enter id of record to be update: ");
                    id = sc.nextInt();
                    sc.nextLine();
                    System.out.print("\nEnter Updated Name: ");
                    name = sc.nextLine();
                    System.out.print("\nEnter Updated age: ");
                    age = sc.nextInt();
                    System.out.print("\nEnter Updated email: ");
                    email = sc.next();
                    System.out.println();
                    sc.nextLine(); // clears input buffer

                    ps.setString(1, name);
                    ps.setInt(2, age);
                    ps.setString(3, email);
                    ps.setInt(4, id);
                    int rowsUpdated = ps.executeUpdate();
                    System.out.println(rowsUpdated + " Record(s) Updated Sucessfully");

                    break;
                case 4:
                    // DELETE
                    query = "DELETE FROM test WHERE id = ?";
                    ps = db.prepareStatement(query);
                    System.out.println("Enter id of record to be deleted");
                    id = sc.nextInt();
                    ps.setInt(1, id);

                    int deletedRows = ps.executeUpdate();
                    System.out.println(deletedRows + " Record(s) Deleted Successfully");
                    break;
                case 5:
                    // TRUNCATE
                    System.out.println("Are you sure? You want to truncate the table \'test\'?\n"
                            + "Doing so will delete all of its contents.(y/n)");
                    if (sc.next().charAt(0) == 'y') {
                        st1.execute("TRUNCATE TABLE test");
                    }
                    break;

                case 6:
                    ctd = 'n';
                    break;

                default:
                    break;
                }
            } while (ctd == 'y');

            // Save data and close
            db.close();

        } catch (Exception e) {
            System.err.println(e);
        }

        sc.close();

    }
}
