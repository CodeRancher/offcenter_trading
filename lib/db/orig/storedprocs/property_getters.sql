USE ota;

DROP PROCEDURE IF EXISTS get_integer_property;

DELIMITER //
CREATE PROCEDURE get_integer_property (
   IN property_name varchar(50),
   IN primary_key varchar(50),
   IN secondary_key varchar(50),
   OUT return_value int
)
BEGIN
   SELECT int_value
   INTO return_value
   FROM property p
   WHERE p.property_name = property_name
     AND p.primary_key = primary_key
     AND p.secondary_key = secondary_key;
END //
DELIMITER ;


DROP PROCEDURE IF EXISTS get_string_property;

DELIMITER //
CREATE PROCEDURE get_string_property (
   IN property_name varchar(50),
   IN primary_key varchar(50),
   IN secondary_key varchar(50),
   OUT return_value varchar(100)
)
BEGIN
   SELECT string_value
   INTO return_value
   FROM property p
   WHERE p.property_name = property_name
     AND p.primary_key = primary_key
     AND p.secondary_key = secondary_key;
END //
DELIMITER ;


DROP PROCEDURE IF EXISTS get_double_property;

DELIMITER //
CREATE PROCEDURE get_double_property (
   IN property_name varchar(50),
   IN primary_key varchar(50),
   IN secondary_key varchar(50),
   OUT return_value double
)
BEGIN
   SELECT double_value
   INTO return_value
   FROM property p
   WHERE p.property_name = property_name
     AND p.primary_key = primary_key
     AND p.secondary_key = secondary_key;
END //
DELIMITER ;


DROP PROCEDURE IF EXISTS get_date_property;

DELIMITER //
CREATE PROCEDURE get_date_property (
   IN property_name varchar(50),
   IN primary_key varchar(50),
   IN secondary_key varchar(50),
   OUT return_value DATETIME
)
BEGIN
   SELECT date_value
   INTO return_value
   FROM property p
   WHERE p.property_name = property_name
     AND p.primary_key = primary_key
     AND p.secondary_key = secondary_key;
END //
DELIMITER ;
