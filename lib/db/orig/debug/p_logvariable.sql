USE ota;

DROP PROCEDURE IF EXISTS log_variable;

DELIMITER //
CREATE PROCEDURE log_variable (
   IN log_source VARCHAR(50),
   IN variable_name VARCHAR(50),
   IN variable_value VARCHAR(1000)
)
BEGIN
   INSERT INTO log(log_level, log_source, log_message)
   VALUES('variable', log_source, var_msg(variable_name, variable_value))
;
END //
DELIMITER ;
