USE ota;

DROP TABLE IF EXISTS invalid_zone;

CREATE TABLE invalid_zone (
   ZoneId int unsigned AUTO_INCREMENT PRIMARY KEY,
   invalid_zone_reason_id int unsigned NOT NULL,
   
   FOREIGN KEY (invalid_zone_reason_id)
      REFERENCES invalid_zone_reason(invalid_zone_reason_id)
);