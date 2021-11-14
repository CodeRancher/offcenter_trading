use ota;

--
-- CALL find_candle_that_contains_time(613, 14, '2008-10-10 12:23:05', @result_id, @result_time);
-- CALL find_candle_that_contains_time(613, 14, '2015-10-10 12:23:05', @result_id, @result_time);
-- SELECT @result_id, @result_time;
-- *******************************************************************************

DROP PROCEDURE IF EXISTS find_candle_that_contains_time;

DELIMITER //
CREATE PROCEDURE find_candle_that_contains_time (
   IN instrument_id INT UNSIGNED,
   IN timeframe_id INT UNSIGNED,
   IN search_time DATETIME,
   OUT candle_id INT UNSIGNED,
   OUT candle_time DATETIME
)
BEGIN
   SELECT MAX(c.Start)
     INTO candle_time
     FROM ota.Candle c
    WHERE c.InstrumentId = instrument_id
      AND c.timeframeId = timeframe_id
      AND c.Start <= search_time
   LIMIT 1;
   
   SELECT c.CandleId
     INTO candle_id
     FROM ota.Candle c
    WHERE c.InstrumentId = instrument_id
      AND c.timeframeId = timeframe_id
      AND c.Start = candle_time;
END //
DELIMITER ;
