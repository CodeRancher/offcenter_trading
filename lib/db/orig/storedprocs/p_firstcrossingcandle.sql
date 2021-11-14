use ota;

DROP PROCEDURE IF EXISTS first_crossing_candle;

DELIMITER //
CREATE PROCEDURE first_crossing_candle (
   IN instrumentId INT UNSIGNED,
   IN timeframeId INT UNSIGNED,
   IN startTime DATETIME,
   IN proximal DECIMAL(9,5),
   IN bidAsk INT UNSIGNED,
   IN supplyDemand INT UNSIGNED,
   OUT id INT UNSIGNED,
   OUT crossTime DATETIME
)
BEGIN
   SELECT c.CandleId, c.Start
     INTO id, crossTime
     FROM ota.Candle c
    WHERE c.InstrumentId = instrumentId
      AND c.timeframeId = timeframeId
      AND c.Start > startTime
      AND
         CASE
            -- Bid, Supply
            WHEN (bidAsk=1 AND supplyDemand=1) THEN c.BidHigh > proximal
            -- Bid, Demand
            WHEN (bidAsk=1 AND supplyDemand=2) THEN c.BidLow < proximal
            -- Ask, Supply
            WHEN (bidAsk=2 AND supplyDemand=1) THEN c.AskHigh > proximal
            -- Ask, Demand
            WHEN (bidAsk=2 AND supplyDemand=2) THEN c.AskLow < proximal
         END
      ORDER BY c.Start
      LIMIT 1
;
END //
DELIMITER ;
