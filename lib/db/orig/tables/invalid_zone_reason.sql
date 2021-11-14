USE ota;

DROP TABLE IF EXISTS invalid_zone_reason;

CREATE TABLE invalid_zone_reason (
   invalid_zone_reason_id int unsigned AUTO_INCREMENT PRIMARY KEY,
   description varchar(50) NOT NULL
);