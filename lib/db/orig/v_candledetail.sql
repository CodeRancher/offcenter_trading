USE ota;

DROP VIEW IF EXISTS CandleDetail;

CREATE VIEW CandleDetail AS
   SELECT CandleId, i.Name AS Instrument, tf.Name AS Timeframe, AskOpen, AskClose, AskHigh, AskLow, BidOpen, BidClose, BidHigh, BidLow, Start
      FROM ota.Candle c
      INNER JOIN ota.Instrument i ON c.InstrumentId = i.InstrumentId
      INNER JOIN ota.Timeframe tf ON c.TimeframeId = tf.TimeframeId;