file:///D:/Coding-practice/PICT_Practicals/Pict-Practicals/assignment12/mongoconnect/src/App.java
### java.util.NoSuchElementException: next on empty iterator

occurred in the presentation compiler.

presentation compiler configuration:
Scala version: 3.3.3
Classpath:
<HOME>\AppData\Local\Coursier\cache\v1\https\repo1.maven.org\maven2\org\scala-lang\scala3-library_3\3.3.3\scala3-library_3-3.3.3.jar [exists ], <HOME>\AppData\Local\Coursier\cache\v1\https\repo1.maven.org\maven2\org\scala-lang\scala-library\2.13.12\scala-library-2.13.12.jar [exists ]
Options:



action parameters:
uri: file:///D:/Coding-practice/PICT_Practicals/Pict-Practicals/assignment12/mongoconnect/src/App.java
text:
```scala
import com.mongodb.MongoException;
import com.mongodb.client.*;
import com.mongodb.client.model.Filters;
import org.bson.Document;

import java.util.Scanner;

import static com.mongodb.client.model.Updates.*;

public class App {
    private static MongoClient client;
    private static MongoDatabase db;
    private static MongoCollection<Document> coll;

    public static void main(String[] args) {
        String url = "mongodb+srv://admin:admin@connect.1mf9v.mongodb.net/?retryWrites=true&w=majority&appName=connect";
        System.out.println("Welcome to K-III DB");
        System.err.print("Please wait while we are connecting to MongoDB");
        for (int i = 0; i < 100000; i++) {
            System.out.print(".");
            System.out.print(".");
            System.out.print(".");
            System.out.print(".");
            System.out.print(".");
            System.out.print(".");
            System.out.print("\b");
            System.out.print("\b");
            System.out.print("\b");
            System.out.print("\b");
            System.out.print("\b");
            System.out.print("\b");
        }
        try {
            client = MongoClients.create(url);
            db = client.getDatabase("mydb");
            coll = db.getCollection("myColl");

            Scanner scanner = new Scanner(System.in);
            int choice;

            do {
                displayMenu();
                choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                switch (choice) {
                case 1:
                    createUser(scanner);
                    break;
                case 2:
                    findUser(scanner);
                    break;
                case 3:
                    updateUser(scanner);
                    break;
                case 4:
                    deleteUser(scanner);
                    break;
                case 5:
                    showAllUsers();
                    break;
                case 6:
                    System.out.println("Exiting the program.");
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
                }
            } while (choice != 6);

        } catch (MongoException e) {
            System.out.println("An error occurred while connecting with MongoDB: " + e);
        } finally {
            if (client != null) {
                client.close();
            }
        }
    }

    private static void displayMenu() {
        System.out.println("\nMenu:");
        System.out.println("1. Create User");
        System.out.println("2. Find User");
        System.out.println("3. Update User");
        System.out.println("4. Delete User");
        System.out.println("5. Show All Users");
        System.out.println("6. Exit");
        System.out.print("Enter your choice: ");
    }

    private static void createUser(Scanner scanner) {
        System.out.print("Enter name: ");
        String name = scanner.nextLine();
        System.out.print("Enter Roll: ");
        int roll = scanner.nextInt();
        scanner.nextLine();
        System.out.print("Enter Department: ");
        String department = scanner.nextLine();

        Document doc = new Document("name", name).append("Roll", roll).append("Department", department);
        coll.insertOne(doc);
        System.out.println("User created: " + doc.toJson());
    }

    private static void findUser(Scanner scanner) {
        System.out.print("Enter name to find: ");
        String name = scanner.nextLine();
        Document foundUser = coll.find(Filters.eq("name", name)).first();
        if (foundUser != null) {
            System.out.println("User found: " + foundUser.toJson());
        } else {
            System.out.println("User not found.");
        }
    }

    private static void updateUser(Scanner scanner) {
        System.out.print("Enter name of the user to update: ");
        String name = scanner.nextLine();
        Document foundUser = coll.find(Filters.eq("name", name)).first();

        if (foundUser != null) {
            System.out.println("Available fields to update: ");
            System.out.println("1. Name");
            System.out.println("2. Roll");
            System.out.println("3. Department");
            System.out.print("Choose a field to update (1-3): ");
            int fieldChoice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (fieldChoice) {
            case 1:
                System.out.print("Enter new name: ");
                String newName = scanner.nextLine();
                coll.updateOne(Filters.eq("name", name), set("name", newName));
                System.out.println("User name updated.");
                break;
            case 2:
                System.out.print("Enter new Roll: ");
                int newRoll = scanner.nextInt();
                coll.updateOne(Filters.eq("name", name), set("Roll", newRoll));
                System.out.println("User Roll updated.");
                break;
            case 3:
                System.out.print("Enter new Department: ");
                String newDepartment = scanner.nextLine();
                coll.updateOne(Filters.eq("name", name), set("Department", newDepartment));
                System.out.println("User Department updated.");
                break;
            default:
                System.out.println("Invalid choice. No updates made.");
            }

            // Display the updated user
            Document updatedUser = coll.find(Filters.eq("name", name)).first();
            System.out.println("Updated User: " + updatedUser.toJson());
        } else {
            System.out.println("User not found.");
        }
    }

    private static void deleteUser(Scanner scanner) {
        System.out.print("Enter name of the user to delete: ");
        String name = scanner.nextLine();
        coll.deleteOne(Filters.eq("name", name));
        System.out.println("User deleted.");

        // Verify deletion
        Document foundUser = coll.find(Filters.eq("name", name)).first();
        if (foundUser == null) {
            System.out.println("User not found after deletion.");
        } else {
            System.out.println("User still exists.");
        }
    }

    private static void showAllUsers() {
        System.out.println("Users in the database:");
        for (Document doc : coll.find()) {
            System.out.println(doc.toJson());
        }
    }
}
```



#### Error stacktrace:

```
scala.collection.Iterator$$anon$19.next(Iterator.scala:973)
	scala.collection.Iterator$$anon$19.next(Iterator.scala:971)
	scala.collection.mutable.MutationTracker$CheckedIterator.next(MutationTracker.scala:76)
	scala.collection.IterableOps.head(Iterable.scala:222)
	scala.collection.IterableOps.head$(Iterable.scala:222)
	scala.collection.AbstractIterable.head(Iterable.scala:933)
	dotty.tools.dotc.interactive.InteractiveDriver.run(InteractiveDriver.scala:168)
	scala.meta.internal.pc.MetalsDriver.run(MetalsDriver.scala:45)
	scala.meta.internal.pc.WithCompilationUnit.<init>(WithCompilationUnit.scala:28)
	scala.meta.internal.pc.SimpleCollector.<init>(PcCollector.scala:373)
	scala.meta.internal.pc.PcSemanticTokensProvider$Collector$.<init>(PcSemanticTokensProvider.scala:61)
	scala.meta.internal.pc.PcSemanticTokensProvider.Collector$lzyINIT1(PcSemanticTokensProvider.scala:61)
	scala.meta.internal.pc.PcSemanticTokensProvider.Collector(PcSemanticTokensProvider.scala:61)
	scala.meta.internal.pc.PcSemanticTokensProvider.provide(PcSemanticTokensProvider.scala:90)
	scala.meta.internal.pc.ScalaPresentationCompiler.semanticTokens$$anonfun$1(ScalaPresentationCompiler.scala:117)
```
#### Short summary: 

java.util.NoSuchElementException: next on empty iterator