USE ota;

DROP VIEW IF EXISTS CandleInstrumentByParentTimeframe;

-- 
-- SELECT * FROM CandleInstrumentByParentTimeframe;
-- 
-- *****************************************************************************

CREATE VIEW CandleInstrumentByParentTimeframe AS
   SELECT 
         cit.InstrumentId AS InstrumentId,
         cit.TimeframeId AS TimeframeId,
         tf.ParentTimeframeId AS ParentTimeframeId,
         tf.RefiningTimeframeId AS RefiningTimeframeId
      FROM ota.CandleInstrumentTimeframe cit
      INNER JOIN ota.Timeframe tf ON cit.TimeframeId = tf.TimeframeId;