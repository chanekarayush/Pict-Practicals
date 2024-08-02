# Assignment 3
## **Queries**

## 1. Find Employee details and Department details using NATURAL JOIN.  
```sql
mysql> SELECT * FROM EMPLOYEE NATURAL JOIN DEPT;
+---------+--------+-------------+-----------+-------------------------------------------+------------+--------------+-----------+-----------+
| Dept_id | Emp_id | Emp_fname   | Emp_lname | Emp_Position                              | Emp_salary | Emp_JoinDate | Dept_name | location  |
+---------+--------+-------------+-----------+-------------------------------------------+------------+--------------+-----------+-----------+
|       1 |     15 | Andrea      | Simmons   | Horticultural therapist                   |   94541.91 | 2019-12-12   | HR        | Pune      |
|       1 |     16 | Jasmine     | Young     | Naval architect                           |   87026.10 | 2020-01-02   | HR        | Pune      |
|       1 |     23 | Jeffrey     | Good      | Animator                                  |   80860.01 | 2023-05-07   | HR        | Pune      |
|       1 |     25 | Steven      | Bates     | Counselling psychologist                  |   69494.88 | 2020-01-17   | HR        | Pune      |
|       1 |     31 | Kimberly    | Hardin    | Engineer, electrical                      |  110751.56 | 2023-12-01   | HR        | Pune      |
|       1 |     44 | William     | Wood      | Sports coach                              |   63486.09 | 2020-04-29   | HR        | Pune      |
|       2 |      9 | Monica      | Smith     | Economist                                 |   75508.04 | 2023-11-22   | CS        | Delhi     |
|       2 |     11 | Judith      | Gibbs     | Customer service manager                  |   54976.45 | 2022-07-31   | CS        | Delhi     |
|       2 |     24 | Joseph      | Munoz     | Airline pilot                             |   50381.89 | 2024-03-24   | CS        | Delhi     |
|       2 |     32 | Nicole      | Matthews  | Engineering geologist                     |  103022.36 | 2021-11-05   | CS        | Delhi     |
|       2 |     34 | Doris       | Ford      | Broadcast presenter                       |  106042.87 | 2020-05-03   | CS        | Delhi     |
|       2 |     46 | Jesse       | Morgan    | Technical sales engineer                  |   82008.04 | 2022-07-05   | CS        | Delhi     |
|       3 |      1 | Sean        | Dixon     | Engineer, structural                      |   62729.33 | 2021-12-16   | Marketing | Hyderabad |
|       3 |      6 | Jessica     | Acosta    | Minerals surveyor                         |   53033.36 | 2024-04-21   | Marketing | Hyderabad |
|       3 |     12 | Rachel      | Kelly     | Transport planner                         |   95577.11 | 2022-08-16   | Marketing | Hyderabad |
|       3 |     21 | Gary        | Boone     | Toxicologist                              |   77425.01 | 2023-08-31   | Marketing | Hyderabad |
|       3 |     22 | Charles     | Greene    | Field seismologist                        |   61007.17 | 2024-05-09   | Marketing | Hyderabad |
|       3 |     26 | Ashley      | Becker    | Doctor, general practice                  |   52927.94 | 2020-12-03   | Marketing | Hyderabad |
|       3 |     28 | Paul        | Dorsey    | Programmer, systems                       |  117457.77 | 2019-12-28   | Marketing | Hyderabad |
|       3 |     39 | Joseph      | Rodriguez | Runner, broadcasting/film/video           |   78683.76 | 2022-04-19   | Marketing | Hyderabad |
|       3 |     40 | Nicole      | Johnson   | Trading standards officer                 |   65234.13 | 2022-11-20   | Marketing | Hyderabad |
|       3 |     41 | Denise      | Romero    | Logistics and distribution manager        |  112492.86 | 2022-05-29   | Marketing | Hyderabad |
|       3 |     42 | Stephanie   | Walton    | Sound technician, broadcasting/film/video |   62439.65 | 2022-08-20   | Marketing | Hyderabad |
|       3 |     43 | Ralph       | Myers     | Minerals surveyor                         |   84585.37 | 2023-04-15   | Marketing | Hyderabad |
|       3 |     47 | Veronica    | Fisher    | Outdoor activities/education manager      |  114460.17 | 2023-06-20   | Marketing | Hyderabad |
|       4 |      3 | Christopher | Waller    | Information systems manager               |   73797.81 | 2022-11-30   | Sales     | Mumbai    |
|       4 |      4 | Michael     | Page      | Doctor, hospital                          |  103024.16 | 2021-10-19   | Sales     | Mumbai    |
|       4 |      5 | Chris       | Love      | Personnel officer                         |   91209.56 | 2020-05-03   | Sales     | Mumbai    |
|       4 |      7 | Charles     | Powers    | Surveyor, planning and development        |   54422.23 | 2022-12-12   | Sales     | Mumbai    |
|       4 |      8 | Ray         | Reed      | Physiological scientist                   |  113763.16 | 2023-06-25   | Sales     | Mumbai    |
|       4 |     14 | Dylan       | Roberts   | Tourism officer                           |   53083.73 | 2021-06-16   | Sales     | Mumbai    |
|       4 |     17 | Maria       | Lam       | Community pharmacist                      |  105383.54 | 2021-05-23   | Sales     | Mumbai    |
|       4 |     18 | Brittany    | Lopez     | Physicist, medical                        |   81685.18 | 2021-07-01   | Sales     | Mumbai    |
|       4 |     19 | Scott       | Green     | Tourism officer                           |   59337.63 | 2023-05-27   | Sales     | Mumbai    |
|       4 |     27 | Julie       | Ward      | Optometrist                               |   83195.32 | 2024-02-01   | Sales     | Mumbai    |
|       4 |     35 | Stephanie   | Little    | Development worker, community             |   93999.09 | 2022-03-06   | Sales     | Mumbai    |
|       4 |     48 | Austin      | Estes     | Ecologist                                 |  118381.60 | 2022-06-03   | Sales     | Mumbai    |
|       4 |     49 | Amber       | Peterson  | Architectural technologist                |  101187.98 | 2023-02-12   | Sales     | Mumbai    |
|       4 |     50 | Tammy       | Lloyd     | Scientist, research (medical)             |   55546.44 | 2024-06-14   | Sales     | Mumbai    |
|       5 |      2 | Dawn        | Price     | Colour technologist                       |  101283.37 | 2021-01-23   | Finance   | Pune      |
|       5 |     10 | Laura       | Mosley    | Neurosurgeon                              |   62466.80 | 2020-11-05   | Finance   | Pune      |
|       5 |     13 | Walter      | Hamilton  | Scientist, product/process development    |   75472.34 | 2022-01-07   | Finance   | Pune      |
|       5 |     20 | Jessica     | Hernandez | Public house manager                      |  115944.60 | 2022-06-13   | Finance   | Pune      |
|       5 |     29 | Elizabeth   | Bond      | Producer, radio                           |  111477.50 | 2020-06-10   | Finance   | Pune      |
|       5 |     30 | Melissa     | Johnson   | Designer, interior/spatial                |  109533.90 | 2022-01-28   | Finance   | Pune      |
|       5 |     33 | David       | Smith     | Financial manager                         |   95738.29 | 2021-01-11   | Finance   | Pune      |
|       5 |     36 | Paul        | Garcia    | Homeopath                                 |   50808.87 | 2020-10-08   | Finance   | Pune      |
|       5 |     37 | James       | Davis     | Armed forces operational officer          |   65759.86 | 2024-04-24   | Finance   | Pune      |
|       5 |     38 | Diane       | Aguilar   | Facilities manager                        |   80203.22 | 2020-11-28   | Finance   | Pune      |
|       5 |     45 | Dominic     | Hudson    | Medical physicist                         |   79721.15 | 2023-11-29   | Finance   | Pune      |
+---------+--------+-------------+-----------+-------------------------------------------+------------+--------------+-----------+-----------+
50 rows in set (0.01 sec)
```
## 2. Find the emp_fname,Emp_position,location,Emp_JoinDate who have same Dept id. 



## 3. Find the Employee details ,Proj_id,Project cost who does not have Project location as ‘Hyderabad’
```sql
SELECT employee.Emp_fname,employee.Emp_position,Dept.location,employee.Emp_JoinDate FROM employee LEFT JOIN dept ON employee.Dept_id = dept.Dept_id GROUPBY Dept_id;
```