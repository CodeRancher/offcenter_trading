use ota;

DROP PROCEDURE IF EXISTS stopping_candle;

DELIMITER //
CREATE PROCEDURE stopping_candle (
   IN instrumentId INT UNSIGNED,
   IN timeframeId INT UNSIGNED,
   IN startTime DATETIME,
   IN distal DECIMAL(9,5),
   IN bidAsk INT UNSIGNED,
   IN supplyDemand INT UNSIGNED,
   OUT stopCandleId INT UNSIGNED,
   OUT stopCandleTime DATETIME
)
BEGIN
   -- CALL log_variable('stopping_candle', 'instrumentId', instrumentId);
   -- CALL log_variable('stopping_candle', 'timeframeId', timeframeId);
   -- CALL log_variable('stopping_candle', 'startTime', startTime);
   -- CALL log_variable('stopping_candle', 'stopTime', stopTime);
   -- CALL log_variable('stopping_candle', 'distal', distal);
   -- CALL log_variable('stopping_candle', 'bidAsk', bidAsk);
   -- CALL log_variable('stopping_candle', 'supplyDemand', supplyDemand);

   CASE
      -- Bid, Supply
      WHEN (bidAsk=1 AND supplyDemand=1) THEN
         SELECT c.CandleId, c.Start
           INTO stopCandleId, stopCandleTime
           FROM ota.Candle c
          WHERE c.InstrumentId = instrumentId
            AND c.TimeframeId = timeframeId
            AND c.Start > startTime
            AND c.BidHigh > distal
          LIMIT 1;
      -- Bid, Demand
      WHEN (bidAsk=1 AND supplyDemand=2) THEN
         SELECT c.CandleId, c.Start
         INTO stopCandleId, stopCandleTime
         FROM ota.Candle c
        WHERE c.InstrumentId = instrumentId
          AND c.TimeframeId = timeframeId
          AND c.Start > startTime
          AND c.BidLow < distal
          LIMIT 1;
      -- Ask, Supply
      WHEN (bidAsk=2 AND supplyDemand=1) THEN
         SELECT c.CandleId, c.Start
           INTO stopCandleId, stopCandleTime
           FROM ota.Candle c
          WHERE c.InstrumentId = instrumentId
            AND c.TimeframeId = timeframeId
            AND c.Start > startTime
            AND c.AskHigh > distal
          LIMIT 1;
      -- Ask, Demand
      WHEN (bidAsk=2 AND supplyDemand=2) THEN
         SELECT c.CandleId, c.Start
           INTO stopCandleId, stopCandleTime
           FROM ota.Candle c -- USE INDEX (candle_st_inst_tf)
          WHERE c.InstrumentId = instrumentId
            AND c.TimeframeId = timeframeId
            AND c.Start > startTime
            AND c.AskLow < distal
          LIMIT 1;
   END CASE;

   -- CALL log_variable('stopping_candle', 'stopCandleId', stopCandleId);
   -- CALL log_variable('stopping_candle', 'stopCandleTime', stopCandleTime);
END //
DELIMITER ;
