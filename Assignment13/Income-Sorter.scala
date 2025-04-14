import org.apache.spark.sql.types._
import org.apache.spark.sql.functions._

// Step 1: Define the schema for a single column
val schema = new StructType().add("Expense", DoubleType)

// Step 2: Load the CSV
val df = spark.read.option("header", "true").schema(schema).csv("D:/Coding-practice/Pict-Practicals/Assignment13/Expense.csv")

// Step 3: Sort by Expense in descending order
val sorted = df.orderBy(col("Expense").desc)

// Step 4: Show the sorted data
sorted.show()
sorted.show(numRows = Int.MaxValue)


