```
> use db
switched to db db
> db.createCollection("st");
{ "ok" : 1 }
> show dbs
31413_mock_db  0.000GB
Assignment_10  0.000GB
Assignment_9   0.000GB
admin          0.000GB
config         0.000GB
db             0.000GB
local          0.000GB
mock_db        0.000GB
mock_db_2      0.000GB
test           0.000GB
```

```json
> db.st.insert({studId:100, studName:"XYZ", studAge:16, studBranch:"COMP", studCity:"Pune", subjects:["Database","Computer Network"]});
WriteResult({ "nInserted" : 1 })
> db.st.insert({studId:101, studName:"ABC", studAge:17, studBranch:"COMP", studCity:"Pune", subjects:["DSA","Computer Network"]});
WriteResult({ "nInserted" : 1 })
> db.st.insert({ "studId": 102, "studName": "BCD", "studAge": 19, "studBranch": " ENTC", "studCity": "Delhi", "subjects": ["Microcontrollers", "Embedded Systems"] });
WriteResult({ "nInserted" : 1 })
db.st.insertMany([
    { "studId": 103, "studName": "PQR", "studAge": 19, "studBranch": "ENTC", "studCity": "Bangalore", "subjects": ["Microprocessor", "Computer Graphics"] },
  { "studId": 104, "studName": "LMN", "studAge": 17, "studBranch": "COMP", "studCity": "Chennai", "subjects": ["Algorithms", "Web Development"] },
  { "studId": 105, "studName": "EFG", "studAge": 18, "studBranch": "IT", "studCity": "Hyderabad", "subjects": ["Computer Networks", "Operating System"] },
  { "studId": 106, "studName": "HIJ", "studAge": 19, "studBranch": "ENTC", "studCity": "Delhi", "subjects": ["Digital Logic", "Computer Architecture"] },
  { "studId": 107, "studName": "KLM", "studAge": 17, "studBranch": "COMP", "studCity": "Pune", "subjects": ["Data Structures", "Database Management"] },
  { "studId": 108, "studName": "NOP", "studAge": 18, "studBranch": "IT", "studCity": "Mumbai", "subjects": ["Artificial Intelligence", "Machine Learning"] },
  { "studId": 109, "studName": "QRS", "studAge": 19, "studBranch": "ENTC", "studCity": "Bangalore", "subjects": ["Computer Vision", "Robotics"] },
  { "studId": 110, "studName": "TUV", "studAge": 17, "studBranch": "COMP", "studCity": "Chennai", "subjects": ["Web Development", "Cloud Computing"] },
  { "studId": 111, "studName": "WXY", "studAge": 18, "studBranch": "IT", "studCity": "Hyderabad", "subjects": ["Network Security", "Cryptography"] },
  { "studId": 112, "studName": "ZAB", "studAge": 19, "studBranch": "ENTC", "studCity": "Delhi", "subjects": ["Microcontrollers", "Embedded Systems"] },
  { "studId": 113, "studName": "CDE", "studAge": 17, "studBranch": "COMP", "studCity": "Pune", "subjects": ["Algorithms", "Data Mining"] },
  { "studId": 114, "studName": "FGH", "studAge": 18, "studBranch": "IT", "studCity": "Mumbai", "subjects": ["Operating System", "Computer Networks"] },
  { "studId": 115, "studName": "IJK", "studAge": 19, "studBranch": "ENTC", "studCity": "Bangalore", "subjects": ["Digital Signal Processing", "VLSI"] },
  { "studId": 116, "studName": "LMN", "studAge": 17, "studBranch": "COMP", "studCity": "Chennai", "subjects": ["Database Management", "Software Engineering"] },
  { "studId": 117, "studName": "OPQ", "studAge": 18, "studBranch": "IT", "studCity": "Hyderabad", "subjects": ["Artificial Intelligence", "Machine Learning"] },
  { "studId": 118, "studName": "RST", "studAge": 19, "studBranch": "ENTC", "studCity": "Delhi", "subjects": ["Computer Vision", "Robotics"] },
  { "studId": 119, "studName": "UVW", "studAge": 17, "studBranch": "COMP", "studCity": "Pune", "subjects": ["Web Development", "Cloud Computing"] },
  { "studId": 120, "studName": "XYZ", "studAge": 18, "studBranch": "IT", "studCity": "Mumbai", "subjects": ["Network Security", "Cryptography"] },
  { "studId": 121, "studName": "ABC", "studAge": 19, "studBranch": "ENTC", "studCity": "Bangalore", "subjects": ["Microcontrollers", "Embedded Systems"] },
  { "studId": 122, "studName": "DEF", "studAge": 17, "studBranch": "COMP", "studCity": "Chennai", "subjects": ["Algorithms", "Data Mining"] },
  { "studId": 123, "studName": "GHI", "studAge": 18, "studBranch": "IT", "studCity": "Hyderabad", "subjects": ["Operating System", "Computer Networks"] },
  { "studId": 124, "studName": "JKL", "studAge": 19, "studBranch": "ENTC", "studCity": "Delhi", "subjects": ["Digital Signal Processing", "VLSI"] },
  { "studId": 125, "studName": "MNO", "studAge": 17, "studBranch": "COMP", "studCity": "Pune", "subjects": ["Database Management", "Software Engineering"] },
  { "studId": 126, "studName": "PQR", "studAge": 18, "studBranch": "IT", "studCity": "Mumbai", "subjects": ["Artificial Intelligence", "Machine Learning"] },
  { "studId": 127, "studName": "STU", "studAge": 19, "studBranch": "ENTC", "studCity": "Bangalore", "subjects": ["Computer Vision", "Robotics"] },
  { "studId": 128, "studName": "VWX", "studAge": 17, "studBranch": "COMP", "studCity": "Chennai", "subjects": ["Web Development", "Cloud Computing"] },
  { "studId": 129, "studName": "YZA", "studAge": 18, "studBranch": "IT", "studCity": "Hyderabad", "subjects": ["Network Security", "Cryptography"] },
  { "studId": 130, "studName": "XYZ", "studAge": 18, "studBranch": "IT", "studCity": "Mumbai", "subjects": ["OS", "DBMS"] }
]);
{
	"acknowledged" : true,
	"insertedIds" : [
		ObjectId("66ee90871c1ae1dea2db1dfb"),
		ObjectId("66ee90871c1ae1dea2db1dfc"),
		ObjectId("66ee90871c1ae1dea2db1dfd"),
		ObjectId("66ee90871c1ae1dea2db1dfe"),
		ObjectId("66ee90871c1ae1dea2db1dff"),
		ObjectId("66ee90871c1ae1dea2db1e00"),
		ObjectId("66ee90871c1ae1dea2db1e01"),
		ObjectId("66ee90871c1ae1dea2db1e02"),
		ObjectId("66ee90871c1ae1dea2db1e03"),
		ObjectId("66ee90871c1ae1dea2db1e04"),
		ObjectId("66ee90871c1ae1dea2db1e05"),
		ObjectId("66ee90871c1ae1dea2db1e06"),
		ObjectId("66ee90871c1ae1dea2db1e07"),
		ObjectId("66ee90871c1ae1dea2db1e08"),
		ObjectId("66ee90871c1ae1dea2db1e09"),
		ObjectId("66ee90871c1ae1dea2db1e0a"),
		ObjectId("66ee90871c1ae1dea2db1e0b"),
		ObjectId("66ee90871c1ae1dea2db1e0c"),
		ObjectId("66ee90871c1ae1dea2db1e0d"),
		ObjectId("66ee90871c1ae1dea2db1e0e"),
		ObjectId("66ee90871c1ae1dea2db1e0f"),
		ObjectId("66ee90871c1ae1dea2db1e10"),
		ObjectId("66ee90871c1ae1dea2db1e11"),
		ObjectId("66ee90871c1ae1dea2db1e12"),
		ObjectId("66ee90871c1ae1dea2db1e13"),
		ObjectId("66ee90871c1ae1dea2db1e14"),
		ObjectId("66ee90871c1ae1dea2db1e15"),
		ObjectId("66ee90871c1ae1dea2db1e16")
	]
}
> db.st.insertMany([
      { "studId": 121, "studName": "ABC", "studAge": 22, "studBranch": "CSE", "studCity": "Mumbai", "subjects": ["Data Structures", "Algorithms"] },
      { "studId": 122, "studName": "DEF", "studAge": 23, "studBranch": "IT", "studCity": "Chennai", "subjects": ["Computer Networks", "Cyber Security"] },
      { "studId": 123, "studName": "GHI", "studAge": 24, "studBranch": "ECE", "studCity": "Hyderabad", "subjects": ["Microcontrollers", "Embedded Systems"] },
      { "studId": 124, "studName": "JKL", "studAge": 25, "studBranch": "MECH", "studCity": "Pune", "subjects": ["Thermodynamics", "Mechanics of Solids"] },
      { "studId": 125, "studName": "MNO", "studAge": 26, "studBranch": "CIVIL", "studCity": "Kolkata", "subjects": ["Structural Analysis", "Building Materials"] }
    ]);
{
	"acknowledged" : true,
	"insertedIds" : [
		ObjectId("66ee962b1c1ae1dea2db1e18"),
		ObjectId("66ee962b1c1ae1dea2db1e19"),
		ObjectId("66ee962b1c1ae1dea2db1e1a"),
		ObjectId("66ee962b1c1ae1dea2db1e1b"),
		ObjectId("66ee962b1c1ae1dea2db1e1c")
	]
}

```
## Display only studName and studBranch
```json
> db.st.find({},{_id:false, studName:true, studBranch:true});
{ "studName" : "XYZ", "studBranch" : "COMP" }
{ "studName" : "ABC", "studBranch" : "COMP" }
{ "studName" : "PQR", "studBranch" : "ENTC" }
{ "studName" : "PQR", "studBranch" : "ENTC" }
{ "studName" : "LMN", "studBranch" : "COMP" }
{ "studName" : "EFG", "studBranch" : "IT" }
{ "studName" : "HIJ", "studBranch" : "ENTC" }
{ "studName" : "KLM", "studBranch" : "COMP" }
{ "studName" : "NOP", "studBranch" : "IT" }
{ "studName" : "QRS", "studBranch" : "ENTC" }
{ "studName" : "TUV", "studBranch" : "COMP" }
{ "studName" : "WXY", "studBranch" : "IT" }
{ "studName" : "ZAB", "studBranch" : "ENTC" }
{ "studName" : "CDE", "studBranch" : "COMP" }
{ "studName" : "FGH", "studBranch" : "IT" }
{ "studName" : "IJK", "studBranch" : "ENTC" }
{ "studName" : "LMN", "studBranch" : "COMP" }
{ "studName" : "OPQ", "studBranch" : "IT" }
{ "studName" : "RST", "studBranch" : "ENTC" }
{ "studName" : "UVW", "studBranch" : "COMP" }
Type "it" for more
> it
{ "studName" : "XYZ", "studBranch" : "IT" }
{ "studName" : "ABC", "studBranch" : "ENTC" }
{ "studName" : "DEF", "studBranch" : "COMP" }
{ "studName" : "GHI", "studBranch" : "IT" }
{ "studName" : "JKL", "studBranch" : "ENTC" }
{ "studName" : "MNO", "studBranch" : "COMP" }
{ "studName" : "PQR", "studBranch" : "IT" }
{ "studName" : "STU", "studBranch" : "ENTC" }
{ "studName" : "VWX", "studBranch" : "COMP" }
{ "studName" : "YZA", "studBranch" : "IT" }
{ "studName" : "XYZ", "studBranch" : "IT" }
```

