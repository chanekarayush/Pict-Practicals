# Description of Tables

```sql
mysql> desc Dept;
+---------------+-------------+------+-----+---------+-------+
| Field         | Type        | Null | Key | Default | Extra |
+---------------+-------------+------+-----+---------+-------+
| Dept_id       | int         | NO   | PRI | NULL    |       |
| Dept_name     | varchar(60) | YES  |     | NULL    |       |
| Dept_location | varchar(50) | YES  |     | NULL    |       |
+---------------+-------------+------+-----+---------+-------+
3 rows in set (0.00 sec)

mysql> desc Project;
+---------------+--------------+------+-----+---------+-------+
| Field         | Type         | Null | Key | Default | Extra |
+---------------+--------------+------+-----+---------+-------+
| Proj_id       | int          | NO   | PRI | NULL    |       |
| Dept_id       | int          | YES  | MUL | NULL    |       |
| Proj_name     | varchar(100) | YES  |     | NULL    |       |
| Proj_Location | varchar(100) | YES  |     | NULL    |       |
| Proj_cost     | double(10,2) | YES  |     | NULL    |       |
| Proj_year     | int          | YES  |     | NULL    |       |
+---------------+--------------+------+-----+---------+-------+
6 rows in set (0.00 sec)

mysql> desc Employee;
+--------------+--------------+------+-----+---------+-------+
| Field        | Type         | Null | Key | Default | Extra |
+--------------+--------------+------+-----+---------+-------+
| Emp_id       | int          | NO   | PRI | NULL    |       |
| Dept_id      | int          | YES  | MUL | NULL    |       |
| Emp_fname    | varchar(50)  | YES  |     | NULL    |       |
| Emp_lname    | varchar(50)  | YES  |     | NULL    |       |
| Emp_position | varchar(100) | YES  |     | NULL    |       |
| Emp_salary   | double(10,2) | YES  |     | NULL    |       |
| Emp_joinDate | date         | YES  |     | NULL    |       |
+--------------+--------------+------+-----+---------+-------+
7 rows in set (0.00 sec)
```
## Insert at least 10 records in the employee and other tables accordingly

```sql
-- Department Table
INSERT INTO `Dept` (Dept_id, Dept_name, Dept_location) VALUES
(1, 'HR', 'Mumbai'),
(2, 'Finance', 'Delhi'),
(3, 'IT', 'Bengaluru'),
(4, 'R&D', 'Hyderabad'),
(5, 'Marketing', 'Chennai'),
(6, 'Sales', 'Kolkata'),
(7, 'Legal', 'Pune'),
(8, 'Operations', 'Ahmedabad'),
(9, 'Admin', 'Surat'),
(10, 'Support', 'Jaipur');
Query OK, 10 rows affected (0.01 sec)
Records: 10  Duplicates: 0  Warnings: 0

-- Project Table
INSERT INTO `Project` (Proj_id, Dept_id, Proj_name, Proj_Location, Proj_cost, Proj_year) VALUES
(1, 1, 'Employee Engagement Initiative', 'Mumbai', 50500.00, 2005),
(2, 2, 'Financial Software Upgrade', 'Delhi', 750000.00, 2010),
(3, 3, 'IT Infrastructure Overhaul', 'Bengaluru', 150000.00, 2000),
(4, 4, 'New Product Launch', 'Hyderabad', 200000.00, 2015),
(5, 5, 'Market Expansion Plan', 'Chennai', 175000.00, 2008),
(6, 6, 'Sales Training Program', 'Kolkata', 125000.00, 1998),
(7, 7, 'Legal Compliance Audit', 'Pune', 60000.00, 2020),
(8, 8, 'Operational Efficiency Project', 'Ahmedabad', 300000.00, 2005),
(9, 9, 'Office Renovation', 'Surat', 45000.00, 2012),
(10, 10, 'Customer Feedback System', 'Jaipur', 99000.00, 2018);
Query OK, 10 rows affected (0.00 sec)
Records: 10  Duplicates: 0  Warnings: 0

-- Employee Table
INSERT INTO `Employee` (Emp_id, Dept_id, Emp_fname, Emp_lname, Emp_position, Emp_salary, Emp_joinDate) VALUES
(1, 1, 'Pankaj', 'Patel', 'Manager', 50000.00, '2005-06-15'),
(2, 2, 'Ravi', 'Reddy', 'Analyst', 60000.00, '2010-03-21'),
(3, 3, 'Suresh', 'Sharma', 'Developer', 70000.00, '2000-11-09'),
(4, 4, 'Harish', 'Hegde', 'Researcher', 80000.00, '2015-02-28'),
(5, 5, 'Pranav', 'Pawar', 'Marketing Executive', 75000.00, '2008-07-14'),
(6, 6, 'Rajesh', 'Rao', 'Sales Executive', 65000.00, '1998-10-22'),
(7, 7, 'Sanjay', 'Singh', 'Legal Advisor', 85000.00, '2020-01-17'),
(8, 8, 'Hemant', 'Hooda', 'Operations Manager', 95000.00, '2005-05-24'),
(9, 9, 'Prakash', 'Patil', 'Administrator', 55000.00, '2012-08-30'),
(10, 10, 'Rahul', 'Roy', 'Support Engineer', 45000.00, '2018-12-19');
Query OK, 10 rows affected (0.10 sec)
Records: 10  Duplicates: 0  Warnings: 0
```
## Display all Employee Details with Department `Computer` and `IT` and Employee first name starting with `P` or `H`

