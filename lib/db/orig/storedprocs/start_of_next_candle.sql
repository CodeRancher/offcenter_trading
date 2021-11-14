use ota;

-- 
-- CALL start_of_this_or_next_candle(613, 13, '1993-10-02 17:00:00', @candle_id, @candle_time);
-- SELECT @candle_id, @candle_time
-- 
-- **********************************************************************************************

DROP PROCEDURE IF EXISTS start_of_next_candle;

DELIMITER //
CREATE PROCEDURE start_of_next_candle (
   IN instrument_id INT UNSIGNED,
   IN timeframe_id INT UNSIGNED,
   IN this_time DATETIME,
   OUT candle_id INT UNSIGNED,
   OUT candle_time DATETIME
)
BEGIN
   SELECT c.CandleId, c.Start
     INTO candle_id, candle_time
     FROM ota.Candle c
    WHERE c.InstrumentId = instrument_id
      AND c.TimeframeId = timeframe_id
      AND c.Start > this_time
    ORDER BY c.Start
    LIMIT 1
;
END //
DELIMITER ;
