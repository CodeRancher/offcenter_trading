USE ota;

DROP VIEW IF EXISTS CandleInstrumentTimeframe;

CREATE VIEW CandleInstrumentTimeframe AS
   SELECT c.InstrumentId, c.TimeframeId
      FROM ota.Candle c
      GROUP BY c.InstrumentId, c.TimeframeId;