## Display info of student 102

```json
> db.st.find({studId:102}).pretty();
{
	"_id" : ObjectId("66ee924c1c1ae1dea2db1e17"),
	"studId" : 102,
	"studName" : "BCD",
	"studAge" : 19,
	"studBranch" : " ENTC",
	"studCity" : "Delhi",
	"subjects" : [
		"Microcontrollers",
		"Embedded Systems"
	]
}
```

## Display id, name in decreasing order of age.

```json
> db.st.find({},{_id:0, studId:1, studName:1}).sort({age:1});
{ "studId" : 100, "studName" : "XYZ" }
{ "studId" : 101, "studName" : "ABC" }
{ "studId" : 103, "studName" : "PQR" }
{ "studId" : 103, "studName" : "PQR" }
{ "studId" : 104, "studName" : "LMN" }
{ "studId" : 105, "studName" : "EFG" }
{ "studId" : 106, "studName" : "HIJ" }
{ "studId" : 107, "studName" : "KLM" }
{ "studId" : 108, "studName" : "NOP" }
{ "studId" : 109, "studName" : "QRS" }
{ "studId" : 110, "studName" : "TUV" }
{ "studId" : 111, "studName" : "WXY" }
{ "studId" : 112, "studName" : "ZAB" }
{ "studId" : 113, "studName" : "CDE" }
{ "studId" : 114, "studName" : "FGH" }
{ "studId" : 115, "studName" : "IJK" }
{ "studId" : 116, "studName" : "LMN" }
{ "studId" : 117, "studName" : "OPQ" }
{ "studId" : 118, "studName" : "RST" }
{ "studId" : 119, "studName" : "UVW" }
Type "it" for more
> it
{ "studId" : 120, "studName" : "XYZ" }
{ "studId" : 121, "studName" : "ABC" }
{ "studId" : 122, "studName" : "DEF" }
{ "studId" : 123, "studName" : "GHI" }
{ "studId" : 124, "studName" : "JKL" }
{ "studId" : 125, "studName" : "MNO" }
{ "studId" : 126, "studName" : "PQR" }
{ "studId" : 127, "studName" : "STU" }
{ "studId" : 128, "studName" : "VWX" }
{ "studId" : 129, "studName" : "YZA" }
{ "studId" : 130, "studName" : "XYZ" }
{ "studId" : 102, "studName" : "BCD" }

```