```sql
mysql> select * from `Employee` LEFT JOIN Dept ON Employee.Dept_id = Dept.Dept_id WHERE (Dept.Dept_name LIKE 'Computer' OR Dept.Dept_
name LIKE 'IT') AND (Employee.Emp_fname LIKE 'P%' OR Employee.Emp_fname LIKE 'H%');
+--------+---------+-----------+-----------+--------------------------+------------+--------------+---------+-----------+---------------+
| Emp_id | Dept_id | Emp_fname | Emp_lname | Emp_position             | Emp_salary | Emp_joinDate | Dept_id | Dept_name | Dept_location |
+--------+---------+-----------+-----------+--------------------------+------------+--------------+---------+-----------+---------------+
|      4 |       4 | Harish    | Hegde     | Researcher               |   80000.00 | 2015-02-28   |       4 | Computer  | Mumbai        |
|      9 |       9 | Prakash   | Patil     | Administrator            |   55000.00 | 2012-08-30   |       9 | Computer  | Chennai       |
|     11 |      11 | Puneet    | Pandey    | Logistics Manager        |   40000.00 | 2021-04-10   |      11 | IT        | Kolkata       |
|     15 |      15 | Parth     | Pandya    | Purchasing Officer       |   75000.00 | 2014-04-07   |      15 | Computer  | Bengaluru     |
|     19 |      19 | Palash    | Pathak    | Trainer                  |   78000.00 | 2020-07-23   |      19 | Computer  | Surat         |
|     22 |      22 | Harshal   | Handa     | Corporate Strategist     |   96000.00 | 2010-08-16   |      22 | IT        | Delhi         |
|     31 |      31 | Praveen   | Pillai    | Tech Support             |   56000.00 | 2023-05-30   |      31 | IT        | Jaipur        |
|     46 |      46 | Harsh     | Hegde     | Organizational Developer |   87000.00 | 2009-06-18   |      46 | IT        | Ahmedabad     |
+--------+---------+-----------+-----------+--------------------------+------------+--------------+---------+-----------+---------------+
8 rows in set (0.00 sec)
```

## Lists the Number of different Employee Positions

```sql
mysql> SELECT COUNT(DISTINCT Emp_position) FROM Employee;
+------------------------------+
| COUNT(DISTINCT Emp_position) |
+------------------------------+
|                           50 |
+------------------------------+
1 row in set (0.05 sec)

```

## Give 10% increase in Salary of the Employee whose joining year is before 1985.  

