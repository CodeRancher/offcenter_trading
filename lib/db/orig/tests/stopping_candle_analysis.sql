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


SELECT MAX(c.Start) AS Start
INTO @stopStartCandleTime
 FROM ota.Candle c
 -- INNER JOIN ota.Instrument i ON c.InstrumentId = i.InstrumentId
 -- INNER JOIN ota.Timeframe tf ON c.TimeframeId = tf.TimeframeId
 WHERE c.InstrumentId = @iId
   AND c.TimeframeId = @tfId
   AND c.Start <= @startCandleTime
   AND
      CASE
         -- Bid, Supply
         WHEN (@bidAsk=1 AND @supplyDemand=1) THEN c.BidOpen < @proximal
         -- Bid, Demand
         WHEN (@bidAsk=1 AND @supplyDemand=2) THEN c.BidOpen > @proximal
         -- Ask, Supply
         WHEN (@bidAsk=2 AND @supplyDemand=1) THEN c.AskOpen < @proximal
         -- Ask, Demand
         WHEN (@bidAsk=2 AND @supplyDemand=2) THEN c.AskOpen > @proximal
      END;
            
 SELECT MIN(c.Start) Start
 INTO @lastStart
 FROM ota.Candle c
 WHERE c.InstrumentId = @iId
   AND c.timeframeId = @tfId
   AND Start > '2016-12-07 07:00:00'
   AND Start < @stopStartCandleTime
   AND
      CASE
         -- Bid, Supply
         WHEN (@bidAsk=1 AND @supplyDemand=1) THEN c.BidHigh > @proximal
         -- Bid, Demand
         WHEN (@bidAsk=1 AND @supplyDemand=2) THEN c.BidLow < @proximal
         -- Ask, Supply
         WHEN (@bidAsk=2 AND @supplyDemand=1) THEN c.AskHigh > @proximal
         -- Ask, Demand
         WHEN (@bidAsk=2 AND @supplyDemand=2) THEN c.AskLow < @proximal
      END;

SELECT @iId, @tfId, @zStart, @proximal, @distal, @bidAsk, @supplyDemand, @startCandleId, @startCandleTime, @stopCandleId,  @stopCandleTime, @stopStartCandleTime, @lastStart;

SELECT MIN(c.Start) Start, c.CandleId
INTO @retraceLastCandleStart, @retraceLastCandleId
FROM ota.Candle c
WHERE c.InstrumentId = @iId
AND c.timeframeId = @tfId
AND Start >= @lastStart
AND Start < @stopStartCandleTime
AND
   CASE
      -- Bid, Supply
      WHEN (@bidAsk=1 AND @supplyDemand=1) THEN c.BidHigh < @proximal
      -- Bid, Demand
      WHEN (@bidAsk=1 AND @supplyDemand=2) THEN c.BidLow > @proximal
      -- Ask, Supply
      WHEN (@bidAsk=2 AND @supplyDemand=1) THEN c.AskHigh < @proximal
      -- Ask, Demand
      WHEN (@bidAsk=2 AND @supplyDemand=2) THEN c.AskLow > @proximal
   END;

SELECT @iId, @tfId, @zStart, @proximal, @distal, @bidAsk, @supplyDemand, @startCandleId, @startCandleTime, @stopCandleId,  @stopCandleTime, @stopStartCandleTime, @lastStart, @retraceLastCandleStart, @retraceLastCandleId;