## Display studName and studBranch having age greater than 25

```json
> db.st.find({studAge: {$gt:25}}, {_id:0, studName:1, studBranch:1}).pretty();
{ "studName" : "MNO", "studBranch" : "CIVIL" }

```

## Display first 3 documents in ascending order of age

```json
> db.st.find().sort({studAge:1}).limit(3).pretty();
{
	"_id" : ObjectId("66ee8b501c1ae1dea2db1df8"),
	"studId" : 100,
	"studName" : "XYZ",
	"studAge" : 16,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Database",
		"Computer Network"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dfc"),
	"studId" : 104,
	"studName" : "LMN",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Algorithms",
		"Web Development"
	]
}
{
	"_id" : ObjectId("66ee8c471c1ae1dea2db1df9"),
	"studId" : 101,
	"studName" : "ABC",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"DSA",
		"Computer Network"
	]
}
```

## Display information of student with id 101 and branch computer

```json
> db.st.find({$and:[{studId:101},{studBranch:"COMP"}]}).pretty();
{
	"_id" : ObjectId("66ee8c471c1ae1dea2db1df9"),
	"studId" : 101,
	"studName" : "ABC",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"DSA",
		"Computer Network"
	]
}
```

## Display information of student with branch COMPUTER and age less than 22

```json
> db.st.find({$and:[{studBranch:"COMP"}, {studAge: {$lt:22}}]}).pretty();
{
	"_id" : ObjectId("66ee8b501c1ae1dea2db1df8"),
	"studId" : 100,
	"studName" : "XYZ",
	"studAge" : 16,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Database",
		"Computer Network"
	]
}
{
	"_id" : ObjectId("66ee8c471c1ae1dea2db1df9"),
	"studId" : 101,
	"studName" : "ABC",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"DSA",
		"Computer Network"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dfc"),
	"studId" : 104,
	"studName" : "LMN",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Algorithms",
		"Web Development"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dff"),
	"studId" : 107,
	"studName" : "KLM",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Data Structures",
		"Database Management"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e02"),
	"studId" : 110,
	"studName" : "TUV",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Web Development",
		"Cloud Computing"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e05"),
	"studId" : 113,
	"studName" : "CDE",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Algorithms",
		"Data Mining"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e08"),
	"studId" : 116,
	"studName" : "LMN",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Database Management",
		"Software Engineering"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0b"),
	"studId" : 119,
	"studName" : "UVW",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Web Development",
		"Cloud Computing"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0e"),
	"studId" : 122,
	"studName" : "DEF",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Algorithms",
		"Data Mining"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e11"),
	"studId" : 125,
	"studName" : "MNO",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Database Management",
		"Software Engineering"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e14"),
	"studId" : 128,
	"studName" : "VWX",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Web Development",
		"Cloud Computing"
	]
}

```

