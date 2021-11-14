SELECT ZoneId
INTO @zoneId
FROM ota.Zone
WHERE proximal = 114.183
  AND distal = 114.774;

SELECT z.ZoneId, i.Name AS Instrument, tf.Name AS Timeframe, ba.Name AS BidAsk, cc.Name AS ColorChange, f.Name AS Formation,
       sd.Name AS SupplyDemand, z.FirstCandleStart, z.LastCandleStart, z.Proximal, z.Distal
FROM ota.Zone z
  INNER JOIN ota.Instrument i ON z.InstrumentId = i.InstrumentId
  INNER JOIN ota.Timeframe tf ON z.TimeframeId = tf.TimeframeId
  INNER JOIN ota.BidAsk ba ON z.BidAskId = ba.BidAskId
  INNER JOIN ota.ColorChange cc ON z.ColorChangeId = cc.ColorChangeId
  INNER JOIN ota.Formation f ON z.FormationId = f.FormationId
  INNER JOIN ota.SupplyDemand sd ON z.SupplyDemandId = sd.SupplyDemandId
WHERE z.ZoneId = @zoneId;


SELECT zs.ZoneStopId, zs.ZoneId, zs.TimeframeId, c1.Start, c2.Start
FROM ota.Zonestop zs
INNER JOIN ota.Candle c1 ON zs.FirstCandleId = c1.CandleId
INNER JOIN ota.Candle c2 ON zs.LastCandleId = c2.CandleId
WHERE zs.ZoneId = @zoneId;


SELECT zr.ZoneRetracementId, zr.TimeframeId, c1.Start, c2.Start
FROM ota.ZoneRetracement zr
INNER JOIN ota.Candle c1 ON zr.FirstCrossingCandleId = c1.CandleId
INNER JOIN ota.Candle c2 ON zr.LastCrossingCandleId = c2.CandleId
WHERE zr.ZoneId = @zoneId;

