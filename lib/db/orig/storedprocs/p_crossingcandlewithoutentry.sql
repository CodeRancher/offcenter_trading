use ota;

DROP PROCEDURE IF EXISTS crossing_candle_without_entry;

DELIMITER //
CREATE PROCEDURE crossing_candle_without_entry (
   IN instrumentId INT UNSIGNED,
   IN timeframeId INT UNSIGNED,
   IN startTime DATETIME,
   IN stopTime DATETIME,
   IN proximal DECIMAL(9,5),
   IN bidAsk INT UNSIGNED,
   IN supplyDemand INT UNSIGNED,
   OUT crossInId INT UNSIGNED,
   OUT crossInTime DATETIME,
   OUT crossOutId INT UNSIGNED,
   OUT crossOutTime DATETIME
)
BEGIN
   SELECT c.CandleId, c.Start
     INTO crossInId, crossInTime
     FROM ota.Candle c
    WHERE c.InstrumentId = instrumentId
      AND c.timeframeId = timeframeId
      AND c.Start >= startTime
      AND c.Start < stopTime
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
      LIMIT 1;

   IF ISNULL(crossInId) THEN
      SELECT NULL, NULL
      INTO crossOutId, crossOutTime;
   ELSE
      SELECT c.CandleId, c.Start
        INTO crossOutId, crossOutTime
        FROM ota.Candle c
       WHERE c.InstrumentId = instrumentId
         AND c.timeframeId = timeframeId
         AND c.Start > crossInTime
         AND c.Start < stopTime
         AND
            CASE
               -- Bid, Supply
               WHEN (bidAsk=1 AND supplyDemand=1) THEN c.BidHigh < proximal
               -- Bid, Demand
               WHEN (bidAsk=1 AND supplyDemand=2) THEN c.BidLow > proximal
               -- Ask, Supply
               WHEN (bidAsk=2 AND supplyDemand=1) THEN c.AskHigh < proximal
               -- Ask, Demand
               WHEN (bidAsk=2 AND supplyDemand=2) THEN c.AskLow > proximal
            END
         ORDER BY c.Start
         LIMIT 1;
   END IF;
END //
DELIMITER ;