## Display information of student whose branch is not civil and whose city is not mumbai

```json
db.st.find({$and:[{studBranch:{$ne:"CIVIL"}},{studCity: {$ne: "Mumbai"}}]}).pretty();

> db.st.find({$and:[{studBranch:{$ne:"CIVIL"}},{studCity: {$ne: "Mumbai"}}]}).pretty();
{
	"_id" : ObjectId("66ee8b501c1ae1dea2db1df8"),
	"studId" : 100,
	"studName" : "XYZ",
	"studAge" : 16,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Database",
		"Computer Network"
	]
}
{
	"_id" : ObjectId("66ee8c471c1ae1dea2db1df9"),
	"studId" : 101,
	"studName" : "ABC",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"DSA",
		"Computer Network"
	]
}
{
	"_id" : ObjectId("66ee905b1c1ae1dea2db1dfa"),
	"studId" : 103,
	"studName" : "PQR",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Bangalore",
	"subjects" : [
		"Microprocessor",
		"Computer Graphics"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dfb"),
	"studId" : 103,
	"studName" : "PQR",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Bangalore",
	"subjects" : [
		"Microprocessor",
		"Computer Graphics"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dfc"),
	"studId" : 104,
	"studName" : "LMN",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Algorithms",
		"Web Development"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dfd"),
	"studId" : 105,
	"studName" : "EFG",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Computer Networks",
		"Operating System"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dfe"),
	"studId" : 106,
	"studName" : "HIJ",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Delhi",
	"subjects" : [
		"Digital Logic",
		"Computer Architecture"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dff"),
	"studId" : 107,
	"studName" : "KLM",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Data Structures",
		"Database Management"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e01"),
	"studId" : 109,
	"studName" : "QRS",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Bangalore",
	"subjects" : [
		"Computer Vision",
		"Robotics"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e02"),
	"studId" : 110,
	"studName" : "TUV",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Web Development",
		"Cloud Computing"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e03"),
	"studId" : 111,
	"studName" : "WXY",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Network Security",
		"Cryptography"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e04"),
	"studId" : 112,
	"studName" : "ZAB",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Delhi",
	"subjects" : [
		"Microcontrollers",
		"Embedded Systems"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e05"),
	"studId" : 113,
	"studName" : "CDE",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Algorithms",
		"Data Mining"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e07"),
	"studId" : 115,
	"studName" : "IJK",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Bangalore",
	"subjects" : [
		"Digital Signal Processing",
		"VLSI"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e08"),
	"studId" : 116,
	"studName" : "LMN",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Database Management",
		"Software Engineering"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e09"),
	"studId" : 117,
	"studName" : "OPQ",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Artificial Intelligence",
		"Machine Learning"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0a"),
	"studId" : 118,
	"studName" : "RST",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Delhi",
	"subjects" : [
		"Computer Vision",
		"Robotics"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0b"),
	"studId" : 119,
	"studName" : "UVW",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Web Development",
		"Cloud Computing"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0d"),
	"studId" : 121,
	"studName" : "ABC",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Bangalore",
	"subjects" : [
		"Microcontrollers",
		"Embedded Systems"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0e"),
	"studId" : 122,
	"studName" : "DEF",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Algorithms",
		"Data Mining"
	]
}
Type "it" for more
> it
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0f"),
	"studId" : 123,
	"studName" : "GHI",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Operating System",
		"Computer Networks"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e10"),
	"studId" : 124,
	"studName" : "JKL",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Delhi",
	"subjects" : [
		"Digital Signal Processing",
		"VLSI"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e11"),
	"studId" : 125,
	"studName" : "MNO",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Database Management",
		"Software Engineering"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e13"),
	"studId" : 127,
	"studName" : "STU",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Bangalore",
	"subjects" : [
		"Computer Vision",
		"Robotics"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e14"),
	"studId" : 128,
	"studName" : "VWX",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Web Development",
		"Cloud Computing"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e15"),
	"studId" : 129,
	"studName" : "YZA",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Network Security",
		"Cryptography"
	]
}
{
	"_id" : ObjectId("66ee924c1c1ae1dea2db1e17"),
	"studId" : 102,
	"studName" : "BCD",
	"studAge" : 19,
	"studBranch" : " ENTC",
	"studCity" : "Delhi",
	"subjects" : [
		"Microcontrollers",
		"Embedded Systems"
	]
}
{
	"_id" : ObjectId("66ee962b1c1ae1dea2db1e19"),
	"studId" : 122,
	"studName" : "DEF",
	"studAge" : 23,
	"studBranch" : "IT",
	"studCity" : "Chennai",
	"subjects" : [
		"Computer Networks",
		"Cyber Security"
	]
}
{
	"_id" : ObjectId("66ee962b1c1ae1dea2db1e1a"),
	"studId" : 123,
	"studName" : "GHI",
	"studAge" : 24,
	"studBranch" : "ECE",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Microcontrollers",
		"Embedded Systems"
	]
}
{
	"_id" : ObjectId("66ee962b1c1ae1dea2db1e1b"),
	"studId" : 124,
	"studName" : "JKL",
	"studAge" : 25,
	"studBranch" : "MECH",
	"studCity" : "Pune",
	"subjects" : [
		"Thermodynamics",
		"Mechanics of Solids"
	]
}
> 
```

