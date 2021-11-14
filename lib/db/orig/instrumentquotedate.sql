USE ota;

CREATE TABLE InstrumentQuoteDate (
   InstrumentQuoteDateId int AUTO_INCREMENT PRIMARY KEY,
   
   InstrumentId int unsigned NOT NULL,
   InstrumentBaseTimeframeId int unsigned NOT NULL,
   
   LatestQuoteDate DATETIME NOT NULL,
   OldestQuoteDate DATETIME NOT NULL,
   
   CONSTRAINT CkInstrument_Name UNIQUE(InstrumentId, InstrumentBaseTimeframeId)
)
