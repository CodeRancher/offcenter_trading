USE ota;

SET @instrumentName = 'USD/JPY';
SET @timeframe = 'H3';
SET @price = 114.183;
SET @bidAskName = 'Bid';
SET @supplyDemandName = 'Supply';

SELECT c.Start, c.BidHigh, c.BidOpen, c.InstrumentId, c.TimeFrameId INTO @zoneDate, @distal, @proximal, @instrumentId, @timeframeId
FROM ota.Candle c
INNER JOIN ota.Instrument i ON c.InstrumentId = i.InstrumentId
INNER JOIN ota.Timeframe tf ON c.TimeframeId = tf.TimeframeId
WHERE i.Name=@instrumentName
AND tf.Name=@timeframe
AND c.BidHigh=@price;
-- SELECT @openDate;

SELECT ba.BidAskId INTO @bidAskId
FROM ota.BidAsk ba
WHERE ba.Name = @bidAskName;

SELECT sd.SupplyDemandId INTO @supplyDemandId
FROM ota.SupplyDemand sd
WHERE sd.Name = @supplyDemandName;

CALL stopping_candle(         @instrumentId, @timeframeId, @zoneDate, @distal,   @bidAskId, @supplyDemandId, @stopId,  @stopTime);
CALL start_of_stopping_candle(@instrumentId, @timeframeId, @stopTime, @proximal, @bidAskId, @supplyDemandId, @startId, @startTime);
SELECT @instrumentName, @instrumentId, @timeframe, @timeframeId, @zoneDate, @distal, @proximal, @bidAskId, @supplyDemandId, @startId, @startTime, @stopId, @stopTime;

-- CALL stopping_candles(@instrumentName, @timeframe, @zoneDate, @proximal, @distal, @bidAskId, @supplyDemandId, @startId, @startTime, @stopId,  @stopTime);
-- SELECT @instrumentName, @timeframe, @zoneDate, @distal, @proximal, @bidAskId, @supplyDemandId, @startId, @startTime, @stopId, @stopTime;