## Display information of students whose age is not greater than 22

```json
> db.st.find({studAge:{$lte: 22}}).pretty();
{
	"_id" : ObjectId("66ee8b501c1ae1dea2db1df8"),
	"studId" : 100,
	"studName" : "XYZ",
	"studAge" : 16,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Database",
		"Computer Network"
	]
}
{
	"_id" : ObjectId("66ee8c471c1ae1dea2db1df9"),
	"studId" : 101,
	"studName" : "ABC",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"DSA",
		"Computer Network"
	]
}
{
	"_id" : ObjectId("66ee905b1c1ae1dea2db1dfa"),
	"studId" : 103,
	"studName" : "PQR",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Bangalore",
	"subjects" : [
		"Microprocessor",
		"Computer Graphics"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dfb"),
	"studId" : 103,
	"studName" : "PQR",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Bangalore",
	"subjects" : [
		"Microprocessor",
		"Computer Graphics"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dfc"),
	"studId" : 104,
	"studName" : "LMN",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Algorithms",
		"Web Development"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dfd"),
	"studId" : 105,
	"studName" : "EFG",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Computer Networks",
		"Operating System"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dfe"),
	"studId" : 106,
	"studName" : "HIJ",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Delhi",
	"subjects" : [
		"Digital Logic",
		"Computer Architecture"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dff"),
	"studId" : 107,
	"studName" : "KLM",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Data Structures",
		"Database Management"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e00"),
	"studId" : 108,
	"studName" : "NOP",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Mumbai",
	"subjects" : [
		"Artificial Intelligence",
		"Machine Learning"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e01"),
	"studId" : 109,
	"studName" : "QRS",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Bangalore",
	"subjects" : [
		"Computer Vision",
		"Robotics"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e02"),
	"studId" : 110,
	"studName" : "TUV",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Web Development",
		"Cloud Computing"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e03"),
	"studId" : 111,
	"studName" : "WXY",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Network Security",
		"Cryptography"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e04"),
	"studId" : 112,
	"studName" : "ZAB",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Delhi",
	"subjects" : [
		"Microcontrollers",
		"Embedded Systems"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e05"),
	"studId" : 113,
	"studName" : "CDE",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Algorithms",
		"Data Mining"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e06"),
	"studId" : 114,
	"studName" : "FGH",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Mumbai",
	"subjects" : [
		"Operating System",
		"Computer Networks"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e07"),
	"studId" : 115,
	"studName" : "IJK",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Bangalore",
	"subjects" : [
		"Digital Signal Processing",
		"VLSI"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e08"),
	"studId" : 116,
	"studName" : "LMN",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Database Management",
		"Software Engineering"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e09"),
	"studId" : 117,
	"studName" : "OPQ",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Artificial Intelligence",
		"Machine Learning"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0a"),
	"studId" : 118,
	"studName" : "RST",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Delhi",
	"subjects" : [
		"Computer Vision",
		"Robotics"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0b"),
	"studId" : 119,
	"studName" : "UVW",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Web Development",
		"Cloud Computing"
	]
}
Type "it" for more
> it
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0c"),
	"studId" : 120,
	"studName" : "XYZ",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Mumbai",
	"subjects" : [
		"Network Security",
		"Cryptography"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0d"),
	"studId" : 121,
	"studName" : "ABC",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Bangalore",
	"subjects" : [
		"Microcontrollers",
		"Embedded Systems"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0e"),
	"studId" : 122,
	"studName" : "DEF",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Algorithms",
		"Data Mining"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0f"),
	"studId" : 123,
	"studName" : "GHI",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Operating System",
		"Computer Networks"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e10"),
	"studId" : 124,
	"studName" : "JKL",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Delhi",
	"subjects" : [
		"Digital Signal Processing",
		"VLSI"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e11"),
	"studId" : 125,
	"studName" : "MNO",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Database Management",
		"Software Engineering"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e12"),
	"studId" : 126,
	"studName" : "PQR",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Mumbai",
	"subjects" : [
		"Artificial Intelligence",
		"Machine Learning"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e13"),
	"studId" : 127,
	"studName" : "STU",
	"studAge" : 19,
	"studBranch" : "ENTC",
	"studCity" : "Bangalore",
	"subjects" : [
		"Computer Vision",
		"Robotics"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e14"),
	"studId" : 128,
	"studName" : "VWX",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Web Development",
		"Cloud Computing"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e15"),
	"studId" : 129,
	"studName" : "YZA",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Network Security",
		"Cryptography"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e16"),
	"studId" : 130,
	"studName" : "XYZ",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Mumbai",
	"subjects" : [
		"OS",
		"DBMS"
	]
}
{
	"_id" : ObjectId("66ee924c1c1ae1dea2db1e17"),
	"studId" : 102,
	"studName" : "BCD",
	"studAge" : 19,
	"studBranch" : " ENTC",
	"studCity" : "Delhi",
	"subjects" : [
		"Microcontrollers",
		"Embedded Systems"
	]
}
{
	"_id" : ObjectId("66ee962b1c1ae1dea2db1e18"),
	"studId" : 121,
	"studName" : "ABC",
	"studAge" : 22,
	"studBranch" : "CSE",
	"studCity" : "Mumbai",
	"subjects" : [
		"Data Structures",
		"Algorithms"
	]
}
> 
```

