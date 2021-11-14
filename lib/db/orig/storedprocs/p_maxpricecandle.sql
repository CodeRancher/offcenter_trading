use ota;

DROP PROCEDURE IF EXISTS max_price_candle;

DELIMITER //
CREATE PROCEDURE max_price_candle (
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
      SELECT IF(bidAsk=1, IF(supplyDemand=1, MIN(c.BidLow), MAX(c.BidHigh)), IF(supplyDemand=1, MIN(c.AskLow), MAX(c.AskHigh))) AS MaxPrice
        FROM ota.Candle c
       WHERE c.InstrumentId = instrumentId
         AND c.timeframeId = timeframeId
         AND c.Start >= firstTime
         AND c.Start <= lastTime
      ) r ON CASE
             -- Bid, Supply
             WHEN (bidAsk=1 AND supplyDemand=1) THEN a.BidLow = r.MaxPrice
             -- Bid, Demand
             WHEN (bidAsk=1 AND supplyDemand=2) THEN a.BidHigh = r.MaxPrice
             -- Ask, Supply
             WHEN (bidAsk=2 AND supplyDemand=1) THEN a.AskLow = r.MaxPrice
             -- Ask, Demand
             WHEN (bidAsk=2 AND supplyDemand=2) THEN a.AskHigh = r.MaxPrice
          END
    WHERE a.InstrumentId = instrumentId
      AND a.TimeframeId = timeframeId
      AND a.Start >= firstTime
      AND a.Start <= lastTime;
END //
DELIMITER ;
