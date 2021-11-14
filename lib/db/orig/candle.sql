USE ota;

CREATE TABLE Candle (
   CandleId int unsigned AUTO_INCREMENT PRIMARY KEY,
   InstrumentId int unsigned NOT NULL,
   TimeframeId int unsigned NOT NULL,

   AskOpen decimal(9,5) NOT NULL,
   AskClose decimal(9,5) NOT NULL,
   AskHigh decimal(9,5) NOT NULL,
   AskLow decimal(9,5) NOT NULL,

   BidOpen decimal(9,5) NOT NULL,
   BidClose decimal(9,5) NOT NULL,
   BidHigh decimal(9,5) NOT NULL,
   BidLow decimal(9,5) NOT NULL,
   
   Start DATETIME NOT NULL,

   FOREIGN KEY (InstrumentId)
      REFERENCES Instrument(InstrumentId)
      ON DELETE CASCADE,
   FOREIGN KEY (TimeframeId)
      REFERENCES Timeframe(TimeframeId)
      ON DELETE CASCADE
);

CREATE INDEX candle_inst_tf
ON Candle (InstrumentId, TimeFrameId);   

CREATE UNIQUE INDEX candle_inst_tf_st
ON Candle (InstrumentId, TimeFrameId, Start);

CREATE UNIQUE INDEX candle_st_inst_tf
ON Candle (Start, InstrumentId, TimeFrameId);

USE ota;
CREATE INDEX candle_inst_tf_ah
ON Candle (InstrumentId, TimeFrameId, AskHigh);   

CREATE INDEX candle_inst_tf_al
ON Candle (InstrumentId, TimeFrameId, AskLow);   

CREATE INDEX candle_inst_tf_bh
ON Candle (InstrumentId, TimeFrameId, BidHigh);   

CREATE INDEX candle_inst_tf_bl
ON Candle (InstrumentId, TimeFrameId, BidLow);   
