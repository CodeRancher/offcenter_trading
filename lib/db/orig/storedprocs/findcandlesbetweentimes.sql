use ota;

--
-- CALL find_candles_between_times(613, 14, '2008-10-10 12:23:05', '2009-03-10 12:23:05', @start_id, @start_time, @end_id, @end_time);
-- CALL find_candles_between_times(613, 14, '2014-01-01 12:23:05', '2014-01-29 12:23:05', @start_id, @start_time, @end_id, @end_time);
-- SELECT @start_id, @start_time, @end_id, @end_time;
-- *******************************************************************************

DROP PROCEDURE IF EXISTS find_candles_between_times;

DELIMITER //
CREATE PROCEDURE find_candles_between_times (
   IN instrument_id INT UNSIGNED,
   IN timeframe_id INT UNSIGNED,
   IN start_search_time DATETIME,
   IN end_search_time DATETIME,
   OUT start_candle_id INT UNSIGNED,
   OUT start_candle_time DATETIME,
   OUT end_candle_id INT UNSIGNED,
   OUT end_candle_time DATETIME
)
BEGIN
   SELECT ANY_VALUE(CandleId), MIN(Start)
     INTO start_candle_id, start_candle_time
     FROM ota.Candle c
    WHERE c.InstrumentId = instrument_id
      AND c.timeframeId = timeframe_id
      AND c.Start > start_search_time
   LIMIT 1;

   SELECT ANY_VALUE(CandleId), MAX(Start)
     INTO end_candle_id, end_candle_time
     FROM ota.Candle c
    WHERE c.InstrumentId = instrument_id
      AND c.timeframeId = timeframe_id
      AND c.Start < end_search_time
   LIMIT 1;
END //
DELIMITER ;
