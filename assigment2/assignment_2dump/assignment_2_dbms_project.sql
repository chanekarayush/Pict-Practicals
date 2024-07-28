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
-- Table structure for table `project`
--

DROP TABLE IF EXISTS `project`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `project` (
  `Proj_id` int NOT NULL,
  `Dept_id` int DEFAULT NULL,
  `Proj_name` varchar(100) DEFAULT NULL,
  `Proj_Location` varchar(100) DEFAULT NULL,
  `Proj_cost` double(10,2) DEFAULT NULL,
  `Proj_year` int DEFAULT NULL,
  PRIMARY KEY (`Proj_id`),
  KEY `Dept_id` (`Dept_id`),
  CONSTRAINT `project_ibfk_1` FOREIGN KEY (`Dept_id`) REFERENCES `dept` (`Dept_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `project`
--

LOCK TABLES `project` WRITE;
/*!40000 ALTER TABLE `project` DISABLE KEYS */;
INSERT INTO `project` VALUES (1,1,'Employee Engagement Initiative','Mumbai',50500.00,2005),(2,2,'Financial Software Upgrade','Delhi',750000.00,2010),(3,3,'IT Infrastructure Overhaul','Bengaluru',150000.00,2000),(4,4,'New Product Launch','Hyderabad',200000.00,2015),(5,5,'Market Expansion Plan','Chennai',175000.00,2008),(6,6,'Sales Training Program','Kolkata',125000.00,1998),(7,7,'Legal Compliance Audit','Pune',60000.00,2020),(8,8,'Operational Efficiency Project','Ahmedabad',300000.00,2005),(9,9,'Office Renovation','Surat',45000.00,2012),(10,10,'Customer Feedback System','Jaipur',99000.00,2018),(11,11,'Supply Chain Optimization','Mumbai',470000.00,2021),(12,12,'Customer Service Improvement','Delhi',80000.00,2019),(13,13,'Product Redesign','Bengaluru',550000.00,1995),(14,14,'Quality Assurance Enhancement','Hyderabad',92000.00,2022),(15,15,'Purchasing System Overhaul','Chennai',105000.00,2014),(16,16,'Engineering Innovation','Kolkata',670000.00,1990),(17,17,'Public Relations Campaign','Pune',130000.00,2016),(18,18,'Business Development Strategy','Ahmedabad',450000.00,2003),(19,19,'Training Program Development','Surat',110000.00,2020),(20,20,'Procurement Process Improvement','Jaipur',360000.00,2013),(21,21,'Legal Affairs Review','Mumbai',90000.00,2019),(22,22,'Corporate Strategy Formulation','Delhi',520000.00,2010),(23,23,'Compliance Review','Bengaluru',49000.00,2021),(24,24,'Risk Management Framework','Hyderabad',240000.00,2007),(25,25,'Government Relations Plan','Chennai',300000.00,1995),(26,26,'Facilities Management Upgrade','Kolkata',85000.00,2018),(27,27,'Investor Relations Improvement','Pune',190000.00,2006),(28,28,'Corporate Communications Plan','Ahmedabad',120000.00,2011),(29,29,'Human Resources Initiative','Surat',250000.00,2012),(30,30,'Financial Analysis System','Jaipur',57000.00,2002),(31,31,'Technical Support System','Mumbai',400000.00,2023),(32,32,'Manufacturing Process Review','Delhi',70000.00,2001),(33,33,'Supply Chain Management','Bengaluru',800000.00,2015),(34,34,'Corporate Development Program','Hyderabad',620000.00,1999),(35,35,'Environmental Sustainability Project','Chennai',100000.00,2024),(36,36,'Corporate Social Responsibility','Kolkata',490000.00,2000),(37,37,'Security System Upgrade','Pune',210000.00,2017),(38,38,'IT Services Enhancement','Ahmedabad',110000.00,2013),(39,39,'Internal Audit Program','Surat',67000.00,2011),(40,40,'Corporate Affairs Strategy','Jaipur',49000.00,2020),(41,41,'Sustainability Initiative','Mumbai',130000.00,2012),(42,42,'Talent Management Program','Delhi',80000.00,2014),(43,43,'Compensation and Benefits Review','Bengaluru',150000.00,2023),(44,44,'Employee Relations Strategy','Hyderabad',180000.00,2021),(45,45,'Performance Management System','Chennai',250000.00,1997),(46,46,'Organizational Development Plan','Kolkata',450000.00,2009),(47,47,'HR Operations Improvement','Pune',310000.00,2010),(48,48,'Diversity and Inclusion Initiative','Ahmedabad',260000.00,1998),(49,49,'Learning and Development Program','Surat',100000.00,2011),(50,50,'Workforce Planning Strategy','Jaipur',220000.00,2024);
/*!40000 ALTER TABLE `project` ENABLE KEYS */;
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