```sql
mysql> update employee
    -> set Employee.Emp_salary = Emp_salary * 1.1
    -> where Employee.Emp_joinDate <= '1985-01-01';
Query OK, 5 rows affected (0.10 sec)
Rows matched: 5  Changed: 5  Warnings: 0

mysql> select * from employee where Emp_joinDate <= '1985-01-01';
+--------+---------+-----------+-----------+---------------------+------------+--------------+
| Emp_id | Dept_id | Emp_fname | Emp_lname | Emp_position        | Emp_salary | Emp_joinDate |
+--------+---------+-----------+-----------+---------------------+------------+--------------+
|      1 |       1 | Pankaj    | Patel     | Manager             |   55000.00 | 1980-01-15   |
|      2 |       2 | Ravi      | Reddy     | Analyst             |   66000.00 | 1981-03-21   |
|      3 |       3 | Suresh    | Sharma    | Developer           |   77000.00 | 1982-05-30   |
|      4 |       4 | Harish    | Hegde     | Researcher          |   88000.00 | 1983-07-12   |
|      5 |       5 | Pranav    | Pawar     | Marketing Executive |   82500.00 | 1984-09-24   |
+--------+---------+-----------+-----------+---------------------+------------+--------------+
5 rows in set (0.00 sec)
```

## Delete Department details which location is ‘Mumbai’.  

```sql
mysql> select * from dept where Dept_location LIKE 'Mumbai';
+---------+----------------+---------------+
| Dept_id | Dept_name      | Dept_location |
+---------+----------------+---------------+
|       1 | HR             | Mumbai        |
|       4 | Computer       | Mumbai        |
|       7 | Computer       | Mumbai        |
|      21 | Legal Affairs  | Mumbai        |
|      41 | Sustainability | Mumbai        |
+---------+----------------+---------------+
5 rows in set (0.00 sec)

mysql> delete from Dept where Dept.Dept_location LIKE 'Mumbai';
ERROR 1451 (23000): Cannot delete or update a parent row: a foreign key constraint fails (`assignment_2_dbms`.`employee`, CONSTRAINT `employee_ibfk_1` FOREIGN KEY (`Dept_id`) REFERENCES `dept` (`Dept_id`))
```

## Find the names of Projects with location ‘pune’

```sql
mysql> select * from Project where Proj_location = 'Pune';
+---------+---------+--------------------------------+---------------+-----------+-----------+
| Proj_id | Dept_id | Proj_name                      | Proj_Location | Proj_cost | Proj_year |
+---------+---------+--------------------------------+---------------+-----------+-----------+
|       7 |       7 | Legal Compliance Audit         | Pune          |  60000.00 |      2020 |
|      17 |      17 | Public Relations Campaign      | Pune          | 130000.00 |      2016 |
|      27 |      27 | Investor Relations Improvement | Pune          | 190000.00 |      2006 |
|      37 |      37 | Security System Upgrade        | Pune          | 210000.00 |      2017 |
|      47 |      47 | HR Operations Improvement      | Pune          | 310000.00 |      2010 |
+---------+---------+--------------------------------+---------------+-----------+-----------+
5 rows in set (0.00 sec)
```

## Find the project having cost in between 100000 to 500000. 

