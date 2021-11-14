use ota;

DROP PROCEDURE IF EXISTS recross_proximal_or_distal;

DELIMITER //
CREATE PROCEDURE recross_proximal_or_distal (
   IN instrument_id INT UNSIGNED,
   IN timeframe_id INT UNSIGNED,
   IN start_time DATETIME,
   IN end_time DATETIME,
   IN proximal DECIMAL(9,5),
   IN distal DECIMAL(9,5),
   IN bid_ask INT UNSIGNED,
   IN supply_demand INT UNSIGNED,
   OUT cross_id INT UNSIGNED,
   OUT cross_time DATETIME,
   OUT cross_price DECIMAL(9,5),
   OUT is_stop_candle BOOLEAN
)
BEGIN
   CASE bid_ask
      WHEN 1 THEN BEGIN
         CASE supply_demand
            WHEN 1 THEN BEGIN
               CASE ISNULL(end_time)
                  WHEN 1 THEN BEGIN
                     SELECT c.CandleId, c.Start, c.BidHigh, c.BidHigh > distal
                        INTO cross_id, cross_time, cross_price, is_stop_candle
                        FROM ota.Candle c
                        WHERE c.InstrumentId = instrument_id
                           AND c.timeframeId = timeframe_id
                           AND c.Start >= start_time
                           AND (c.BidHigh > distal OR c.BidHigh < proximal)
                        ORDER BY c.Start
                        LIMIT 1;
                  END;
                  WHEN 0 THEN BEGIN
                     SELECT c.CandleId, c.Start, c.BidHigh, c.BidHigh > distal
                        INTO cross_id, cross_time, cross_price, is_stop_candle
                        FROM ota.Candle c
                        WHERE c.InstrumentId = instrument_id
                           AND c.timeframeId = timeframe_id
                           AND c.Start >= start_time
                           AND c.Start < end_time
                           AND (c.BidHigh > distal OR c.BidHigh < proximal)
                        ORDER BY c.Start
                        LIMIT 1;
                  END;
               END CASE;
            END;
            WHEN 2 THEN BEGIN
               CASE ISNULL(end_time)
                  WHEN 1 THEN BEGIN
                     SELECT c.CandleId, c.Start, c.BidLow, c.BidLow < distal
                        INTO cross_id, cross_time, cross_price, is_stop_candle
                        FROM ota.Candle c
                        WHERE c.InstrumentId = instrument_id
                           AND c.timeframeId = timeframe_id
                           AND c.Start >= start_time
                           AND (c.BidLow < distal OR c.BidLow > proximal)
                        ORDER BY c.Start
                        LIMIT 1;
                  END;
                  WHEN 0 THEN BEGIN
                     SELECT c.CandleId, c.Start, c.BidLow, c.BidLow < distal
                        INTO cross_id, cross_time, cross_price, is_stop_candle
                        FROM ota.Candle c
                        WHERE c.InstrumentId = instrument_id
                           AND c.timeframeId = timeframe_id
                           AND c.Start >= start_time
                           AND c.Start < end_time
                           AND (c.BidLow < distal OR c.BidLow > proximal)
                        ORDER BY c.Start
                        LIMIT 1;
                  END;
               END CASE;
            END;
         END CASE;
      END;
      WHEN 2 THEN BEGIN
         CASE supply_demand
            WHEN 1 THEN BEGIN
               CASE ISNULL(end_time)
                  WHEN 1 THEN BEGIN
                     SELECT c.CandleId, c.Start, c.AskHigh, c.AskHigh > distal
                        INTO cross_id, cross_time, cross_price, is_stop_candle
                        FROM ota.Candle c
                        WHERE c.InstrumentId = instrument_id
                           AND c.timeframeId = timeframe_id
                           AND c.Start >= start_time
                           AND (c.AskHigh > distal OR c.AskHigh < proximal)
                        ORDER BY c.Start
                        LIMIT 1;
                  END;
                  WHEN 0 THEN BEGIN
                     SELECT c.CandleId, c.Start, c.AskHigh, c.AskHigh > distal
                        INTO cross_id, cross_time, cross_price, is_stop_candle
                        FROM ota.Candle c
                        WHERE c.InstrumentId = instrument_id
                           AND c.timeframeId = timeframe_id
                           AND c.Start >= start_time
                           AND c.Start < end_time
                           AND (c.AskHigh > distal OR c.AskHigh < proximal)
                        ORDER BY c.Start
                        LIMIT 1;
                  END;
               END CASE;
            END;
            WHEN 2 THEN BEGIN
               CASE ISNULL(end_time)
                  WHEN 1 THEN BEGIN
                     SELECT c.CandleId, c.Start, c.AskLow, c.AskLow < distal
                        INTO cross_id, cross_time, cross_price, is_stop_candle
                        FROM ota.Candle c
                        WHERE c.InstrumentId = instrument_id
                           AND c.timeframeId = timeframe_id
                           AND c.Start >= start_time
                           AND (c.AskLow < distal OR c.AskLow > proximal)
                        ORDER BY c.Start
                        LIMIT 1;
                  END;
                  WHEN 0 THEN BEGIN
                     SELECT c.CandleId, c.Start, c.AskLow, c.AskLow < distal
                        INTO cross_id, cross_time, cross_price, is_stop_candle
                        FROM ota.Candle c
                        WHERE c.InstrumentId = instrument_id
                           AND c.timeframeId = timeframe_id
                           AND c.Start >= start_time
                           AND c.Start <= end_time
                           AND (c.AskLow < distal OR c.AskLow > proximal)
                        ORDER BY c.Start
                        LIMIT 1;
                  END;
               END CASE;
            END;
         END CASE;
      END;
   END CASE;
END //
DELIMITER ;
