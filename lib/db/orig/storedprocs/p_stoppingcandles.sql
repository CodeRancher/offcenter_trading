use ota;

DROP PROCEDURE IF EXISTS stopping_candles;

DELIMITER //
CREATE PROCEDURE stopping_candles (
   IN instrumentId INT UNSIGNED,
   IN timeframeId INT UNSIGNED,
   IN startTime DATETIME,
   IN proximal DECIMAL(9,5),
   IN distal DECIMAL(9,5),
   IN bidAsk INT UNSIGNED,
   IN supplyDemand INT UNSIGNED,
   OUT startCandleId INT UNSIGNED,
   OUT startCandleTime DATETIME,
   OUT stopCandleId INT UNSIGNED,
   OUT stopCandleTime DATETIME
)
BEGIN
   DECLARE beginId INT UNSIGNED;
   DECLARE beginTime DATETIME;
   DECLARE endId INT UNSIGNED;
   DECLARE endTime DATETIME;
   CALL stopping_candle(instrumentId, timeframeId, startTime, distal, bidAsk, supplyDemand, endId, endTime);
   CALL start_of_stopping_candle(instrumentId, timeframeId, endTime, proximal, bidAsk, supplyDemand, beginId, beginTime);
   SELECT beginId, beginTime, endId, endTime
   INTO startCandleId, startCandleTime, stopCandleId, stopCandleTime;   
END //
DELIMITER ;
