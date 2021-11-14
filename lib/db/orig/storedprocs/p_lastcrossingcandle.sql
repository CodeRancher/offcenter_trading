use ota;

DROP PROCEDURE IF EXISTS last_crossing_candle;

DELIMITER //
CREATE PROCEDURE last_crossing_candle (
   IN instrumentId INT UNSIGNED,
   IN timeframeId INT UNSIGNED,
   IN firstTime DATETIME,
   IN lastTime DATETIME,
   IN price DECIMAL(9,5),
   IN bidAsk INT UNSIGNED,
   IN supplyDemand INT UNSIGNED,
   OUT id INT UNSIGNED,
   OUT crossTime DATETIME
)
BEGIN
   SELECT a.CandleId, a.Start
   INTO id, crossTime
   FROM ota.Candle a
   INNER JOIN (
      SELECT MAX(b.Start) Start
      FROM ota.Candle b
      INNER JOIN (
          SELECT MIN(c.Start) Start
          FROM ota.Candle c
          WHERE c.InstrumentId = instrumentId
            AND c.timeframeId = timeframeId
            AND Start >= firstTime
            AND Start < lastTime
            AND
               CASE
                  -- Bid, Supply
                  WHEN (bidAsk=1 AND supplyDemand=1) THEN c.BidHigh < price
                  -- Bid, Demand
                  WHEN (bidAsk=1 AND supplyDemand=2) THEN c.BidLow > price
                  -- Ask, Supply
                  WHEN (bidAsk=2 AND supplyDemand=1) THEN c.AskHigh < price
                  -- Ask, Demand
                  WHEN (bidAsk=2 AND supplyDemand=2) THEN c.AskLow > price
               END
      ) d ON b.Start < d.Start
      WHERE b.InstrumentId = instrumentId
        AND b.timeframeId = timeframeId
        AND b.Start >= firstTime
   ) e ON a.Start = e.Start
   WHERE a.InstrumentId = instrumentId
     AND a.timeframeId = timeframeId
;
END //
DELIMITER ;
