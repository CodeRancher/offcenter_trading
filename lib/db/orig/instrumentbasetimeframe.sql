USE ota;

CREATE TABLE InstrumentBaseTimeframe (
   InstrumentBaseTimeframeId int unsigned AUTO_INCREMENT PRIMARY KEY,
   
   InstrumentId int unsigned NOT NULL,
   TimeframeId int unsigned NOT NULL,

   FOREIGN KEY (InstrumentId)
      REFERENCES Instrument(InstrumentId),
   FOREIGN KEY (TimeframeId)
      REFERENCES Timeframe(TimeframeId)
)
