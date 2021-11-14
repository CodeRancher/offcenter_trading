use ota;

DROP PROCEDURE IF EXISTS max_price_between_times;

DELIMITER //
CREATE PROCEDURE max_price_between_times (
   IN instrument_id INT UNSIGNED,
   IN timeframe_id INT UNSIGNED,
   IN first_time DATETIME,
   IN last_time DATETIME,
   IN bid_ask INT UNSIGNED,
   IN supply_demand INT UNSIGNED,
   OUT max_id INT UNSIGNED,
   OUT max_time DATETIME,
   OUT max_price DECIMAL(9,5)
)
BEGIN
   CASE bid_ask
      WHEN 1 THEN BEGIN
         CASE supply_demand
            WHEN 1 THEN BEGIN
               SELECT MAX(c.BidHigh)
                 INTO max_price
                 FROM ota.Candle c
                WHERE c.InstrumentId = instrument_id
                  AND c.TimeframeId = timeframe_id
                  AND c.Start >= first_time
                  AND c.Start <= last_time;
               SELECT c.CandleId, c.Start
                 INTO max_id, max_time
                 FROM ota.Candle c
                WHERE c.InstrumentId = instrument_id
                  AND c.TimeframeId = timeframe_id
                  AND c.Start >= first_time
                  AND c.Start <= last_time
                  AND c.BidHigh = max_price
                LIMIT 1;
            END;
            WHEN 2 THEN BEGIN
               SELECT MIN(c.BidLow)
                 INTO max_price
                 FROM ota.Candle c
                WHERE c.InstrumentId = instrument_id
                  AND c.TimeframeId = timeframe_id
                  AND c.Start >= first_time
                  AND c.Start <= last_time;
               SELECT c.CandleId, c.Start
                 INTO max_id, max_time
                 FROM ota.Candle c
                WHERE c.InstrumentId = instrument_id
                  AND c.TimeframeId = timeframe_id
                  AND c.Start >= first_time
                  AND c.Start <= last_time
                  AND c.BidLow = max_price
                LIMIT 1;
            END;
         END CASE;
      END;
      WHEN 2 THEN BEGIN
         CASE supply_demand
            WHEN 1 THEN BEGIN
               SELECT MAX(c.AskHigh)
                 INTO max_price
                 FROM ota.Candle c
                WHERE c.InstrumentId = instrument_id
                  AND c.TimeframeId = timeframe_id
                  AND c.Start >= first_time
                  AND c.Start <= last_time;
               SELECT c.CandleId, c.Start
                 INTO max_id, max_time
                 FROM ota.Candle c
                WHERE c.InstrumentId = instrument_id
                  AND c.TimeframeId = timeframe_id
                  AND c.Start >= first_time
                  AND c.Start <= last_time
                  AND c.AskHigh = max_price
                LIMIT 1;
            END;
            WHEN 2 THEN BEGIN
               SELECT MIN(c.AskLow)
                 INTO max_price
                 FROM ota.Candle c
                WHERE c.InstrumentId = instrument_id
                  AND c.TimeframeId = timeframe_id
                  AND c.Start >= first_time
                  AND c.Start <= last_time;
               SELECT c.CandleId, c.Start
                 INTO max_id, max_time
                 FROM ota.Candle c
                WHERE c.InstrumentId = instrument_id
                  AND c.TimeframeId = timeframe_id
                  AND c.Start >= first_time
                  AND c.Start <= last_time
                  AND c.AskLow = max_price
                LIMIT 1;
            END;
         END CASE;
      END;
   END CASE;
END //
DELIMITER ;