## Display ionformation of students whose DEPT is `COMP` or `CIVIL` or `IT`

```json
> db.st.find({$or:[{studBranch:"COMP"},{studBranch:"CIVIL"},{studBranch:"IT"}]}).pretty()
{
	"_id" : ObjectId("66ee8b501c1ae1dea2db1df8"),
	"studId" : 100,
	"studName" : "XYZ",
	"studAge" : 16,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Database",
		"Computer Network"
	]
}
{
	"_id" : ObjectId("66ee8c471c1ae1dea2db1df9"),
	"studId" : 101,
	"studName" : "ABC",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"DSA",
		"Computer Network"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dfc"),
	"studId" : 104,
	"studName" : "LMN",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Algorithms",
		"Web Development"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dfd"),
	"studId" : 105,
	"studName" : "EFG",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Computer Networks",
		"Operating System"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dff"),
	"studId" : 107,
	"studName" : "KLM",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Data Structures",
		"Database Management"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e00"),
	"studId" : 108,
	"studName" : "NOP",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Mumbai",
	"subjects" : [
		"Artificial Intelligence",
		"Machine Learning"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e02"),
	"studId" : 110,
	"studName" : "TUV",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Web Development",
		"Cloud Computing"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e03"),
	"studId" : 111,
	"studName" : "WXY",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Network Security",
		"Cryptography"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e05"),
	"studId" : 113,
	"studName" : "CDE",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Algorithms",
		"Data Mining"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e06"),
	"studId" : 114,
	"studName" : "FGH",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Mumbai",
	"subjects" : [
		"Operating System",
		"Computer Networks"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e08"),
	"studId" : 116,
	"studName" : "LMN",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Database Management",
		"Software Engineering"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e09"),
	"studId" : 117,
	"studName" : "OPQ",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Artificial Intelligence",
		"Machine Learning"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0b"),
	"studId" : 119,
	"studName" : "UVW",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Web Development",
		"Cloud Computing"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0c"),
	"studId" : 120,
	"studName" : "XYZ",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Mumbai",
	"subjects" : [
		"Network Security",
		"Cryptography"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0e"),
	"studId" : 122,
	"studName" : "DEF",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Algorithms",
		"Data Mining"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e0f"),
	"studId" : 123,
	"studName" : "GHI",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Operating System",
		"Computer Networks"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e11"),
	"studId" : 125,
	"studName" : "MNO",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Database Management",
		"Software Engineering"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e12"),
	"studId" : 126,
	"studName" : "PQR",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Mumbai",
	"subjects" : [
		"Artificial Intelligence",
		"Machine Learning"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e14"),
	"studId" : 128,
	"studName" : "VWX",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Web Development",
		"Cloud Computing"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e15"),
	"studId" : 129,
	"studName" : "YZA",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Hyderabad",
	"subjects" : [
		"Network Security",
		"Cryptography"
	]
}
Type "it" for more
> it
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e16"),
	"studId" : 130,
	"studName" : "XYZ",
	"studAge" : 18,
	"studBranch" : "IT",
	"studCity" : "Mumbai",
	"subjects" : [
		"OS",
		"DBMS"
	]
}
{
	"_id" : ObjectId("66ee962b1c1ae1dea2db1e19"),
	"studId" : 122,
	"studName" : "DEF",
	"studAge" : 23,
	"studBranch" : "IT",
	"studCity" : "Chennai",
	"subjects" : [
		"Computer Networks",
		"Cyber Security"
	]
}
{
	"_id" : ObjectId("66ee962b1c1ae1dea2db1e1c"),
	"studId" : 125,
	"studName" : "MNO",
	"studAge" : 26,
	"studBranch" : "CIVIL",
	"studCity" : "Kolkata",
	"subjects" : [
		"Structural Analysis",
		"Building Materials"
	]
}
> 
```
## Find the information of students interested in database management

