USE ota;

DROP VIEW IF EXISTS zone_with_stop_times;

CREATE VIEW zone_with_stop_times AS
   SELECT
      z.ZoneId,
      zs.ZoneStopId,
      z.InstrumentId,
      z.TimeframeId,
      z.FirstCandleStart AS ZoneStart,
      z.LastCandleStart AS ZoneEnd,
      zs.FirstCandleId,
      cf.Start AS ZoneStopStart,
      zs.LastCandleId,
      cl.Start AS ZoneStopEnd
     FROM ota.Zone z
     LEFT JOIN ota.ZoneStop zs ON z.ZoneId = zs.ZoneId
     LEFT JOIN ota.Candle cf ON zs.FirstCandleId = cf.CandleId
     LEFT JOIN ota.Candle cl ON zs.LastCandleId = cl.CandleId
   ;