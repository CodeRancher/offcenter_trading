use ota;

DROP PROCEDURE IF EXISTS candle_after_candle;

DELIMITER //
CREATE PROCEDURE candle_after_candle (
   IN instrumentId INT UNSIGNED,
   IN timeframeId INT UNSIGNED,
   IN prevTime DATETIME,
   OUT id INT UNSIGNED,
   OUT candleTime DATETIME
)
BEGIN
   SELECT c.CandleId, c.Start
     INTO id, candleTime
     FROM ota.Candle c
    WHERE c.InstrumentId = instrumentId
      AND c.TimeframeId = timeframeId
      AND c.Start > prevTime
    ORDER BY c.Start
    LIMIT 1
;
END //
DELIMITER ;
