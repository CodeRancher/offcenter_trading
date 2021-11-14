USE ota;

DROP PROCEDURE IF EXISTS get_integer_property_with_default;

DELIMITER //
CREATE PROCEDURE get_integer_property_with_default (
   IN property_name varchar(50),
   IN primary_key varchar(50),
   IN secondary_key varchar(50),
   IN default_property_name varchar(50),
   IN default_primary_key varchar(50),
   IN default_secondary_key varchar(50),
   OUT return_value int
)
BEGIN
   CALL ota.get_integer_property (property_name, primary_key, secondary_key, return_value);
     
   IF (ISNULL(return_value)) THEN
      CALL ota.get_integer_property (default_property_name, default_primary_key, default_secondary_key, return_value);
      CALL ota.set_integer_property (property_name, primary_key, secondary_key, return_value);
   END IF;
END //
DELIMITER ;


DROP PROCEDURE IF EXISTS get_string_property_with_default;

DELIMITER //
CREATE PROCEDURE get_string_property_with_default (
   IN property_name varchar(50),
   IN primary_key varchar(50),
   IN secondary_key varchar(50),
   IN default_property_name varchar(50),
   IN default_primary_key varchar(50),
   IN default_secondary_key varchar(50),
   OUT return_value varchar(200)
)
BEGIN
   CALL ota.get_string_property (property_name, primary_key, secondary_key, return_value);
     
   IF (ISNULL(return_value)) THEN
      CALL ota.get_string_property (default_property_name, default_primary_key, default_secondary_key, return_value);
      CALL ota.set_string_property (property_name, primary_key, secondary_key, return_value);
   END IF;
END //
DELIMITER ;


DROP PROCEDURE IF EXISTS get_double_property_with_default;

DELIMITER //
CREATE PROCEDURE get_double_property_with_default (
   IN property_name varchar(50),
   IN primary_key varchar(50),
   IN secondary_key varchar(50),
   IN default_property_name varchar(50),
   IN default_primary_key varchar(50),
   IN default_secondary_key varchar(50),
   OUT return_value double
)
BEGIN
   CALL ota.get_double_property (property_name, primary_key, secondary_key, return_value);
     
   IF (ISNULL(return_value)) THEN
      CALL ota.get_double_property (default_property_name, default_primary_key, default_secondary_key, return_value);
      CALL ota.set_double_property (property_name, primary_key, secondary_key, return_value);
   END IF;
END //
DELIMITER ;


DROP PROCEDURE IF EXISTS get_date_property_with_default;

DELIMITER //
CREATE PROCEDURE get_date_property_with_default (
   IN property_name varchar(50),
   IN primary_key varchar(50),
   IN secondary_key varchar(50),
   IN default_property_name varchar(50),
   IN default_primary_key varchar(50),
   IN default_secondary_key varchar(50),
   OUT return_value DATETIME
)
BEGIN
   CALL ota.get_date_property (property_name, primary_key, secondary_key, return_value);
     
   IF (ISNULL(return_value)) THEN
      CALL ota.get_date_property (default_property_name, default_primary_key, default_secondary_key, return_value);
      CALL ota.set_date_property (property_name, primary_key, secondary_key, return_value);
   END IF;
END //
DELIMITER ;
