use ota;
DROP PROCEDURE IF EXISTS BoringExciting;
DELIMITER //
CREATE PROCEDURE BoringExciting(
   IN candleSize decimal(9,5),
   IN bodySize decimal(9,5),
   IN boringPercent int,
   OUT candleType char(1)
)
   BEGIN
      DECLARE actBoringPercent decimal(6,5);
      DECLARE rangePercent decimal(9,5);
      
      SET actBoringPercent = boringPercent / 100.0;
      SET rangePercent = candleSize * actBoringPercent;
      SELECT rangePercent;
      
      IF bodySize <= rangePercent THEN
         SET candleType = 'B';
      ELSE
         SET candleType = 'E';
      END IF;
   END //
DELIMITER ;


CALL BoringExciting(100.0, 100.0, 50, @candleType);
SELECT @candleType;

CALL BoringExciting(100.0, 0.0, 50, @candleType);
SELECT @candleType;

CALL BoringExciting(100.0, 50.1, 50, @candleType);
SELECT @candleType;

CALL BoringExciting(100.0, 50.0, 50, @candleType);
SELECT @candleType;

CALL BoringExciting(100.0, 49.9, 50, @candleType);
SELECT @candleType;