```sql
mysql> select * from Project where Proj_cost between 100000 AND 500000;
+---------+---------+--------------------------------------+---------------+-----------+-----------+
| Proj_id | Dept_id | Proj_name                            | Proj_Location | Proj_cost | Proj_year |
+---------+---------+--------------------------------------+---------------+-----------+-----------+
|       3 |       3 | IT Infrastructure Overhaul           | Bengaluru     | 150000.00 |      2000 |
|       4 |       4 | New Product Launch                   | Hyderabad     | 200000.00 |      2015 |
|       5 |       5 | Market Expansion Plan                | Chennai       | 175000.00 |      2008 |
|       6 |       6 | Sales Training Program               | Kolkata       | 125000.00 |      1998 |
|       8 |       8 | Operational Efficiency Project       | Ahmedabad     | 300000.00 |      2005 |
|      11 |      11 | Supply Chain Optimization            | Mumbai        | 470000.00 |      2021 |
|      15 |      15 | Purchasing System Overhaul           | Chennai       | 105000.00 |      2014 |
|      17 |      17 | Public Relations Campaign            | Pune          | 130000.00 |      2016 |
|      18 |      18 | Business Development Strategy        | Ahmedabad     | 450000.00 |      2003 |
|      19 |      19 | Training Program Development         | Surat         | 110000.00 |      2020 |
|      20 |      20 | Procurement Process Improvement      | Jaipur        | 360000.00 |      2013 |
|      24 |      24 | Risk Management Framework            | Hyderabad     | 240000.00 |      2007 |
|      25 |      25 | Government Relations Plan            | Chennai       | 300000.00 |      1995 |
|      27 |      27 | Investor Relations Improvement       | Pune          | 190000.00 |      2006 |
|      28 |      28 | Corporate Communications Plan        | Ahmedabad     | 120000.00 |      2011 |
|      29 |      29 | Human Resources Initiative           | Surat         | 250000.00 |      2012 |
|      31 |      31 | Technical Support System             | Mumbai        | 400000.00 |      2023 |
|      35 |      35 | Environmental Sustainability Project | Chennai       | 100000.00 |      2024 |
|      36 |      36 | Corporate Social Responsibility      | Kolkata       | 490000.00 |      2000 |
|      37 |      37 | Security System Upgrade              | Pune          | 210000.00 |      2017 |
|      38 |      38 | IT Services Enhancement              | Ahmedabad     | 110000.00 |      2013 |
|      41 |      41 | Sustainability Initiative            | Mumbai        | 130000.00 |      2012 |
|      43 |      43 | Compensation and Benefits Review     | Bengaluru     | 150000.00 |      2023 |
|      44 |      44 | Employee Relations Strategy          | Hyderabad     | 180000.00 |      2021 |
|      45 |      45 | Performance Management System        | Chennai       | 250000.00 |      1997 |
|      46 |      46 | Organizational Development Plan      | Kolkata       | 450000.00 |      2009 |
|      47 |      47 | HR Operations Improvement            | Pune          | 310000.00 |      2010 |
|      48 |      48 | Diversity and Inclusion Initiative   | Ahmedabad     | 260000.00 |      1998 |
|      49 |      49 | Learning and Development Program     | Surat         | 100000.00 |      2011 |
|      50 |      50 | Workforce Planning Strategy          | Jaipur        | 220000.00 |      2024 |
+---------+---------+--------------------------------------+---------------+-----------+-----------+
30 rows in set (0.01 sec)
```

## Find the project having maximum price and find average of Project cost

```sql
mysql> select MAX(Proj_cost) FROM Project;
+----------------+
| MAX(Proj_cost) |
+----------------+
|      800000.00 |
+----------------+
1 row in set (0.00 sec)

mysql> select AVG(Proj_cost) FROM Project;
+----------------+
| AVG(Proj_cost) |
+----------------+
|  238370.000000 |
+----------------+
1 row in set (0.00 sec)
```

## Display all employees with Emp _id  and Emp name in decreasing order of Emp_lname

