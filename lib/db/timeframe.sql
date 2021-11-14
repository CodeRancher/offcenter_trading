USE ota;

CREATE TABLE Timeframe (
	TimeframeId int unsigned AUTO_INCREMENT PRIMARY KEY,
	Name varchar(10) BINARY NOT NULL,
	ParentTimeframeId int unsigned,
	RefiningTimeframeId int unsigned,
   WidthTime varchar(10) BINARY NOT NULL,
   WidthUnit int unsigned,
   SearchTimeframe int unsigned NOT NULL,
	
	CONSTRAINT CkTimeframe_Name UNIQUE(Name),
	FOREIGN KEY (ParentTimeframeId)
		REFERENCES Timeframe(TimeframeId),
	FOREIGN KEY (RefiningTimeframeId)
		REFERENCES Timeframe(TimeframeId)
);

SELECT ANY_VALUE(InstrumentId), ANY_VALUE(TimeframeId), MIN(Start)
FROM ota.Candle
GROUP BY InstrumentId, TimeframeId;

SELECT *
FROM ota.Timeframe;

USE ota;
UPDATE ota.Timeframe SET RefiningTimeframeId = 14 WHERE Name = 'M1';
UPDATE ota.Timeframe SET RefiningTimeframeId = 13 WHERE Name = 'W1';
UPDATE ota.Timeframe SET RefiningTimeframeId = 9 WHERE Name = 'D1';
UPDATE ota.Timeframe SET RefiningTimeframeId = 9 WHERE Name = 'H8';
UPDATE ota.Timeframe SET RefiningTimeframeId = 9 WHERE Name = 'H6';
UPDATE ota.Timeframe SET RefiningTimeframeId = 9 WHERE Name = 'H4';
UPDATE ota.Timeframe SET RefiningTimeframeId = 6 WHERE Name = 'H3';
UPDATE ota.Timeframe SET RefiningTimeframeId = 6 WHERE Name = 'H2';
UPDATE ota.Timeframe SET RefiningTimeframeId = 6 WHERE Name = 'H1';
UPDATE ota.Timeframe SET RefiningTimeframeId = 3 WHERE Name = 'm30';
UPDATE ota.Timeframe SET RefiningTimeframeId = 3 WHERE Name = 'm15';
UPDATE ota.Timeframe SET RefiningTimeframeId = 3 WHERE Name = 'm10';
UPDATE ota.Timeframe SET RefiningTimeframeId = 1 WHERE Name = 'm5';
UPDATE ota.Timeframe SET RefiningTimeframeId = 1 WHERE Name = 'm2';
UPDATE ota.Timeframe SET RefiningTimeframeId = null WHERE Name = 'm1';

USE ota;
UPDATE ota.Timeframe SET WidthTime = 'MONTH', WidthUnit = 1 WHERE Name = 'M1';
UPDATE ota.Timeframe SET RefiningTimeframeId = 13 WHERE Name = 'W1';
UPDATE ota.Timeframe SET RefiningTimeframeId = 9 WHERE Name = 'D1';
UPDATE ota.Timeframe SET RefiningTimeframeId = 9 WHERE Name = 'H8';
UPDATE ota.Timeframe SET RefiningTimeframeId = 9 WHERE Name = 'H6';
UPDATE ota.Timeframe SET RefiningTimeframeId = 9 WHERE Name = 'H4';
UPDATE ota.Timeframe SET RefiningTimeframeId = 6 WHERE Name = 'H3';
UPDATE ota.Timeframe SET RefiningTimeframeId = 6 WHERE Name = 'H2';
UPDATE ota.Timeframe SET RefiningTimeframeId = 6 WHERE Name = 'H1';
UPDATE ota.Timeframe SET RefiningTimeframeId = 3 WHERE Name = 'm30';
UPDATE ota.Timeframe SET RefiningTimeframeId = 3 WHERE Name = 'm15';
UPDATE ota.Timeframe SET RefiningTimeframeId = 3 WHERE Name = 'm10';
UPDATE ota.Timeframe SET RefiningTimeframeId = 1 WHERE Name = 'm5';
UPDATE ota.Timeframe SET RefiningTimeframeId = 1 WHERE Name = 'm2';
UPDATE ota.Timeframe SET RefiningTimeframeId = null WHERE Name = 'm1';

UPDATE ota.Timeframe SET SearchTimeframe = 9 WHERE TimeframeId = 1;
UPDATE ota.Timeframe SET SearchTimeframe = 9 WHERE TimeframeId = 2;
UPDATE ota.Timeframe SET SearchTimeframe = 9 WHERE TimeframeId = 3;
UPDATE ota.Timeframe SET SearchTimeframe = 9 WHERE TimeframeId = 4;
UPDATE ota.Timeframe SET SearchTimeframe = 9 WHERE TimeframeId = 5;
UPDATE ota.Timeframe SET SearchTimeframe = 9 WHERE TimeframeId = 6;
UPDATE ota.Timeframe SET SearchTimeframe = 9 WHERE TimeframeId = 7;
UPDATE ota.Timeframe SET SearchTimeframe = 9 WHERE TimeframeId = 8;
UPDATE ota.Timeframe SET SearchTimeframe = 13 WHERE TimeframeId = 9;
UPDATE ota.Timeframe SET SearchTimeframe = 13 WHERE TimeframeId = 10;
UPDATE ota.Timeframe SET SearchTimeframe = 13 WHERE TimeframeId = 11;
UPDATE ota.Timeframe SET SearchTimeframe = 13 WHERE TimeframeId = 12;
UPDATE ota.Timeframe SET SearchTimeframe = 15 WHERE TimeframeId = 13;
UPDATE ota.Timeframe SET SearchTimeframe = 14 WHERE TimeframeId = 14;
UPDATE ota.Timeframe SET SearchTimeframe = 15 WHERE TimeframeId = 15;