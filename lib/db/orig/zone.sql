USE ota;

DROP TABLE IF EXISTS Zone;

CREATE TABLE Zone (
   -- Record ID
   ZoneId int unsigned AUTO_INCREMENT PRIMARY KEY,
   InstrumentId int unsigned NOT NULL,
   TimeframeId int unsigned NOT NULL,
   
   -- Zone Foreign Records
   BidAskId int unsigned NOT NULL,
   ColorChangeId int unsigned NOT NULL,
   FormationId int unsigned NOT NULL,
   SupplyDemandId int unsigned NOT NULL,
   
   -- Zone info
   FirstCandleStart DATETIME NOT NULL,
   LastCandleStart DATETIME NOT NULL,
   
   ZoneOpen decimal(9,5) NOT NULL,
   ZoneClose decimal(9,5) NOT NULL,
   ZoneHigh decimal(9,5) NOT NULL,
   ZoneLow decimal(9,5) NOT NULL,
   ZoneWidth int unsigned NOT NULL,
   
   Proximal decimal(9,5) NOT NULL,
   ProximalWickArea decimal(9,5) NOT NULL,
   Distal decimal(9,5) NOT NULL,
   DistalWickArea decimal(9,5) NOT NULL,

   ProximalBodyStdDev decimal(9,5) NOT NULL,
   ProximalWickStdDev decimal(9,5) NOT NULL,
   DistalBodyStdDev decimal(9,5) NOT NULL,
   DistalWickStdDev decimal(9,5) NOT NULL,

   -- Leg In
   LegInFirstCandleStart DATETIME NOT NULL,
   LegInLastCandleStart DATETIME NOT NULL,
   
   LegInDirectionId int unsigned NOT NULL,
   
   LegInOpen decimal(9,5) NOT NULL,
   LegInClose decimal(9,5) NOT NULL,
   LegInHigh decimal(9,5) NOT NULL,
   LegInLow decimal(9,5) NOT NULL,
   LegInWidth int unsigned NOT NULL,

   LegInBodyArea decimal(13,5) NOT NULL,
   LegInWickArea decimal(13,5) NOT NULL,

   LegInBodyHigh decimal(9,5) NOT NULL,
   LegInBodyLow decimal(9,5) NOT NULL,

   LegInVelocity decimal(11,5) NOT NULL,

   -- Base
   BaseFirstCandleStart DATETIME,
   BaseLastCandleStart DATETIME,
   
   BaseDirectionId int unsigned,
   
   BaseOpen decimal(9,5),
   BaseClose decimal(9,5),
   BaseHigh decimal(9,5),
   BaseLow decimal(9,5),
   BaseWidth int unsigned,

   BaseBodyArea decimal(13,5),
   BaseWickArea decimal(13,5),

   BaseBodyHigh decimal(9,5),
   BaseBodyLow decimal(9,5),

   BaseVelocity decimal(11,5),

   -- Leg Out
   LegOutFirstCandleStart DATETIME NOT NULL,
   LegOutLastCandleStart DATETIME NOT NULL,
   
   LegOutDirectionId int unsigned NOT NULL,
   
   LegOutOpen decimal(9,5) NOT NULL,
   LegOutClose decimal(9,5) NOT NULL,
   LegOutHigh decimal(9,5) NOT NULL,
   LegOutLow decimal(9,5) NOT NULL,
   LegOutWidth int unsigned NOT NULL,

   LegOutBodyArea decimal(13,5) NOT NULL,
   LegOutWickArea decimal(13,5) NOT NULL,

   LegOutBodyHigh decimal(9,5) NOT NULL,
   LegOutBodyLow decimal(9,5) NOT NULL,

   LegOutVelocity decimal(11,5) NOT NULL,

   -- LegInRangeSize decimal(11,5) NOT NULL, = LegInHigh - LegInLow
   -- LegInBodySize decimal(11,5) NOT NULL, = ABS(LegInOpen - LegInClose)
   -- LegInBodyPercent decimal(9,5) NOT NULL, = LegInBodySize / LegInRangeSize
   -- LegInWickSize decimal(9,5) NOT NULL, = LegInRangeSize - LegInBodySize
   -- LegInProximalWick decimal(9,5) NOT NULL,
   -- LegInDistalWick decimal(9,5) NOT NULL,
   -- LegInProximalWickArea decimal(13,5) NOT NULL,
   -- LegInDistalWickArea decimal(13,5) NOT NULL,
   -- LegInBodyAreaPercent decimal(9,5) NOT NULL, = LegInBodyArea / LegInRangeArea
   -- LegInWickAreaPercent decimal(9,5) NOT NULL, = LegInWickArea / LegInRangeArea
   -- LegInProximalWickAreaPercent decimal(9,5) NOT NULL, = LegInProximalWickArea / LegInRangeArea
   -- LegInDistalWickAreaPercent decimal(9,5) NOT NULL, = LegInDistalWickArea / LegInRangeArea
   -- LegInStart DATETIME NOT NULL,

   FOREIGN KEY (InstrumentId)
      REFERENCES Instrument(InstrumentId),
   FOREIGN KEY (TimeframeId)
      REFERENCES Timeframe(TimeframeId),
   FOREIGN KEY (FormationId)
      REFERENCES Formation(FormationId),
   FOREIGN KEY (SupplyDemandId)
      REFERENCES SupplyDemand(SupplyDemandId),
   FOREIGN KEY (ColorChangeId)
      REFERENCES ColorChange(ColorChangeId),
   FOREIGN KEY (LegInDirectionId)
      REFERENCES Direction(DirectionId),
   FOREIGN KEY (BaseDirectionId)
      REFERENCES Direction(DirectionId),
   FOREIGN KEY (LegOutDirectionId)
      REFERENCES Direction(DirectionId),
   INDEX(InstrumentId, TimeframeId, FirstCandleStart),
   INDEX(InstrumentId, TimeframeId, LastCandleStart)
)
