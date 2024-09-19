# Assignment 8
## Roll number : `31311`

## **Java Database Connection Program Output**

## SELECT
```powershell
PS D:\Coding-practice\PICT_Practicals\Pict-Practicals>  & 'C:\Program Files\Java\jdk-22\bin\java.exe' '@C:\Users\chane\AppData\Local\Temp\cp_d1mt243hhoqzd0wafljovragr.argfile' 'assignment8.App'
Successfully Connected to databasejdbc:mysql://127.0.0.1:3306/assignment_8_dbms! 

Enter:
1. Display all records from table
2. Insert new records
3. Update existing records
4. Delete existing records
5. Truncate Table
6. Exit
1
+-----------------------------------------------------------------------------------------------------+
| 1          | Jon Snow                  | 30                   | jon.snow@example.com                |
| 2          | Arya Stark                | 20                   | arya.stark@example.com              |
| 3          | Sansa Stark               | 25                   | sansa.stark@example.com             |
| 4          | Bran Stark                | 18                   | bran.stark@example.com              |
| 5          | Tyrion Lannister          | 35                   | tyrion.lannister@example.com        |
| 6          | Daenerys Targaryen        | 28                   | daenerys.targaryen@example.com      |
| 7          | Jaime Lannister           | 40                   | jaime.lannister@example.com         |
| 8          | Cersei Lannister          | 42                   | cersei.lannister@example.com        |
| 9          | Samwell Tarly             | 32                   | samwell.tarly@example.com           |
| 10         | Theon Greyjoy             | 27                   | theon.greyjoy@example.com           |
| 11         | K Drogo                   | 45                   | khal.drogo@example.com              |
+-----------------------------------------------------------------------------------------------------+
```
## UPDATE
```powershell
Enter:
1. Display all records from table
2. Insert new records
3. Update existing records
4. Delete existing records
5. Truncate Table
6. Exit
3
Enter id of record to be update: 11

Enter Updated Name: Khal Drogo

Enter Updated age: 40

Enter Updated email: khal.drogo@example.com

1 Record(s) Updated Sucessfully
Enter:
1. Display all records from table
2. Insert new records
3. Update existing records
4. Delete existing records
5. Truncate Table
6. Exit
1
+-----------------------------------------------------------------------------------------------------+
| 1          | Jon Snow                  | 30                   | jon.snow@example.com                |
| 2          | Arya Stark                | 20                   | arya.stark@example.com              |
| 3          | Sansa Stark               | 25                   | sansa.stark@example.com             |
| 4          | Bran Stark                | 18                   | bran.stark@example.com              |
| 5          | Tyrion Lannister          | 35                   | tyrion.lannister@example.com        |
| 6          | Daenerys Targaryen        | 28                   | daenerys.targaryen@example.com      |
| 7          | Jaime Lannister           | 40                   | jaime.lannister@example.com         |
| 8          | Cersei Lannister          | 42                   | cersei.lannister@example.com        |
| 9          | Samwell Tarly             | 32                   | samwell.tarly@example.com           |
| 10         | Theon Greyjoy             | 27                   | theon.greyjoy@example.com           |
| 11         | Khal Drogo                | 40                   | khal.drogo@example.com              |
+-----------------------------------------------------------------------------------------------------+
```

## Insert
```powershell
Enter:
1. Display all records from table
2. Insert new records
3. Update existing records
4. Delete existing records
5. Truncate Table
6. Exit
2
Enter id: 12

Enter Name: Tywin Lannister

Enter age: 65

Enter email: tywin.lannister@example.com

1 Record(s) Inserted Sucessfully
Enter:
1. Display all records from table
2. Insert new records
3. Update existing records
4. Delete existing records
5. Truncate Table
6. Exit
1
+-----------------------------------------------------------------------------------------------------+
| 1          | Jon Snow                  | 30                   | jon.snow@example.com                |
| 2          | Arya Stark                | 20                   | arya.stark@example.com              |
| 3          | Sansa Stark               | 25                   | sansa.stark@example.com             |
| 4          | Bran Stark                | 18                   | bran.stark@example.com              |
| 5          | Tyrion Lannister          | 35                   | tyrion.lannister@example.com        |
| 6          | Daenerys Targaryen        | 28                   | daenerys.targaryen@example.com      |
| 7          | Jaime Lannister           | 40                   | jaime.lannister@example.com         |
| 8          | Cersei Lannister          | 42                   | cersei.lannister@example.com        |
| 9          | Samwell Tarly             | 32                   | samwell.tarly@example.com           |
| 10         | Theon Greyjoy             | 27                   | theon.greyjoy@example.com           |
| 11         | Khal Drogo                | 40                   | khal.drogo@example.com              |
| 12         | Tywin Lannister           | 65                   | tywin.lannister@example.com         |
+-----------------------------------------------------------------------------------------------------+
```

