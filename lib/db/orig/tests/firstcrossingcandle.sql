use ota;

SET @instrumentName = 'USD/JPY';
SET @timeframe = 'H3';
SET @price = 114.183;
SET @bidAskName = 'Bid';
SET @supplyDemandName = 'Supply';

SELECT 
-- z.ZoneId, i.Name AS Instrument, tf.Name AS Timeframe, ba.Name AS BidAsk, cc.Name AS ColorChange, f.Name AS Formation,
-- sd.Name AS SupplyDemand, z.FirstCandleStart, z.LastCandleStart, z.Proximal, z.Distal
z.InstrumentId, z.TimeframeId, z.FirstCandleStart, z.Proximal, z.Distal, z.BidAskId, z.SupplyDemandId
INTO @iId, @tfId, @zStart, @proximal, @distal, @bidAsk, @supplyDemand
FROM ota.Zone z
  INNER JOIN ota.Instrument i ON z.InstrumentId = i.InstrumentId
  INNER JOIN ota.Timeframe tf ON z.timeframeId = tf.timeframeId
  INNER JOIN ota.BidAsk ba ON z.BidAskId = ba.BidAskId
  INNER JOIN ota.ColorChange cc ON z.ColorChangeId = cc.ColorChangeId
  INNER JOIN ota.Formation f ON z.FormationId = f.FormationId
  INNER JOIN ota.SupplyDemand sd ON z.SupplyDemandId = sd.SupplyDemandId
WHERE z.ZoneId = 17298;

SELECT @iId, @tfId, @zStart, @distal, @bidAsk, @supplyDemand;
CALL stopping_candle(         @iId, @tfId, @zStart, @distal, @bidAsk, @supplyDemand, @stopCandleId,  @stopCandleTime);
CALL start_of_stopping_candle(@iId, @tfId, @zStart, @stopCandleTime, @proximal, @bidAsk, @supplyDemand, @startCandleId, @startCandleTime);

SELECT @iId, @tfId, @zStart, @proximal, @distal, @bidAsk, @supplyDemand, @startCandleId, @startCandleTime, @stopCandleId,  @stopCandleTime;

CALL first_crossing_candle(@iId, @tfId, @zStart, @startCandleTime, @proximal, @bidAsk, @supplyDemand, @firstCrossingId, @firstCrossingTime);
SELECT @instrumentName, @timeframe, @proximal, @bidAskName, @bidAsk, @supplyDemandName, @supplyDemand, @zStart, @startCandleTime, @firstCrossingId, @firstCrossingTime, @distal, @proximal;

CALL last_crossing_candle(@iId, @tfId, @firstCrossingTime, @startCandleTime, @proximal, @bidAsk, @supplyDemand, @lastCrossingId, @lastCrossingTime);
SELECT @instrumentName, @timeframe, @proximal, @bidAskName, @bidAsk, @supplyDemandName, @supplyDemand, @lastCrossingTime, @startCandleTime, @lastCrossingId, @lastCrossingTime, @distal, @proximal;

-- CALL first_crossing_candle(@instrumentName, @timeframe, @reCrossTime, @stopTime, @proximal, @bidAskId, @supplyDemandId, @id, @crossTime);
-- SELECT @instrumentName, @timeframe, @proximal, @bidAskName, @bidAskId, @supplyDemandName, @supplyDemandId, @reCrossTime, @stopTime, @id, @crossTime, @distal, @proximal;
