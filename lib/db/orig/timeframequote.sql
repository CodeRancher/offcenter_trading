USE ota;

CREATE TABLE TimeframeQuote (
   TimeframeQuoteId int unsigned AUTO_INCREMENT PRIMARY KEY,

   InstrumentId int unsigned NOT NULL,
   TimeframeId int unsigned NOT NULL,
   
   LatestQuote DATETIME,
   OldestQuote DATETIME,
   -- LatestQuote TIMESTAMP,
   -- OldestQuote TIMESTAMP,
	
	CONSTRAINT CkTimeframeQuotes_Pair UNIQUE(InstrumentId, TimeframeId),
   FOREIGN KEY (InstrumentId)
      REFERENCES Instrument(InstrumentId),
   FOREIGN KEY (TimeframeId)
      REFERENCES Timeframe(TimeframeId)
)
