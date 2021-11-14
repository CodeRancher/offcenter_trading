use ota;

DROP PROCEDURE IF EXISTS max_retracement_candle;

DELIMITER //
CREATE PROCEDURE max_retracement_candle (
   IN instrumentId INT UNSIGNED,
   IN timeframeId INT UNSIGNED,
   IN firstTime DATETIME,
   IN lastTime DATETIME,
   IN bidAsk INT UNSIGNED,
   IN supplyDemand INT UNSIGNED,
   OUT id INT UNSIGNED
)
BEGIN
   SELECT a.CandleId
     INTO id
     FROM ota.Candle a
    INNER JOIN (
      SELECT IF(bidAsk=1, IF(supplyDemand=1, MAX(c.BidHigh), MIN(c.BidLow)), IF(supplyDemand=1, MAX(c.AskHigh), MIN(c.AskLow))) AS MaxRetracement
        FROM ota.Candle c
       WHERE c.InstrumentId = instrumentId
         AND c.timeframeId = timeframeId
         AND c.Start >= firstTime
         AND c.Start <= lastTime
      ) r ON CASE
             -- Bid, Supply
             WHEN (bidAsk=1 AND supplyDemand=1) THEN a.BidHigh = r.MaxRetracement
             -- Bid, Demand
             WHEN (bidAsk=1 AND supplyDemand=2) THEN a.BidLow = r.MaxRetracement
             -- Ask, Supply
             WHEN (bidAsk=2 AND supplyDemand=1) THEN a.AskHigh = r.MaxRetracement
             -- Ask, Demand
             WHEN (bidAsk=2 AND supplyDemand=2) THEN a.AskLow = r.MaxRetracement
          END
    WHERE a.InstrumentId = instrumentId
      AND a.TimeframeId = timeframeId
      AND a.Start >= firstTime
      AND a.Start <= lastTime
      LIMIT 1;
END //
DELIMITER ;
