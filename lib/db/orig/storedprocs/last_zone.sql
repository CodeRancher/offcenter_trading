use ota;

DROP PROCEDURE IF EXISTS last_zone;

DELIMITER //
CREATE PROCEDURE last_zone (
   IN instrument_id INT UNSIGNED,
   IN timeframe_id INT UNSIGNED,
   OUT zone_id INT UNSIGNED,
   OUT bid_ask_id INT UNSIGNED,
   OUT color_change_id INT UNSIGNED,
   OUT formation_id INT UNSIGNED,
   OUT supply_demand_id INT UNSIGNED,
   OUT first_candle_start DATETIME,
   OUT last_candle_start DATETIME
)
BEGIN
   SELECT z.ZoneId, z.BidAskId, z.ColorChangeId, z.FormationId,
      z.SupplyDemandId, z.FirstCandleStart, z.LastCandleStart
   INTO zone_id, bid_ask_id, color_change_id, formation_id,
      supply_demand_id, first_candle_start, last_candle_start
   FROM ota.Zone z
   WHERE z.InstrumentId = instrument_id
   AND z.TimeframeId = timeframe_id
   ORDER BY z.FirstCandleStart DESC
   LIMIT 1
   ;
END //
DELIMITER ;
