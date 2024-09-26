# Assignment 10 
## Roll no. `31311`

## Insert into collections
```js
db.emp.insertMany([
  { empId: 2, empName: 'Winston', emp_deptID: 102, empSal: 85000 },
  { empId: 3, empName: 'Charon', emp_deptID: 103, empSal: 78000 },
  { empId: 4, empName: 'Santino D`Antonio', emp_deptID: 104, empSal: 72000 },
  { empId: 5, empName: 'Marcus', emp_deptID: 101, empSal: 67000 },
  { empId: 6, empName: 'Aurelio', emp_deptID: 105, empSal: 64000 },
  { empId: 7, empName: 'Sofia Al-Azwar', emp_deptID: 102, empSal: 82000 },
  { empId: 8, empName: 'The Adjudicator', emp_deptID: 106, empSal: 79000 },
  { empId: 9, empName: 'Zero', emp_deptID: 107, empSal: 68000 },
  { empId: 10, empName: 'Cassian', emp_deptID: 101, empSal: 71000 },
  { empId: 11, empName: 'Bowery King', emp_deptID: 108, empSal: 90000 },
  { empId: 12, empName: 'Ares', emp_deptID: 109, empSal: 74000 },
  { empId: 13, empName: 'Viggo Tarasov', emp_deptID: 103, empSal: 93000 },
  { empId: 14, empName: 'Iosef Tarasov', emp_deptID: 104, empSal: 55000 },
  { empId: 15, empName: 'Helen Wick', emp_deptID: 110, empSal: 95000 },
  { empId: 16, empName: 'Perkins', emp_deptID: 105, empSal: 68000 },
  { empId: 17, empName: 'Abram Tarasov', emp_deptID: 103, empSal: 70000 },
  { empId: 18, empName: 'Gianna D`Antonio', emp_deptID: 104, empSal: 87000 },
  { empId: 19, empName: 'Jimmy the Cop', emp_deptID: 107, empSal: 60000 },
  { empId: 20, empName: 'Earl', emp_deptID: 109, empSal: 76000 },
]);
```
## Count the Total Number of Employees

```js
Atlas atlas-aniack-shard-0 [primary] db> db.emp.aggregate([ { $group: { _id: null, totalEmployees: { $sum: 1 } } }] ).pretty()
[ { _id: null, totalEmployees: 20 } ]
Atlas atlas-aniack-shard-0 [primary] db>
```

## Calculate the Total Salary of All Employees
```js
Atlas atlas-aniack-shard-0 [primary] db> db.emp.aggregate([ { $group: {_id:null, totalSalary: { $sum: '$empSal' } } }])
[ { _id: null, totalSalary: 6434000 } ]
```
## Calculate the Average Salary of Employees

```js
Atlas atlas-aniack-shard-0 [primary] db> db.emp.aggregate([ { $group: {_id:null, Average_Salary: { $avg: '$empSal' } } }]).pretty()
[ { _id: null, Average_Salary: 321700 } ]
```
## Find the Maximum Salary in the Company
```js
Atlas atlas-aniack-shard-0 [primary] db> db.emp.aggregate([ { $group: {_id:null, Maximum_Salary: { $max: '$empSal' } } }]).pretty() 
[ { _id: null, Maximum_Salary: 5000000 } ]
Atlas atlas-aniack-shard-0 [primary] db>
```
## Count Employees by Department

```js
Atlas atlas-aniack-shard-0 [primary] db> db.emp.aggregate([ {$group:{_id:'$emp_deptID', DepartmentSum:{$sum:1}}}
... ])                                                                                                                                                             
[
  { _id: 107, DepartmentSum: 2 },
  { _id: 108, DepartmentSum: 1 },
  { _id: 109, DepartmentSum: 2 },
  { _id: 110, DepartmentSum: 1 },
  { _id: 105, DepartmentSum: 2 },
  { _id: 103, DepartmentSum: 3 },
  { _id: 1, DepartmentSum: 1 },
  { _id: 104, DepartmentSum: 3 },
  { _id: 102, DepartmentSum: 2 },
  { _id: 101, DepartmentSum: 2 },
  { _id: 106, DepartmentSum: 1 }
]
Atlas atlas-aniack-shard-0 [primary] db>
```
## Calculate the Average Salary by Department
```js
Atlas atlas-aniack-shard-0 [primary] db> db.emp.aggregate([{ $group: { _id: '$emp_deptID', DepartmentSum: { $avg: '$empSal' }}}]);
[
  { _id: 102, DepartmentSum: 83500 },
  { _id: 1, DepartmentSum: 5000000 },
  { _id: 104, DepartmentSum: 71333.33333333333 },
  { _id: 103, DepartmentSum: 80333.33333333333 },
  { _id: 105, DepartmentSum: 66000 },
  { _id: 109, DepartmentSum: 75000 },
  { _id: 108, DepartmentSum: 90000 },
  { _id: 110, DepartmentSum: 95000 },
  { _id: 106, DepartmentSum: 79000 },
  { _id: 107, DepartmentSum: 64000 },
  { _id: 101, DepartmentSum: 69000 }
]
Atlas atlas-aniack-shard-0 [primary] db>
```
## Total Salary Expenditure by Department
```js
Atlas atlas-aniack-shard-0 [primary] db> db.emp.aggregate([{ $group: { _id: '$emp_deptID', DepartmentSum: { $sum: '$empSal' }}}]);
[
  { _id: 101, DepartmentSum: 138000 },
  { _id: 103, DepartmentSum: 241000 },
  { _id: 105, DepartmentSum: 132000 },
  { _id: 102, DepartmentSum: 167000 },
  { _id: 106, DepartmentSum: 79000 },
  { _id: 107, DepartmentSum: 128000 },
  { _id: 109, DepartmentSum: 150000 },
  { _id: 108, DepartmentSum: 90000 },
  { _id: 110, DepartmentSum: 95000 },
  { _id: 1, DepartmentSum: 5000000 },
  { _id: 104, DepartmentSum: 214000 }
]
Atlas atlas-aniack-shard-0 [primary] db>
```
## Count Employees with Salary Greater Than 100000
```js
Atlas atlas-aniack-shard-0 [primary] db> db.emp.aggregate([{$match:{empSal:{$gt:100000}}},{ $group: { _id: null, RichEmployees: { $sum:'$empId'}}}]);
[ { _id: null, RichEmployees: 1 } ]
```
## Find the Department with the Highest Average Salary
```js
Atlas atlas-aniack-shard-0 [primary] db> db.emp.aggregate([ {$group:{_id:'$emp_deptID',averageSal:{$avg:'$empSal'}}}, {$sort: {averageSal : -1}}, {$limit:1}])
[ { _id: 1, averageSal: 5000000 } ]
Atlas atlas-aniack-shard-0 [primary] db>
```
## Top 3 Highest Paid Employees by Department
```js
Atlas atlas-aniack-shard-0 [primary] db> db.emp.aggregate([ {$group:{_id:'$emp_deptID', maxSal:{$max:'$empSal'}}},{ $sort:{maxSal:-1}},{$limit:3}]);
[
  { _id: 1, maxSal: 5000000 },
  { _id: 110, maxSal: 95000 },
  { _id: 103, maxSal: 93000 }
]
Atlas atlas-aniack-shard-0 [primary] db>
```