```sql
mysql> SELECT Emp_id, Emp_fname, Emp_lname FROM Employee ORDER BY Emp_lname DESC;
+--------+-----------+-----------+
| Emp_id | Emp_fname | Emp_lname |
+--------+-----------+-----------+
|     13 | Siddharth | Soni      |
|     45 | Siddharth | Sinha     |
|     29 | Sanket    | Sinha     |
|      7 | Sanjay    | Singh     |
|     41 | Saurabh   | Singh     |
|     17 | Suraj     | Shukla    |
|      3 | Suresh    | Sharma    |
|     37 | Shyam     | Sharma    |
|     33 | Sagar     | Sharma    |
|     49 | Suraj     | Saxena    |
|     21 | Sahil     | Saxena    |
|     25 | Satish    | Sarkar    |
|     24 | Rohan     | Roy       |
|     10 | Rahul     | Roy       |
|     40 | Rishi     | Roy       |
|      2 | Ravi      | Reddy     |
|     44 | Rakesh    | Reddy     |
|     28 | Rahul     | Reddy     |
|     16 | Rohit     | Rathore   |
|     32 | Rakesh    | Rathore   |
|      6 | Rajesh    | Rao       |
|     36 | Ranjit    | Rao       |
|     12 | Ramesh    | Ram       |
|     20 | Ritik     | Raj       |
|     48 | Rohan     | Raj       |
|     43 | Pranay    | Purohit   |
|     27 | Pratik    | Purohit   |
|     23 | Piyush    | Pradhan   |
|     47 | Piyush    | Pradhan   |
|     31 | Praveen   | Pillai    |
|      5 | Pranav    | Pawar     |
|     35 | Prashant  | Pawar     |
|     39 | Praveen   | Patil     |
|      9 | Prakash   | Patil     |
|     19 | Palash    | Pathak    |
|      1 | Pankaj    | Patel     |
|     15 | Parth     | Pandya    |
|     11 | Puneet    | Pandey    |
|     34 | Hitesh    | Hooda     |
|     38 | Himanshu  | Hooda     |
|      8 | Hemant    | Hooda     |
|     14 | Himanshu  | Hiran     |
|     50 | Himanshu  | Hiran     |
|      4 | Harish    | Hegde     |
|     30 | Hemang    | Hegde     |
|     26 | Hiren     | Hegde     |
|     42 | Harish    | Hegde     |
|     46 | Harsh     | Hegde     |
|     18 | Hrithik   | Harsha    |
|     22 | Harshal   | Handa     |
+--------+-----------+-----------+
50 rows in set (0.01 sec)
```
## Display Proj_name,Proj_location ,Proj_cost of all project started in 2004,2005,2007

```sql
mysql> select Proj_name,Proj_location ,Proj_cost from Project where Proj_year = 2004 OR Proj_year = 2005 OR Proj_year = 2007;
+--------------------------------+---------------+-----------+
| Proj_name                      | Proj_location | Proj_cost |
+--------------------------------+---------------+-----------+
| Employee Engagement Initiative | Mumbai        |  50500.00 |
| Operational Efficiency Project | Ahmedabad     | 300000.00 |
| Risk Management Framework      | Hyderabad     | 240000.00 |
+--------------------------------+---------------+-----------+
3 rows in set (0.00 sec)

mysql> select Proj_name,Proj_location ,Proj_cost, Proj_year from Project where Proj_year = 2004 OR Proj_year = 2005 OR Proj_year = 20
07;
+--------------------------------+---------------+-----------+-----------+
| Proj_name                      | Proj_location | Proj_cost | Proj_year |
+--------------------------------+---------------+-----------+-----------+
| Employee Engagement Initiative | Mumbai        |  50500.00 |      2005 |
| Operational Efficiency Project | Ahmedabad     | 300000.00 |      2005 |
| Risk Management Framework      | Hyderabad     | 240000.00 |      2007 |
+--------------------------------+---------------+-----------+-----------+
3 rows in set (0.00 sec)
```

## Additional Queries
### All employee names above earning more than 5000 in Computer Dept

```sql
mysql> select Emp_fname, Emp_lname FROM Employee LEFT JOIN Dept ON Employee.Dept_id = Dept.Dept_id WHERE Emp_salary > 5000 AND Dept.Dept_name = 'Computer';
+-----------+-----------+
| Emp_fname | Emp_lname |
+-----------+-----------+
| Harish    | Hegde     |
| Sanjay    | Singh     |
| Prakash   | Patil     |
| Parth     | Pandya    |
| Palash    | Pathak    |
| Satish    | Sarkar    |
| Sagar     | Sharma    |
| Shyam     | Sharma    |
+-----------+-----------+
8 rows in set (0.00 sec)
```

### Projects which have names containing `K`
```sql
mysql> select * from Project where Proj_name LIKE '%K%';
+---------+---------+-----------------------------+---------------+-----------+-----------+
| Proj_id | Dept_id | Proj_name                   | Proj_Location | Proj_cost | Proj_year |
+---------+---------+-----------------------------+---------------+-----------+-----------+
|       5 |       5 | Market Expansion Plan       | Chennai       | 175000.00 |      2008 |
|      10 |      10 | Customer Feedback System    | Jaipur        |  99000.00 |      2018 |
|      24 |      24 | Risk Management Framework   | Hyderabad     | 240000.00 |      2007 |
|      50 |      50 | Workforce Planning Strategy | Jaipur        | 220000.00 |      2024 |
+---------+---------+-----------------------------+---------------+-----------+-----------+
4 rows in set (0.00 sec)
```

