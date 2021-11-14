USE ota;

DROP VIEW IF EXISTS zone_stop_with_times;

CREATE VIEW zone_stop_with_times AS
   SELECT
      zs.ZoneStopId,
      zs.ZoneId,
      z.InstrumentId,
      zs.TimeframeId,
      z.FirstCandleStart AS ZoneStart,
      z.LastCandleStart AS ZoneEnd,
      zs.FirstCandleId,
      cf.Start AS ZoneStopStart,
      zs.LastCandleId,
      cl.Start AS ZoneStopEnd
     FROM ota.ZoneStop zs
     INNER JOIN ota.Zone z ON zs.ZoneId = z.ZoneId
     INNER JOIN ota.Candle cf ON zs.FirstCandleId = cf.CandleId
     INNER JOIN ota.Candle cl ON zs.LastCandleId = cl.CandleId
   ;