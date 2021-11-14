use ota;
DROP PROCEDURE IF EXISTS CombinedBoringExciting;
DELIMITER //
CREATE PROCEDURE CombinedBoringExciting(
   IN instid INT UNSIGNED,
   IN tfid INT UNSIGNED,
   IN firstdate DATETIME,
   IN lastdate DATETIME,
   IN boring_exciting_percent DOUBLE
)
   BEGIN
      DECLARE cCandleId INT UNSIGNED;
      DECLARE cInstrumentId INT UNSIGNED;
      DECLARE cTimeFrameId INT UNSIGNED;
      
      DECLARE cAskOpen decimal(9,5);
      DECLARE cAskClose decimal(9,5);
      DECLARE cAskHigh decimal(9,5);
      DECLARE cAskLow decimal(9,5);
      DECLARE cAskCandleSize decimal(9,5);
      DECLARE cAskWickSize decimal(9,5);
      DECLARE cAskBodySize decimal(9,5);
      DECLARE cAskTopWickSize decimal(9,5);
      DECLARE cAskBottomWickSize decimal(9,5);
      DECLARE cAskBodyDirection char(1);
      DECLARE cAskType char(1);

      DECLARE cBidOpen decimal(9,5);
      DECLARE cBidClose decimal(9,5);
      DECLARE cBidHigh decimal(9,5);
      DECLARE cBidLow decimal(9,5);
      DECLARE cBidCandleSize decimal(9,5);
      DECLARE cBidWickSize decimal(9,5);
      DECLARE cBidBodySize decimal(9,5);
      DECLARE cBidTopWickSize decimal(9,5);
      DECLARE cBidBottomWickSize decimal(9,5);
      DECLARE cBidBodyDirection char(1);
      DECLARE cBidType char(1);
   
      DECLARE cStart DATETIME;
      
      DECLARE cBoring INT; -- -1 Boring 0 Undefined 1 Exciting
      -- SELECT cBoring = 0;
      
      DECLARE done INT DEFAULT FALSE;
      DECLARE cursor_i CURSOR FOR
         SELECT CandleId, InstrumentId, TimeFrameId, AskOpen, AskClose, AskHigh, AskLow, BidOpen, BidClose, BidHigh, BidLow, Start
         FROM ota.Candle c
         WHERE c.InstrumentId=instid
            AND c.TimeFrameId=tfid
            AND c.Start>=firstdate
            AND c.Start<=lastdate
         ORDER BY Start;
         
	   DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;
         
      DROP TEMPORARY TABLE IF EXISTS CombinedCandle;
	   CREATE TEMPORARY TABLE CombinedCandle (
  	      CandleId int AUTO_INCREMENT PRIMARY KEY,
	      InstrumentId int unsigned NOT NULL,
	      TimeFrameId int unsigned NOT NULL,

	      AskOpen decimal(9,5) NOT NULL,
	      AskClose decimal(9,5) NOT NULL,
	      AskHigh decimal(9,5) NOT NULL,
	      AskLow decimal(9,5) NOT NULL,

	      BidOpen decimal(9,5) NOT NULL,
	      BidClose decimal(9,5) NOT NULL,
	      BidHigh decimal(9,5) NOT NULL,
	      BidLow decimal(9,5) NOT NULL,
	   
	      Start DATETIME NOT NULL,
         CandleCount int NOT NULL
      );
     
      OPEN cursor_i;
      read_loop: LOOP
         FETCH cursor_i INTO cCandleId, cInstrumentId, cTimeFrameId, cAskOpen, cAskClose, cAskHigh, cAskLow, cBidOpen, cBidClose, cBidHigh, cBidLow, cStart;
		   IF done THEN
            LEAVE read_loop;
         END IF;
         
         -- Calc here
         CALL CandleInfo(cAskOpen, cAskClose, cAskHigh, cAskLow, @cAskCandleSize, @cAskWickSize, @cAskBodySize, @cAskTopWickSize, @cAskBottomWickSize, @cAskBodyDirection);
         CALL BoringExciting(@cAskCandleSize, @cAskBodySize, 50, @cAskType);
         IF (@pAskBodyDirection = @cAskBodyDirection) AND (@pAskType = @cAskType) THEN BEGIN
               -- Combine previous candle
            END;
         ELSE BEGIN
            INSERT INTO CombinedCandle (cCandleId, cInstrumentId, cTimeFrameIdcandle, AskOpen, AskClose, AskHigh, AskLow, BidOpen, BidClose, BidHigh, BidLow, Start, CandleCount)
            VALUES (cCandleId, cInstrumentId, cTimeFrameId, cAskOpen, cAskClose, cAskHigh, cAskLow, cBidOpen, cBidClose, cBidHigh, cBidLow, cStart, 1);
            END;
         END IF;
         
         CALL CandleInfo(cBidOpen, cBidClose, cBidHigh, cBidLow, @cBidCandleSize, @cBidWickSize, @cBidBodySize, @cBidTopWickSize, @cBidBottomWickSize, @cBidBodyDirection);
         CALL BoringExciting(@cBidCandleSize, @cBidBodySize, 50, @cBidType);
         IF (@pBidBodyDirection = @cBidBodyDirection) AND (@pBidType = @cBidType) THEN BEGIN
               -- Combine previous candle
            END;
         ELSE BEGIN
               -- Add new candle
            END;
         END IF;

         SELECT body_size = cAskOpen - cAskClose;
         IF body_size > 0 THEN
			   SELECT body_direction = 1;
		   ELSE
            SELECT body_direction = -1;
		   END IF;
         SELECT body_direction = 
         SELECT size_percent = (cAskHigh - cAskLow - body_size) / body_size;
         IF size_percent <= boring_exciting_percent THEN
			-- Boring
		 ELSE
			-- Exciting
         END IF;
         SELECT cCandleId, cStart;
         INSERT INTO CombinedCandle (CandleId, InstrumentId, TimeFrameId, AskOpen, AskClose, AskHigh, AskLow, BidOpen, BidClose, BidHigh, BidLow, Start, CandleCount)
         VALUES (cCandleId, cInstrumentId, cTimeFrameId, cAskOpen, cAskClose, cAskHigh, cAskLow, cBidOpen, cBidClose, cBidHigh, cBidLow, cStart, 1);
      END LOOP;
      CLOSE cursor_i;
      
      SELECT CandleId, InstrumentId, TimeFrameId, AskOpen, AskClose, AskHigh, AskLow, BidOpen, BidClose, BidHigh, BidLow, Start, CandleCount FROM CombinedCandle;
      DROP TEMPORARY TABLE IF EXISTS CombinedCandle;
   END //
DELIMITER ;


CALL Test(613, 15, '2001-11-28 06:15:00', '2001-11-28 06:30:00');
-- CALL `ota`.`Test`(<{IN instid INT UNSIGNED}>, <{IN tfid INT UNSIGNED}>, <{IN firstdate DATETIME}>, <{IN lastdate DATETIME}>);

-- DROP PROCEDURE Test;
