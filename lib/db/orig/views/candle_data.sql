USE ota;

DROP VIEW IF EXISTS candle_data;

CREATE VIEW candle_data AS
   SELECT
      CandleId,
      InstrumentId,
      TimeframeId,
      AskOpen,
      AskClose,
      AskHigh,
      AskLow,
      BidOpen,
      BidClose,
      BidHigh,
      BidLow,
      Start,
      AS Stop
   FROM ota.Candle
   ;
   
SELECT * FROM ota.Timeframe;