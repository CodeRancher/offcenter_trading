use ota;
DROP PROCEDURE IF EXISTS CandleInfo;
DELIMITER //
CREATE PROCEDURE CandleInfo(
   IN cOpen decimal(9,5),
   IN cClose decimal(9,5),
   IN cHigh decimal(9,5),
   IN cLow decimal(9,5),
   OUT candleSize decimal(9,5),
   OUT wickSize decimal(9,5),
   OUT bodySize decimal(9,5),
   OUT topWickSize decimal(9,5),
   OUT bottomWickSize decimal(9,5),
   OUT bodyDirection char(1)
)
   BEGIN
      -- DECLARE candleSize decimal(9,5);
      -- DECLARE wickSize decimal(9,5);
      -- DECLARE bodySize decimal(9,5);
      -- DECLARE topWickSize decimal(9,5);
      -- DECLARE bottomWickSize decimal(9,5);
      -- DECLARE bodyDirection char(1);

      DECLARE bodyTop decimal(9,5);
      DECLARE bodyBottom decimal(9,5);
      
      IF cOpen > cClose THEN BEGIN
		   SET bodyTop = cOpen;
		   SET bodyBottom = cClose;
         SET bodyDirection = 'D';
	      END;
	  ELSE BEGIN
		   SET bodyTop = cClose;
		   SET bodyBottom = cOpen;
         SET bodyDirection = 'U';
         END;
	  END IF;
      
      SET candleSize = cHigh - cLow;
      SET bodySize = bodyTop - bodyBottom;
      SET wickSize = candleSize - bodySize;
      SET topWickSize = cHigh - bodyTop;
      SET bottomWickSize = bodyBottom - cLow;

   END //
DELIMITER ;


CALL CandleInfo(1.1, 1.2, 1.3, 1.0, @candleSize, @wickSize, @bodySize, @topWickSize, @bottomWickSize, @bodyDirection);
SELECT @candleSize, @wickSize, @bodySize, @topWickSize, @bottomWickSize, @bodyDirection;
CALL CandleInfo(1.2, 1.1, 1.3, 1.0, @candleSize, @wickSize, @bodySize, @topWickSize, @bottomWickSize, @bodyDirection);
SELECT @candleSize, @wickSize, @bodySize, @topWickSize, @bottomWickSize, @bodyDirection;