```json
> db.st.find({subjects:{$in : ["Database Management"]}}).pretty();
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1dff"),
	"studId" : 107,
	"studName" : "KLM",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Data Structures",
		"Database Management"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e08"),
	"studId" : 116,
	"studName" : "LMN",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Chennai",
	"subjects" : [
		"Database Management",
		"Software Engineering"
	]
}
{
	"_id" : ObjectId("66ee90871c1ae1dea2db1e11"),
	"studId" : 125,
	"studName" : "MNO",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Database Management",
		"Software Engineering"
	]
}
```

## Display information of student who is having subject Computer Network in 2nd position

```json
> db.st.find({"subjects.1": "Computer Network"}).pretty();
{
	"_id" : ObjectId("66ee8b501c1ae1dea2db1df8"),
	"studId" : 100,
	"studName" : "XYZ",
	"studAge" : 16,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"Database",
		"Computer Network"
	]
}
{
	"_id" : ObjectId("66ee8c471c1ae1dea2db1df9"),
	"studId" : 101,
	"studName" : "ABC",
	"studAge" : 17,
	"studBranch" : "COMP",
	"studCity" : "Pune",
	"subjects" : [
		"DSA",
		"Computer Network"
	]
}
```

## Count number of documents

```json
> db.st.find().count();
37
> 
```

## Count of documents whose branch is `Computer Engineering`

```json
> db.st.find({studBranch:"COMP"}).count();
11
> 
```

## Update studBranch to `Mechanical Engineering`

```json
> db.st.update({studId:102},{$set:{studBranch:"Mechanical Engineering"}});
WriteResult({ "nMatched" : 1, "nUpserted" : 0, "nModified" : 1 })
> db.st.find({studId:102}).pretty();
{
        "_id" : ObjectId("66ee924c1c1ae1dea2db1e17"),
        "studId" : 102,
        "studName" : "BCD",
        "studAge" : 19,
        "studBranch" : "Mechanical Engineering",
        "studCity" : "Delhi",
        "subjects" : [
                "Microcontrollers",
                "Embedded Systems"
        ]
}
> 
```
## Update `CIVIL` to `CIVIL ENGINEERING` of all documents

```json
> db.st.updateMany({studBranch: "CIVIL"},{$set:{studBranch:"Civil Engineering"}});
{ "acknowledged" : true, "matchedCount" : 1, "modifiedCount" : 1 }
> db.st.find({studBranch:"Civil Engineering"}).pretty();
{
        "_id" : ObjectId("66ee962b1c1ae1dea2db1e1c"),
        "studId" : 125,
        "studName" : "MNO",
        "studAge" : 26,
        "studBranch" : "Civil Engineering",
        "studCity" : "Kolkata",
        "subjects" : [
                "Structural Analysis",
                "Building Materials"
        ]
}
> 
```

## Update studName and studAge of id 104

