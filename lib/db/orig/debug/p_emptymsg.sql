USE ota;

DROP PROCEDURE IF EXISTS empty_msg;

DELIMITER //
CREATE PROCEDURE empty_msg ()
BEGIN
   INSERT INTO log(log_level, log_source, log_message)
   VALUES('empty', '', '')
;
END //
DELIMITER ;
