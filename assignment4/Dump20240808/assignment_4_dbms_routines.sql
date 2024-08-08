CREATE DATABASE  IF NOT EXISTS `assignment_4_dbms` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `assignment_4_dbms`;
-- MySQL dump 10.13  Distrib 8.0.34, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: assignment_4_dbms
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
-- Dumping events for database 'assignment_4_dbms'
--

--
-- Dumping routines for database 'assignment_4_dbms'
--
/*!50003 DROP PROCEDURE IF EXISTS `ReturnBook` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = cp850 */ ;
/*!50003 SET character_set_results = cp850 */ ;
/*!50003 SET collation_connection  = cp850_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `ReturnBook`(IN p_roll_no INT, IN p_name_of_book VARCHAR(100))
BEGIN
        DECLARE v_date_of_issue DATE;
        DECLARE v_current_date DATE;
        DECLARE v_days INT;
        DECLARE v_fine_amount DECIMAL(10, 2) DEFAULT 0;
        DECLARE v_book_exists INT;
        DECLARE v_error_code VARCHAR(5);
        DECLARE v_error_message TEXT;
    
        
        DECLARE CONTINUE HANDLER FOR SQLEXCEPTION
        BEGIN
           
            GET DIAGNOSTICS CONDITION 1
                v_error_code = RETURNED_SQLSTATE,
                v_error_message = MESSAGE_TEXT;
            ROLLBACK;
            SELECT CONCAT('An error occurred. Error Code: ', v_error_code, ', Message: ', v_error_message) AS ErrorMessage;
        END;
    
        
        DECLARE CONTINUE HANDLER FOR NOT FOUND
        BEGIN
            ROLLBACK;
            SELECT 'The book record was not found for the provided Roll Number and Book Name' AS ErrorMessage;
        END;
    
        SET v_current_date = CURDATE();
        
        
        SELECT COUNT(*) INTO v_book_exists
        FROM Borrower
        WHERE Rollin = p_roll_no AND NameofBook = p_name_of_book AND Status = 'I';
        
        IF v_book_exists = 0 THEN
            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'No book record found or book is not issued.';
        END IF;
    
        
        SELECT DateofIssue INTO v_date_of_issue
        FROM Borrower
        WHERE Rollin = p_roll_no AND NameofBook = p_name_of_book AND Status = 'I';
    
        
        SET v_days = DATEDIFF(v_current_date, v_date_of_issue);
        
        
        IF v_days > 30 THEN
            SET v_fine_amount = (v_days - 30) * 50 + (30 * 5);
        ELSEIF v_days >= 15 THEN
            SET v_fine_amount = v_days * 5;
        ELSE
            SET v_fine_amount = 0;
        END IF;
    
        
        UPDATE Borrower
        SET Status = 'R'
        WHERE Rollin = p_roll_no AND NameofBook = p_name_of_book AND Status = 'I';
        
        
        IF v_fine_amount > 0 THEN
            INSERT INTO Fine (Roll_no, Date, Amt)
            VALUES (p_roll_no, v_current_date, v_fine_amount);
        END IF;
    
        COMMIT;
        
        
        SELECT CONCAT('Book returned. Fine amount: Rs ', v_fine_amount) AS ResultMessage;
    
    END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-08-08  7:49:03
