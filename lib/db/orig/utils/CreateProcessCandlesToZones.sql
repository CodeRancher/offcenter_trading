SELECT 
   CONCAT('processCandlesToZones.processCandleData(', c.CandleId, 'L, ', 
      c.InstrumentId, 'L, "', i.Name, '", ', c.TimeframeId, 'L, "', tf.Name, '", ',
      'new BigDecimal(', c.AskOpen, '), ', 'new BigDecimal(', c.AskClose, '), ', 
      'new BigDecimal(', c.AskHigh, '), ', 'new BigDecimal(', c.AskLow, '), ',
      'new BigDecimal(', c.BidOpen, '), ', 'new BigDecimal(', c.BidClose, '), ', 
      'new BigDecimal(', c.BidHigh, '), ', 'new BigDecimal(', c.BidLow, '), ZonedDateTime.parse("',
      DATE_FORMAT(c.Start, '%Y-%m-%dT%H:%m:%s'), '+04:00"));')
FROM ota.Candle c
INNER JOIN ota.Instrument i ON c.InstrumentId=i.InstrumentId
INNER JOIN ota.Timeframe tf ON c.TimeframeId=tf.TimeframeId
WHERE i.Name='USD/JPY'
  AND tf.Name='H3'
  AND c.Start>='2016-01-01 00:00:00'
  AND c.Start<='2016-02-01 00:00:00';