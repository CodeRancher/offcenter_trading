use ota;

DROP PROCEDURE IF EXISTS max_price_from_zone;

DELIMITER //
CREATE PROCEDURE max_price_from_zone (
   IN instrumentId INT UNSIGNED,
   IN timeframeId INT UNSIGNED,
   IN firstTime DATETIME,
   IN lastTime DATETIME,
   IN bidAsk INT UNSIGNED,
   IN supplyDemand INT UNSIGNED,
   OUT maxFromZoneId INT UNSIGNED,
   OUT maxFromZonePrice DECIMAL(9,5)
)
BEGIN
   SELECT IF(bidAsk=1, IF(supplyDemand=1, MIN(c.BidLow), MAX(c.BidHigh)), IF(supplyDemand=1, MIN(c.AskLow), MAX(c.AskHigh)))
     INTO maxFromZonePrice
     FROM ota.Candle c
    WHERE c.InstrumentId = instrumentId
      AND c.timeframeId = timeframeId
      AND c.Start >= firstTime
      AND c.Start <= lastTime
   LIMIT 1
   ;
   
   SELECT c.CandleId
     INTO maxFromZoneId
     FROM ota.Candle c
    WHERE c.InstrumentId = instrumentId
      AND c.timeframeId = timeframeId
      AND c.Start >= firstTime
      AND c.Start <= lastTime
      AND IF(bidAsk=1, IF(supplyDemand=1, c.BidLow, c.BidHigh), IF(supplyDemand=1, c.AskLow, c.AskHigh)) = maxFromZonePrice
   LIMIT 1
   ;
   
END //
DELIMITER ;
