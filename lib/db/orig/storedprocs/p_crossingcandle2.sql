use ota;

DROP PROCEDURE IF EXISTS crossing_candle;

DELIMITER //
CREATE PROCEDURE crossing_candle (
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
   OUT crossOutTime DATETIME,
   OUT zoneEntryId INT UNSIGNED,
   OUT zoneEntryPrice DECIMAL(9,5)
)
BEGIN
   CASE bidAsk
      WHEN 1 THEN BEGIN
         CASE supplyDemand
            WHEN 1 THEN BEGIN
               SELECT c.CandleId, c.Start
                  INTO crossInId, crossInTime
                  FROM ota.Candle c
                  WHERE c.InstrumentId = instrumentId
                     AND c.timeframeId = timeframeId
                     AND c.Start >= startTime
                     AND c.Start <= stopTime
                     AND c.BidHigh > proximal
                  LIMIT 1;
            END;
            WHEN 2 THEN BEGIN
               SELECT c.CandleId, c.Start
                  INTO crossInId, crossInTime
                  FROM ota.Candle c
                  WHERE c.InstrumentId = instrumentId
                     AND c.timeframeId = timeframeId
                     AND c.Start >= startTime
                     AND c.Start <= stopTime
                     AND c.BidLow < proximal
                  LIMIT 1;
            END;
         END CASE;
      END;
      WHEN 2 THEN BEGIN
         CASE supplyDemand
            WHEN 1 THEN BEGIN
               SELECT c.CandleId, c.Start
                  INTO crossInId, crossInTime
                  FROM ota.Candle c
                  WHERE c.InstrumentId = instrumentId
                     AND c.timeframeId = timeframeId
                     AND c.Start >= startTime
                     AND c.Start <= stopTime
                     AND c.AskHigh > proximal
                  LIMIT 1;
            END;
            WHEN 2 THEN BEGIN
               SELECT c.CandleId, c.Start
                  INTO crossInId, crossInTime
                  FROM ota.Candle c
                  WHERE c.InstrumentId = instrumentId
                     AND c.timeframeId = timeframeId
                     AND c.Start >= startTime
                     AND c.Start <= stopTime
                     AND c.AskLow < proximal
                  LIMIT 1;
            END;
         END CASE;
      END;
   END CASE;

   END //
DELIMITER ;
