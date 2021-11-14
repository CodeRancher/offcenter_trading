USE ota;

DROP FUNCTION IF EXISTS var_msg;

DELIMITER //
CREATE FUNCTION var_msg(
   var_name VARCHAR(40),
   var_val VARCHAR(60)
) RETURNS VARCHAR(100)
DETERMINISTIC
BEGIN
   RETURN CONCAT(' ', var_name, '=''', IF(var_val IS NULL, 'NULL', var_val), '''');
END //
DELIMITER ;
