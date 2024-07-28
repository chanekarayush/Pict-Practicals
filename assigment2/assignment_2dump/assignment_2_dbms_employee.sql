-- MySQL dump 10.13  Distrib 8.0.34, for Win64 (x86_64)
--
-- Host: localhost    Database: assignment_2_dbms
-- ------------------------------------------------------
-- Server version	8.0.34

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `employee`
--

DROP TABLE IF EXISTS `employee`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `employee` (
  `Emp_id` int NOT NULL,
  `Dept_id` int DEFAULT NULL,
  `Emp_fname` varchar(50) DEFAULT NULL,
  `Emp_lname` varchar(50) DEFAULT NULL,
  `Emp_position` varchar(100) DEFAULT NULL,
  `Emp_salary` double(10,2) DEFAULT NULL,
  `Emp_joinDate` date DEFAULT NULL,
  PRIMARY KEY (`Emp_id`),
  KEY `Dept_id` (`Dept_id`),
  CONSTRAINT `employee_ibfk_1` FOREIGN KEY (`Dept_id`) REFERENCES `dept` (`Dept_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employee`
--

LOCK TABLES `employee` WRITE;
/*!40000 ALTER TABLE `employee` DISABLE KEYS */;
INSERT INTO `employee` VALUES (1,1,'Pankaj','Patel','Manager',55000.00,'1980-01-15'),(2,2,'Ravi','Reddy','Analyst',66000.00,'1981-03-21'),(3,3,'Suresh','Sharma','Developer',77000.00,'1982-05-30'),(4,4,'Harish','Hegde','Researcher',88000.00,'1983-07-12'),(5,5,'Pranav','Pawar','Marketing Executive',82500.00,'1984-09-24'),(6,6,'Rajesh','Rao','Sales Executive',65000.00,'1985-11-05'),(7,7,'Sanjay','Singh','Legal Advisor',85000.00,'1986-01-18'),(8,8,'Hemant','Hooda','Operations Manager',95000.00,'2018-04-27'),(9,9,'Prakash','Patil','Administrator',55000.00,'2014-05-11'),(10,10,'Rahul','Roy','Support Engineer',45000.00,'1992-10-28'),(11,11,'Puneet','Pandey','Logistics Manager',40000.00,'2014-01-16'),(12,12,'Ramesh','Ram','Customer Service Rep',47000.00,'1989-09-29'),(13,13,'Siddharth','Soni','Product Developer',90000.00,'1999-08-04'),(14,14,'Himanshu','Hiran','QA Specialist',82000.00,'2004-09-21'),(15,15,'Parth','Pandya','Purchasing Officer',75000.00,'2000-11-02'),(16,16,'Rohit','Rathore','Engineer',92000.00,'2005-01-10'),(17,17,'Suraj','Shukla','PR Manager',72000.00,'1998-08-16'),(18,18,'Hrithik','Harsha','Business Analyst',68000.00,'1993-01-14'),(19,19,'Palash','Pathak','Trainer',78000.00,'2023-04-24'),(20,20,'Ritik','Raj','Procurement Specialist',87000.00,'1996-06-11'),(21,21,'Sahil','Saxena','Legal Assistant',51000.00,'2005-04-16'),(22,22,'Harshal','Handa','Corporate Strategist',96000.00,'2013-02-11'),(23,23,'Piyush','Pradhan','Compliance Officer',64000.00,'1986-09-16'),(24,24,'Rohan','Roy','Risk Manager',91000.00,'1987-03-12'),(25,25,'Satish','Sarkar','Govt. Relations',68000.00,'1990-11-01'),(26,26,'Hiren','Hegde','Facilities Manager',73000.00,'2007-08-06'),(27,27,'Pratik','Purohit','Investor Relations',84000.00,'2002-06-23'),(28,28,'Rahul','Reddy','Communications Officer',49000.00,'2004-08-02'),(29,29,'Sanket','Sinha','HR Executive',58000.00,'1991-07-07'),(30,30,'Hemang','Hegde','Finance Analyst',78000.00,'1997-10-18'),(31,31,'Praveen','Pillai','Tech Support',56000.00,'1990-06-11'),(32,32,'Rakesh','Rathore','Manufacturing Lead',81000.00,'2012-10-26'),(33,33,'Sagar','Sharma','Supply Chain Manager',87000.00,'1990-10-09'),(34,34,'Hitesh','Hooda','Corporate Developer',65000.00,'2008-05-25'),(35,35,'Prashant','Pawar','Environmental Specialist',57000.00,'2006-09-05'),(36,36,'Ranjit','Rao','CSR Manager',78000.00,'2023-03-14'),(37,37,'Shyam','Sharma','Security Officer',72000.00,'1993-12-16'),(38,38,'Himanshu','Hooda','IT Service Lead',93000.00,'1993-03-12'),(39,39,'Praveen','Patil','Internal Auditor',50000.00,'1999-02-02'),(40,40,'Rishi','Roy','Corporate Affairs Manager',56000.00,'1991-11-12'),(41,41,'Saurabh','Singh','Sustainability Specialist',59000.00,'2016-01-20'),(42,42,'Harish','Hegde','Talent Manager',60000.00,'2002-09-03'),(43,43,'Pranay','Purohit','Compensation Specialist',67000.00,'2019-03-14'),(44,44,'Rakesh','Reddy','Employee Relations Officer',71000.00,'1985-12-26'),(45,45,'Siddharth','Sinha','Performance Manager',74000.00,'2004-04-28'),(46,46,'Harsh','Hegde','Organizational Developer',87000.00,'2000-08-29'),(47,47,'Piyush','Pradhan','HR Operations Officer',62000.00,'2005-04-30'),(48,48,'Rohan','Raj','Diversity Specialist',68000.00,'2000-08-30'),(49,49,'Suraj','Saxena','Learning Developer',72000.00,'2002-04-30'),(50,50,'Himanshu','Hiran','Workforce Planner',80000.00,'1985-08-27');
/*!40000 ALTER TABLE `employee` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-07-29  0:49:12