```json
> db.st.update({studId:104}, {$set:{studName:"Suresh",studAge:26}});
WriteResult({ "nMatched" : 1, "nUpserted" : 0, "nModified" : 1 })
> db.st.find({studId:104}).pretty();
{
        "_id" : ObjectId("66ee90871c1ae1dea2db1dfc"),
        "studId" : 104,
        "studName" : "Suresh",
        "studAge" : 26,
        "studBranch" : "COMP",
        "studCity" : "Chennai",
        "subjects" : [
                "Algorithms",
                "Web Development"
        ]
}
> 
```

## Rename field Subject to studSub of all documents

```json
> db.st.updateMany({},{$rename:{"subjects":"studSub"}});
{ "acknowledged" : true, "matchedCount" : 37, "modifiedCount" : 37 }
> 
```

## Increment the value of age by 3 for XYZ

```json
> db.st.update({studName:"XYZ"},{inc:{studAge:3}});
WriteResult({ "nMatched" : 1, "nUpserted" : 0, "nModified" : 1 })
> db.st.find({studName:"XYZ"}).pretty();
{
        "_id" : ObjectId("66ee90871c1ae1dea2db1e0c"),
        "studId" : 120,
        "studName" : "XYZ",
        "studAge" : 18,
        "studBranch" : "IT",
        "studCity" : "Mumbai",
        "studSub" : [
                "Network Security",
                "Cryptography"
        ]
}
{
        "_id" : ObjectId("66ee90871c1ae1dea2db1e16"),
        "studId" : 130,
        "studName" : "XYZ",
        "studAge" : 18,
        "studBranch" : "IT",
        "studCity" : "Mumbai",
        "studSub" : [
                "OS",
                "DBMS"
        ]
}
> 
```

## Remove studAge field of 101

```json
> db.st.update({studId:101},{$unset:{"studAge":""}});
WriteResult({ "nMatched" : 1, "nUpserted" : 0, "nModified" : 1 })
> db.st.find({studId:101}).pretty();
{
        "_id" : ObjectId("66f1377ccddfd4482a8fbc3c"),
        "studId" : 101,
        "studName" : "ABC",
        "studBranch" : "COMP",
        "studCity" : "Pune",
        "subjects" : [
                "DSA",
                "Computer Network"
        ]
}
```

## Add a new field to all documents as `studContact: {personal:1234, parents:2345}`

```json
> db.st.updateMany({},{$set:{studContact:{personal:1234,parents:2345}}});
{ "acknowledged" : true, "matchedCount" : 39, "modifiedCount" : 39 }
> db.st.find().limit(2).pretty();
{
        "_id" : ObjectId("66ee8b501c1ae1dea2db1df8"),
        "inc" : {
                "studAge" : 3
        },
        "studContact" : {
                "personal" : 1234,
                "parents" : 2345
        }
}
{
        "_id" : ObjectId("66ee905b1c1ae1dea2db1dfa"),
        "studId" : 103,
        "studName" : "PQR",
        "studAge" : 19,
        "studBranch" : "ENTC",
        "studCity" : "Bangalore",
        "studSub" : [
                "Microprocessor",
                "Computer Graphics"
        ],
        "studContact" : {
                "personal" : 1234,
                "parents" : 2345
        }
}
> 
```

## Remove all information of studId 103

```json
> db.st.deleteOne({studId:103});
{ "acknowledged" : true, "deletedCount" : 1 }
```


## Remove All documents

```json
> db.st.deleteMany({});
{ "acknowledged" : true, "deletedCount" : 38 }
> 
```

## Drop Collection

```json
> db.st.drop();
true
> 
```

Drop Database

```json
> db.dropDatabase();
{ "dropped" : "db", "ok" : 1 }
> 
```

Compute Estimators of the main statistical measures like Mean, Variance, Standard
Deviation, Covariance, Correlation and Standard error with respect to any example.
Display graphically the distribution of samples.

Plot the Normal Distribution for class test result of a particular subject. Identify the
Skewness and Kurtosis

Load the dataset: birthwt Risk Factors Associated with Low Infant Birth Weight at
https://raw.github.com/neurospin/pystatsml/master/datasets/birthwt.csv
1. Test the association of mother’s (bwt) age and birth weight using the correlation
test and linear regeression.
2. Test the association of mother’s weight (lwt) and birth weight using the
correlation testand linear regeression.
3. Produce two scatter plot of: (i) age by birth weight; (ii) mother’s weight by birth
weight. Elaborate the Conclusion

Apply Basic PCA on the iris dataset. The data set is available at:
https://raw.github.com/neurospin/pystatsml/master/datasets/iris.csv
• Describe the data set. Should the dataset been standardized?
• Describe the structure of correlations among variables.
• Compute a PCA with the maximum number of components
.• Compute the cumulative explained variance ratio. Determine the number of
components𝐾by your computed values.
• Print the𝐾principal components directions and correlations of the𝐾principal
compo-nents with the original variables. Interpret the contribution of the original
variables into the PC.
• Plot the samples projected into the𝐾first PCs.
• Color samples by their species.