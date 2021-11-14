use ota;

DROP PROCEDURE IF EXISTS start_of_stopping_candle;

DELIMITER //
CREATE PROCEDURE start_of_stopping_candle (
   IN instrumentId INT UNSIGNED,
   IN timeframeId INT UNSIGNED,
   IN stopTime DATETIME,
   IN proximal DECIMAL(9,5),
   IN bidAsk INT UNSIGNED,
   IN supplyDemand INT UNSIGNED,
   OUT candleId INT UNSIGNED,
   OUT candleTime DATETIME
)
BEGIN
   SELECT c.CandleId, c.Start
     INTO candleId, candleTime
     FROM ota.Candle c
    WHERE c.InstrumentId = instrumentId
      AND c.TimeframeId = timeframeId
      AND c.Start <= stopTime
      AND
         CASE
            -- Bid, Supply
            WHEN (bidAsk=1 AND supplyDemand=1) THEN c.BidOpen < proximal
            -- Bid, Demand
            WHEN (bidAsk=1 AND supplyDemand=2) THEN c.BidOpen > proximal
            -- Ask, Supply
            WHEN (bidAsk=2 AND supplyDemand=1) THEN c.AskOpen < proximal
            -- Ask, Demand
            WHEN (bidAsk=2 AND supplyDemand=2) THEN c.AskOpen > proximal
         END
      ORDER BY c.Start DESC
      LIMIT 1
   ;
END //
DELIMITER ;
