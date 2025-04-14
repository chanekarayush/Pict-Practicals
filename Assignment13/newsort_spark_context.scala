val rdd = sc.textFile("D:/Coding-practice/Pict-Practicals/Assignment13/Expense.csv")

val expenses = rdd
  .zipWithIndex()
  .filter(_._2 != 0)            // Skip header
  .map { case (line, _) =>
    line.trim.toDouble
  }

val sorted = expenses.sortBy(x => x, ascending = false)

sorted.take(100).foreach(println)
