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
-- Table structure for table `dept`
--

DROP TABLE IF EXISTS `dept`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `dept` (
  `Dept_id` int NOT NULL,
  `Dept_name` varchar(60) DEFAULT NULL,
  `Dept_location` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`Dept_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `dept`
--

LOCK TABLES `dept` WRITE;
/*!40000 ALTER TABLE `dept` DISABLE KEYS */;
INSERT INTO `dept` VALUES (1,'HR','Mumbai'),(2,'Finance','Delhi'),(3,'IT','Bengaluru'),(4,'Computer','Mumbai'),(5,'Marketing','Chennai'),(6,'Sales','Kolkata'),(7,'Computer','Mumbai'),(8,'Operations','Ahmedabad'),(9,'Computer','Chennai'),(10,'Support','Jaipur'),(11,'IT','Kolkata'),(12,'Customer Service','Delhi'),(13,'Product Development','Bengaluru'),(14,'Quality Assurance','Hyderabad'),(15,'Computer','Bengaluru'),(16,'Engineering','Kolkata'),(17,'Public Relations','Pune'),(18,'Business Development','Ahmedabad'),(19,'Computer','Surat'),(20,'Procurement','Jaipur'),(21,'Legal Affairs','Mumbai'),(22,'IT','Delhi'),(23,'Compliance','Bengaluru'),(24,'Risk Management','Hyderabad'),(25,'Computer','Pune'),(26,'Facilities','Kolkata'),(27,'Investor Relations','Pune'),(28,'IT','Delhi'),(29,'Human Resources','Surat'),(30,'Finance and Accounting','Jaipur'),(31,'IT','Jaipur'),(32,'Manufacturing','Delhi'),(33,'Computer','Chennai'),(34,'Corporate Development','Hyderabad'),(35,'Environmental Affairs','Chennai'),(36,'Corporate Social Responsibility','Kolkata'),(37,'Computer','Bengaluru'),(38,'IT Services','Ahmedabad'),(39,'Internal Audit','Surat'),(40,'Corporate Affairs','Jaipur'),(41,'Sustainability','Mumbai'),(42,'Talent Management','Delhi'),(43,'Compensation and Benefits','Bengaluru'),(44,'IT','Hyderabad'),(45,'Performance Management','Chennai'),(46,'IT','Ahmedabad'),(47,'HR Operations','Pune'),(48,'IT','Hyderabad'),(49,'Learning and Development','Surat'),(50,'Workforce Planning','Jaipur');
/*!40000 ALTER TABLE `dept` ENABLE KEYS */;
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
