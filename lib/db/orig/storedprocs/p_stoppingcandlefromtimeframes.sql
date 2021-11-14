USE ota;

DROP PROCEDURE IF EXISTS stopping_candle_from_timeframes;

DELIMITER //
CREATE PROCEDURE stopping_candle_from_timeframes(
   IN instrumentId INT UNSIGNED,
   IN timeframeId INT UNSIGNED,
   IN startTime DATETIME,
   -- IN endTime DATETIME,
   IN distal DECIMAL(9,5),
   IN bidAsk INT UNSIGNED,
   IN supplyDemand INT UNSIGNED,
   OUT stopCandleId INT UNSIGNED,
   OUT stopCandleTime DATETIME,
   OUT stopTimeframeId INT UNSIGNED
)
BEGIN
  DECLARE cursor_InstrumentId INT UNSIGNED;
  DECLARE cursor_TimeframeId INT UNSIGNED;
  DECLARE lookStartTime DATETIME;
  DECLARE lookStopId INT UNSIGNED;
  DECLARE lookStopTime DATETIME;

  DECLARE prevStopCandleId INT UNSIGNED;
  -- SET prevStopCandleId = NULL;
  DECLARE prevStopCandleTime DATETIME;
  -- SET prevStopCandleTime = NULL;
  DECLARE prevStopTimeframeId INT UNSIGNED;
  -- SET prevStopTimeframeId = NULL;

  DECLARE curStopCandleId INT UNSIGNED;
  -- SET prevStopCandleId = NULL;
  DECLARE curStopCandleTime DATETIME;
  -- SET prevStopCandleTime = NULL;
  DECLARE curStopTimeframeId INT UNSIGNED;
  -- SET prevStopTimeframeId = NULL;
  
  -- DECLARE stopCandleId INT UNSIGNED;
  -- DECLARE stopCandleTime DATETIME;
  DECLARE done INT DEFAULT FALSE;
  DECLARE cursor_i CURSOR FOR
      SELECT c.InstrumentId, c.TimeframeId
      FROM CandleInstrumentByParentTimeframe c
      WHERE c.InstrumentId = instrumentId
      ORDER BY c.TimeframeId DESC;
                                 
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
  OPEN cursor_i;
  SET lookStartTime = startTime;
  SET prevStopCandleId = NULL;

  CALL log_variable('stopping_candle_from_timeframes', 'instrumentId', instrumentId);
  CALL log_variable('stopping_candle_from_timeframes', 'timeframeId', timeframeId);
  CALL log_variable('stopping_candle_from_timeframes', 'startTime', startTime);
  CALL log_variable('stopping_candle_from_timeframes', 'distal', distal);
  CALL log_variable('stopping_candle_from_timeframes', 'bidAsk', bidAsk);
  CALL log_variable('stopping_candle_from_timeframes', 'supplyDemand', supplyDemand);
  CALL empty_msg();

  read_loop: LOOP
    FETCH cursor_i INTO cursor_InstrumentId, cursor_TimeframeId;
    CALL log_variable('stopping_candle_from_timeframes', 'cursor_InstrumentId', cursor_InstrumentId);
    CALL log_variable('stopping_candle_from_timeframes', 'cursor_TimeframeId', cursor_TimeframeId);
    CALL empty_msg();
    
    IF done THEN
      LEAVE read_loop;
    END IF;
    
    CALL log_variable('stopping_candle_from_timeframes', 'prevStopCandleId', prevStopCandleId);
    CASE 
      WHEN prevStopCandleId IS NULL THEN CALL stopping_candle(cursor_InstrumentId, cursor_TimeframeId, lookStartTime, distal, bidAsk, supplyDemand, curStopCandleId, curStopCandleTime);
      ELSE CALL stopping_candle_in_range(cursor_InstrumentId, cursor_TimeframeId, lookStartTime, lookStopTime, distal, bidAsk, supplyDemand, curStopCandleId, curStopCandleTime);
    END CASE;
    -- IF prevStopCandleId IS NULL THEN
    --   CALL stopping_candle(cursor_InstrumentId, cursor_TimeframeId, lookStartTime, distal, bidAsk, supplyDemand, curStopCandleId, curStopCandleTime);
    -- else    
    --   CALL stopping_candle_in_range(cursor_InstrumentId, cursor_TimeframeId, lookStartTime, lookStopTime, distal, bidAsk, supplyDemand, curStopCandleId, curStopCandleTime);
    -- END IF;
      -- Get current timeframes stop
      -- CALL stopping_candle_in_range (cursor_InstrumentId, cursor_TimeframeId, lookStartTime, lookStopTime, distal, bidAsk, supplyDemand, curStopCandleId, curStopCandleTime);
    IF curStopCandleId IS NULL THEN
      SET stopCandleId = prevStopCandleId;
      SET stopCandleTime = prevStopCandleTime;
      SET stopTimeframeId = prevStopTimeframeId;
      LEAVE read_loop;
    ELSEIF cursor_TimeframeId = timeframeId THEN
      SET stopCandleId = curStopCandleId;
      SET stopCandleTime = curStopCandleTime;
      SET stopTimeframeId = cursor_TimeframeId;
      LEAVE read_loop;
    ELSE
      CALL candle_after_candle(instrumentId, cursor_TimeframeId, curStopCandleTime, lookStopId, lookStopTime);
      SET lookStartTime = curStopCandleTime;
      SET prevStopCandleId = curStopCandleId;
      SET prevStopCandleTime = curStopCandleTime;
      SET prevStopTimeframeId = cursor_TimeframeId;
    END IF;
  END LOOP;
  CLOSE cursor_i;
END //
DELIMITER ;
