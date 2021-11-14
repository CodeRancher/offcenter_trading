USE ota;

--
-- SELECT * FROM zone_with_entry_times;
-- SELECT * FROM zone_with_entry_times WHERE cross_in_candle_id != zone_entry_candle_id;
-- ********************************************************************************************

DROP VIEW IF EXISTS zone_with_entry_times;

CREATE VIEW zone_with_entry_times AS
   SELECT
      ze.zone_entry_id,
      ze.ZoneId,
      ze.TimeframeId,
      ze.cross_in_candle_id,
      ci.Start AS cross_in_candle_time,
      ze.zone_entry_candle_id,
      e.Start AS zone_entry_candle_time,
      ze.zone_entry_price,
      ze.cross_out_candle_id,
      co.Start AS cross_out_candle_time,
      ze.zone_max_exit_candle_id,
      me.Start AS zone_max_exit_candle_time,
      ze.zone_max_price
     FROM ota.zone_entry ze
     LEFT JOIN ota.Candle ci ON ze.cross_in_candle_id = ci.CandleId
     LEFT JOIN ota.Candle e ON ze.zone_entry_candle_id = e.CandleId
     LEFT JOIN ota.Candle co ON ze.cross_out_candle_id = co.CandleId
     LEFT JOIN ota.Candle me ON ze.zone_max_exit_candle_id = me.CandleId
   ;