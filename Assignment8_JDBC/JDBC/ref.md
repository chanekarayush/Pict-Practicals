
```java
package jdbc_31311;



import java.util.*;

import java.sql.*;



public class JDBC_31311 {

	static String url = "jdbc:mysql://10.10.13.97/te31311_db";

	static String user = "te31311";

	static String password = "te31311";

	public static void main(String args[]) {

		Scanner sc = new Scanner(System.in);

		// accept user, password and server name

		

		PreparedStatement ps;

		String query = "";

		try {

			Class.forName("com.mysql.jdbc.Driver");

			Connection db = DriverManager.getConnection(url, user, password);

			Statement st1 = db.createStatement();

			

			if ( db != null && !db.isClosed()) {

				System.out.println("Database Connection Successful");

			}

			else {

				System.out.println("Database not found or is closed");

				throw new SQLException("Invalid Database url or state");

			}

			

			// SELECT

			query= "USE te31311_db";

			st1.executeQuery(query);

			query = "SELECT * FROM test";

			ResultSet rs1 = st1.executeQuery(query);

			

			while(rs1.next()) {

				System.out.println(rs1.getInt(1)+ "\t" + rs1.getString(2) + "\t" +rs1.getString(3) + "\t" +rs1.getString(4));

			}

			// INSERT

			

			query = "INSERT INTO test VALUES(?,?,?,?)";

			ps = db.prepareStatement(query);

			System.out.print("Enter id: ");

			int id = sc.nextInt();

			System.out.print("\nEnter Name");

			String name = sc.nextLine();

			sc.next();

			System.out.print("\nEnter age");

			int age = sc.nextInt();

			

			// UPDATE

			

			

			// DROP

			

			

			// DELETE

			

			

			// Save data and close

			db.commit();

			db.close();

		}catch(Exception e) {System.err.println(e);}

	}

}
```