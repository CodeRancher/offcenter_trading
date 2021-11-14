use ota;

DROP VIEW IF EXISTS ZoneRetracementCount;

CREATE VIEW ZoneRetracementCount AS
   SELECT z.ZoneId AS ZoneId, i.Name AS iName, tf.Name AS tfName, ba.Name AS baName, cc.Name AS ccName, f.Name AS fName, sd.Name AS sdName, COUNT(zr.ZoneId) AS Retrace, FirstCandleStart, LastCandleStart, ZoneOpen, ZoneClose, ZoneHigh, ZoneLow, ZoneWidth, Proximal, ProximalWickArea, Distal, DistalWickArea, ProximalBodyStdDev, ProximalWickStdDev, DistalBodyStdDev, DistalWickStdDev, LegInFirstCandleStart, LegInLastCandleStart, lid.Name AS LegInDirection, LegInOpen, LegInClose, LegInHigh, LegInLow, LegInWidth, LegInBodyArea, LegInWickArea, LegInBodyHigh, LegInBodyLow, LegInVelocity, BaseFirstCandleStart, BaseLastCandleStart, bd.Name AS BaseDirection, BaseOpen, BaseClose, BaseHigh, BaseLow, BaseWidth, BaseBodyArea, BaseWickArea, BaseBodyHigh, BaseBodyLow, BaseVelocity, LegOutFirstCandleStart, LegOutLastCandleStart, lod.Name AS LegOutDirection, LegOutOpen, LegOutClose, LegOutHigh, LegOutLow, LegOutWidth, LegOutBodyArea, LegOutWickArea, LegOutBodyHigh, LegOutBodyLow, LegOutVelocity
     FROM ota.Zone z
     LEFT OUTER JOIN ota.ZoneRetracement zr ON z.ZoneId = zr.ZoneId
     INNER JOIN ota.ZoneStop zs ON z.ZoneId = zs.ZoneId
     INNER JOIN ota.Instrument i ON z.InstrumentId = i.InstrumentId
     INNER JOIN ota.Timeframe tf ON z.timeframeId = tf.timeframeId
     INNER JOIN ota.BidAsk ba ON z.BidAskId = ba.BidAskId
     INNER JOIN ota.ColorChange cc ON z.ColorChangeId = cc.ColorChangeId
     INNER JOIN ota.Formation f ON z.FormationId = f.FormationId
     INNER JOIN ota.SupplyDemand sd ON z.SupplyDemandId = sd.SupplyDemandId
     INNER JOIN ota.Direction lid ON z.LegInDirectionId = lid.DirectionId
     INNER JOIN ota.Direction bd ON z.LegOutDirectionId = bd.DirectionId
     INNER JOIN ota.Direction lod ON z.LegOutDirectionId = lod.DirectionId
     GROUP BY z.ZoneId;