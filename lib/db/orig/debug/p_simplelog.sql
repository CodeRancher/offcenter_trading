USE ota;

DROP PROCEDURE IF EXISTS simple_log;

DELIMITER //
CREATE PROCEDURE simple_log (
   IN log_level VARCHAR(10),
   IN log_source VARCHAR(50),
   IN log_message VARCHAR(1000)
)
BEGIN
   INSERT INTO log(log_level, log_source, log_message)
   VALUES(log_level, log_source, log_message)
;
END //
DELIMITER ;