## DELETE
```powershell
Enter:
1. Display all records from table
2. Insert new records
3. Update existing records
4. Delete existing records
5. Truncate Table
6. Exit
4
Enter id of record to be deleted
11
1 Record(s) Deleted Successfully
Enter:
1. Display all records from table
2. Insert new records
3. Update existing records
4. Delete existing records
5. Truncate Table
6. Exit
1
+-----------------------------------------------------------------------------------------------------+
| 1          | Jon Snow                  | 30                   | jon.snow@example.com                |
| 2          | Arya Stark                | 20                   | arya.stark@example.com              |
| 3          | Sansa Stark               | 25                   | sansa.stark@example.com             |
| 4          | Bran Stark                | 18                   | bran.stark@example.com              |
| 5          | Tyrion Lannister          | 35                   | tyrion.lannister@example.com        |
| 6          | Daenerys Targaryen        | 28                   | daenerys.targaryen@example.com      |
| 7          | Jaime Lannister           | 40                   | jaime.lannister@example.com         |
| 8          | Cersei Lannister          | 42                   | cersei.lannister@example.com        |
| 9          | Samwell Tarly             | 32                   | samwell.tarly@example.com           |
| 10         | Theon Greyjoy             | 27                   | theon.greyjoy@example.com           |
| 12         | Tywin Lannister           | 65                   | tywin.lannister@example.com         |
+-----------------------------------------------------------------------------------------------------+
Enter:
1. Display all records from table
2. Insert new records
3. Update existing records
4. Delete existing records
5. Truncate Table
6. Exit
4
Enter id of record to be deleted
12
1 Record(s) Deleted Successfully
Enter:
1. Display all records from table
2. Insert new records
3. Update existing records
4. Delete existing records
5. Truncate Table
6. Exit
1
+-----------------------------------------------------------------------------------------------------+
| 1          | Jon Snow                  | 30                   | jon.snow@example.com                |
| 2          | Arya Stark                | 20                   | arya.stark@example.com              |
| 3          | Sansa Stark               | 25                   | sansa.stark@example.com             |
| 4          | Bran Stark                | 18                   | bran.stark@example.com              |
| 5          | Tyrion Lannister          | 35                   | tyrion.lannister@example.com        |
| 6          | Daenerys Targaryen        | 28                   | daenerys.targaryen@example.com      |
| 7          | Jaime Lannister           | 40                   | jaime.lannister@example.com         |
| 8          | Cersei Lannister          | 42                   | cersei.lannister@example.com        |
| 9          | Samwell Tarly             | 32                   | samwell.tarly@example.com           |
| 10         | Theon Greyjoy             | 27                   | theon.greyjoy@example.com           |
+-----------------------------------------------------------------------------------------------------+
```
## TRUCATE (With warning)
```powershell
Enter:
1. Display all records from table
2. Insert new records
3. Update existing records
4. Delete existing records
5. Truncate Table
6. Exit
5
Are you sure? You want to truncate the table 'test'?
Doing so will delete all of its contents.(y/n)
n
Enter:
1. Display all records from table
2. Insert new records
3. Update existing records
4. Delete existing records
5. Truncate Table
6. Exit
5
Are you sure? You want to truncate the table 'test'?
Doing so will delete all of its contents.(y/n)
y
Enter:
1. Display all records from table
2. Insert new records
3. Update existing records
4. Delete existing records
5. Truncate Table
6. Exit
1
+-----------------------------------------------------------------------------------------------------+
+-----------------------------------------------------------------------------------------------------+
```
## Exit
```powershell
Enter:
1. Display all records from table
2. Insert new records
3. Update existing records
4. Delete existing records
5. Truncate Table
6. Exit
6
PS D:\Coding-practice\PICT_Practicals\Pict-Practicals> 
```