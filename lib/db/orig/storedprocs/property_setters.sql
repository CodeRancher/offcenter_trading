USE ota;

DROP PROCEDURE IF EXISTS set_string_property;

DELIMITER //
CREATE PROCEDURE set_string_property (
   IN property_name varchar(50),
   IN primary_key varchar(50),
   IN secondary_key varchar(50),
   IN new_value varchar(200)
)
BEGIN
   INSERT INTO property(property_name, primary_key, secondary_key, string_value, int_value, double_value, date_value)
   VALUES (property_name, primary_key, secondary_key, new_value, null, null, null)
   ON DUPLICATE KEY UPDATE string_value = VALUES(int_value), int_value = null, double_value = null, date_value = null;
END //
DELIMITER ;


DROP PROCEDURE IF EXISTS set_integer_property;

DELIMITER //
CREATE PROCEDURE set_integer_property (
   IN property_name varchar(50),
   IN primary_key varchar(50),
   IN secondary_key varchar(50),
   IN new_value int
)
BEGIN
   INSERT INTO property(property_name, primary_key, secondary_key, string_value, int_value, double_value, date_value)
   VALUES (property_name, primary_key, secondary_key, null, new_value, null, null)
   ON DUPLICATE KEY UPDATE string_value = null, int_value = VALUES(int_value), double_value = null, date_value = null;
END //
DELIMITER ;


DROP PROCEDURE IF EXISTS set_double_property;

DELIMITER //
CREATE PROCEDURE set_double_property (
   IN property_name varchar(50),
   IN primary_key varchar(50),
   IN secondary_key varchar(50),
   IN new_value double
)
BEGIN
   INSERT INTO property(property_name, primary_key, secondary_key, string_value, int_value, double_value, date_value)
   VALUES (property_name, primary_key, secondary_key, null, null, new_value, null)
   ON DUPLICATE KEY UPDATE string_value = null, int_value = null, double_value = VALUES(int_value), date_value = null;
END //
DELIMITER ;


DROP PROCEDURE IF EXISTS set_date_property;

DELIMITER //
CREATE PROCEDURE set_date_property (
   IN property_name varchar(50),
   IN primary_key varchar(50),
   IN secondary_key varchar(50),
   IN new_value DATETIME
)
BEGIN
   INSERT INTO property(property_name, primary_key, secondary_key, string_value, int_value, double_value, date_value)
   VALUES (property_name, primary_key, secondary_key, null, null, null, new_value)
   ON DUPLICATE KEY UPDATE string_value = null, int_value = null, double_value = null, date_value = VALUES(int_value);
END //
DELIMITER ;
