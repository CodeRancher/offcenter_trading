USE ota;

DROP TABLE IF EXISTS ZoneRetracement;

CREATE TABLE ZoneRetracement (
   -- Record ID
   ZoneRetracementId int unsigned AUTO_INCREMENT PRIMARY KEY,

   ZoneId int unsigned NOT NULL,
   TimeframeId int unsigned NOT NULL,

   FirstCrossingCandleId int unsigned NOT NULL,
   MaxEntryCandleId int unsigned,
   LastCrossingCandleId int unsigned NOT NULL,
   MaxRetracementCandleId int unsigned,

   FOREIGN KEY (ZoneId)
      REFERENCES Zone(ZoneId),
   FOREIGN KEY (TimeframeId)
      REFERENCES Timeframe(TimeframeId),	  
   FOREIGN KEY (FirstCrossingCandleId)
      REFERENCES Candle(CandleId),
   FOREIGN KEY (MaxEntryCandleId)
      REFERENCES Candle(CandleId),
   FOREIGN KEY (LastCrossingCandleId)
      REFERENCES Candle(CandleId),
   FOREIGN KEY (MaxRetracementCandleId)
      REFERENCES Candle(CandleId)
)