### Dept name and id with project before 2010

```sql
mysql> select Dept.Dept_id, Dept_name, Proj_year from dept left join project on Dept.Dept_id = Project.Dept_id WHERE Project.Proj_year <= 2010;
+---------+---------------------------------+-----------+
| Dept_id | Dept_name                       | Proj_year |
+---------+---------------------------------+-----------+
|       1 | HR                              |      2005 |
|       2 | Finance                         |      2010 |
|       3 | IT                              |      2000 |
|       5 | Marketing                       |      2008 |
|       6 | Sales                           |      1998 |
|       8 | Operations                      |      2005 |
|      13 | Product Development             |      1995 |
|      16 | Engineering                     |      1990 |
|      18 | Business Development            |      2003 |
|      22 | IT                              |      2010 |
|      24 | Risk Management                 |      2007 |
|      25 | Computer                        |      1995 |
|      27 | Investor Relations              |      2006 |
|      30 | Finance and Accounting          |      2002 |
|      32 | Manufacturing                   |      2001 |
|      34 | Corporate Development           |      1999 |
|      36 | Corporate Social Responsibility |      2000 |
|      45 | Performance Management          |      1997 |
|      46 | IT                              |      2009 |
|      47 | HR Operations                   |      2010 |
|      48 | IT                              |      1998 |
+---------+---------------------------------+-----------+
21 rows in set (0.00 sec)
```

### Employees joined after 01-01-2004 in IT department

```sql
ERROR 1525 (HY000): Incorrect DATE value: '01-01-2004'
mysql> select Employee.Emp_id, Emp_fname, Emp_lname, Emp_joinDate FROM Employee left join Dept ON Employee.Dept_id = Dept.Dept_id WHERE Emp_joinDate > '2004-01-01' AND Dept_name = 'IT';
+--------+-----------+-----------+--------------+
| Emp_id | Emp_fname | Emp_lname | Emp_joinDate |
+--------+-----------+-----------+--------------+
|     11 | Puneet    | Pandey    | 2014-01-16   |
|     22 | Harshal   | Handa     | 2013-02-11   |
|     28 | Rahul     | Reddy     | 2004-08-02   |
+--------+-----------+-----------+--------------+
3 rows in set (0.00 sec)
```

### Top 10 Employees with highest pay

```sql
mysql> select * from Employee order by Emp_salary DESC LIMIT 10;
+--------+---------+-----------+-----------+--------------------------+------------+--------------+
| Emp_id | Dept_id | Emp_fname | Emp_lname | Emp_position             | Emp_salary | Emp_joinDate |
+--------+---------+-----------+-----------+--------------------------+------------+--------------+
|     22 |      22 | Harshal   | Handa     | Corporate Strategist     |   96000.00 | 2013-02-11   |
|      8 |       8 | Hemant    | Hooda     | Operations Manager       |   95000.00 | 2018-04-27   |
|     38 |      38 | Himanshu  | Hooda     | IT Service Lead          |   93000.00 | 1993-03-12   |
|     16 |      16 | Rohit     | Rathore   | Engineer                 |   92000.00 | 2005-01-10   |
|     24 |      24 | Rohan     | Roy       | Risk Manager             |   91000.00 | 1987-03-12   |
|     13 |      13 | Siddharth | Soni      | Product Developer        |   90000.00 | 1999-08-04   |
|      4 |       4 | Harish    | Hegde     | Researcher               |   88000.00 | 1983-07-12   |
|     46 |      46 | Harsh     | Hegde     | Organizational Developer |   87000.00 | 2000-08-29   |
|     20 |      20 | Ritik     | Raj       | Procurement Specialist   |   87000.00 | 1996-06-11   |
|     33 |      33 | Sagar     | Sharma    | Supply Chain Manager     |   87000.00 | 1990-10-09   |
+--------+---------+-----------+-----------+--------------------------+------------+--------------+
10 rows in set (0.00 sec)
```