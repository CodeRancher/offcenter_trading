use ota;

DROP PROCEDURE IF EXISTS first_zone_without_stops;

DELIMITER //
CREATE PROCEDURE first_zone_without_stops (
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
   LEFT JOIN ota.ZoneStop zs ON z.ZoneId = zs.ZoneId
   WHERE z.InstrumentId = instrument_id
   AND z.TimeframeId = timeframe_id
   AND ISNULL(zs.ZoneStopId)
   ORDER BY z.FirstCandleStart
   LIMIT 1
   ;
END //
DELIMITER ;
