USE ota;

DROP TABLE IF EXISTS ZoneStop;

CREATE TABLE ZoneStop (
   -- Record ID
   ZoneStopId int unsigned AUTO_INCREMENT PRIMARY KEY,

   ZoneId int unsigned NOT NULL,
   TimeframeId int unsigned NOT NULL,

   FirstCandleId int unsigned,
   LastCandleId int unsigned,

   FOREIGN KEY (ZoneId)
      REFERENCES Zone(ZoneId),
   FOREIGN KEY (TimeframeId)
      REFERENCES Timeframe(TimeframeId),
   FOREIGN KEY (FirstCandleId)
      REFERENCES Candle(CandleId),
   FOREIGN KEY (LastCandleId)
      REFERENCES Candle(CandleId),
   UNIQUE INDEX(ZoneId)
)
