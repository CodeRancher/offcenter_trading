USE ota;

DROP TABLE IF EXISTS property;

CREATE TABLE property (
   property_id int unsigned AUTO_INCREMENT PRIMARY KEY,
   
   property_name varchar(50) BINARY NOT NULL,
   primary_key varchar(50) BINARY NOT NULL,
   secondary_key varchar(50) BINARY NOT NULL,
   
   string_value varchar(200),
   int_value int,
   double_value double,
   date_value DATETIME,

   UNIQUE KEY (property_name, primary_key, secondary_key)
);