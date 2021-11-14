USE ota;

DROP TABLE IF EXISTS zone_entry;

CREATE TABLE zone_entry (
   -- Record ID
   zone_entry_id int unsigned AUTO_INCREMENT PRIMARY KEY,

   ZoneId int unsigned NOT NULL,
   TimeframeId int unsigned NOT NULL,

   cross_in_candle_id int unsigned NOT NULL,
   zone_entry_candle_id int unsigned,
   zone_entry_price decimal(9,5) NOT NULL,
   cross_out_candle_id int unsigned NOT NULL,
   zone_max_exit_candle_id int unsigned,
   zone_max_price decimal(9,5),

   FOREIGN KEY (ZoneId)
      REFERENCES Zone(ZoneId),
   FOREIGN KEY (TimeframeId)
      REFERENCES Timeframe(TimeframeId),	  
   FOREIGN KEY (cross_in_candle_id)
      REFERENCES Candle(CandleId),
   FOREIGN KEY (zone_entry_candle_id)
      REFERENCES Candle(CandleId),
   FOREIGN KEY (cross_out_candle_id)
      REFERENCES Candle(CandleId),
   FOREIGN KEY (zone_max_exit_candle_id)
      REFERENCES Candle(CandleId),
   INDEX zone_entry_zone_tf(ZoneId, TimeframeId)
);


