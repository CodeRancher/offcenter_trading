use ota;

CREATE VIEW vBoringExciting AS
   SELECT
      CandleId,
      ROUND(AskHigh - AskLow - (2 * ABS(AskOpen - AskClose)), 5) >= 0 AS Boring
   FROM ota.Candle c
   ;