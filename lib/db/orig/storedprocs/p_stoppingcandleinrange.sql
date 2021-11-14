use ota;

DROP PROCEDURE IF EXISTS stopping_candle_in_range;

DELIMITER //
CREATE PROCEDURE stopping_candle_in_range (
   IN instrumentId INT UNSIGNED,
   IN timeframeId INT UNSIGNED,
   IN startTime DATETIME,
   IN endTime DATETIME,
   IN distal DECIMAL(9,5),
   IN bidAsk INT UNSIGNED,
   IN supplyDemand INT UNSIGNED,
   OUT stopCandleId INT UNSIGNED,
   OUT stopCandleTime DATETIME
)
BEGIN
   -- CALL log_variable('stopping_candle_in_range', 'instrumentId', instrumentId);
   -- CALL log_variable('stopping_candle_in_range', 'timeframeId', timeframeId);
   -- CALL log_variable('stopping_candle_in_range', 'startTime', startTime);
   -- CALL log_variable('stopping_candle_in_range', 'endTime', endTime);
   -- CALL log_variable('stopping_candle_in_range', 'distal', distal);
   -- CALL log_variable('stopping_candle_in_range', 'bidAsk', bidAsk);
   -- CALL log_variable('stopping_candle_in_range', 'supplyDemand', supplyDemand);
   
   SELECT c.CandleId, c.Start
     INTO stopCandleId, stopCandleTime
     FROM ota.Candle c
    WHERE c.InstrumentId = instrumentId
      AND c.TimeframeId = timeframeId
      AND c.Start >= startTime
      AND c.Start <= endTime
      AND
         CASE
            -- Bid, Supply
            WHEN (bidAsk=1 AND supplyDemand=1) THEN c.BidHigh > distal
            -- Bid, Demand
            WHEN (bidAsk=1 AND supplyDemand=2) THEN c.BidLow < distal
            -- Ask, Supply
            WHEN (bidAsk=2 AND supplyDemand=1) THEN c.AskHigh > distal
            -- Ask, Demand
            WHEN (bidAsk=2 AND supplyDemand=2) THEN c.AskLow < distal
         END
      ORDER BY c.Start
      LIMIT 1;

   -- CALL log_variable('stopping_candle_in_range', 'stopCandleId', stopCandleId);
   -- CALL log_variable('stopping_candle_in_range', 'stopCandleTime', stopCandleTime);

END //
DELIMITER ;
