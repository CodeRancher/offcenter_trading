SELECT
	CandleId,
    @candle_size := AskHigh - AskLow AS CandleSize,
    @body_size := ABS(AskOpen - AskClose) AS BodySize,
    ROUND(@candle_size - @body_size, 5) AS WickSize,
    @boring_exciting := ROUND(@candle_size - (2 * @body_size), 5) AS BorEx,
    @boring_exciting >= 0 AS Boring
	FROM ota.Candle c
    ;
    