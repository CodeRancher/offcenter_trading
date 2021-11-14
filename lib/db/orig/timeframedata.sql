USE ota;

INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	VALUES('m1', NULL, NULL);
   
INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	SELECT 'm2', tf.TimeframeId, tf2.TimeframeId
	FROM ota.Timeframe tf
   INNER JOIN ota.Timeframe tf2 ON tf2.Name='m1'
   WHERE tf.Name='m1';
   
INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	SELECT 'm5', tf.TimeframeId, tf2.TimeframeId
	FROM ota.Timeframe tf
   INNER JOIN ota.Timeframe tf2 ON tf2.Name='m1'
   WHERE tf.Name='m2';
   
INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	SELECT 'm10', tf.TimeframeId, tf2.TimeframeId
	FROM ota.Timeframe tf
   INNER JOIN ota.Timeframe tf2 ON tf2.Name='m5'
   WHERE tf.Name='m5';
   
INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	SELECT 'm15', tf.TimeframeId, tf2.TimeframeId
	FROM ota.Timeframe tf
   INNER JOIN ota.Timeframe tf2 ON tf2.Name='m5'
   WHERE tf.Name='m10';
   
INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	SELECT 'm30', tf.TimeframeId, tf2.TimeframeId
	FROM ota.Timeframe tf
   INNER JOIN ota.Timeframe tf2 ON tf2.Name='m5'
   WHERE tf.Name='m15';
   
INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	SELECT 'H1', tf.TimeframeId, tf2.TimeframeId
	FROM ota.Timeframe tf
   INNER JOIN ota.Timeframe tf2 ON tf2.Name='m30'
   WHERE tf.Name='m30';
   
INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	SELECT 'H2', tf.TimeframeId, tf2.TimeframeId
	FROM ota.Timeframe tf
   INNER JOIN ota.Timeframe tf2 ON tf2.Name='m30'
   WHERE tf.Name='H1';
   
INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	SELECT 'H3', tf.TimeframeId, tf2.TimeframeId
	FROM ota.Timeframe tf
   INNER JOIN ota.Timeframe tf2 ON tf2.Name='m30'
   WHERE tf.Name='H2';
   
INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	SELECT 'H4', tf.TimeframeId, tf2.TimeframeId
	FROM ota.Timeframe tf
   INNER JOIN ota.Timeframe tf2 ON tf2.Name='H3'
   WHERE tf.Name='H3';
   
INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	SELECT 'H6', tf.TimeframeId, tf2.TimeframeId
	FROM ota.Timeframe tf
   INNER JOIN ota.Timeframe tf2 ON tf2.Name='H3'
   WHERE tf.Name='H4';
   
INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	SELECT 'H8', tf.TimeframeId, tf2.TimeframeId
	FROM ota.Timeframe tf
   INNER JOIN ota.Timeframe tf2 ON tf2.Name='H3'
   WHERE tf.Name='H6';
   
INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	SELECT 'D1', tf.TimeframeId, tf2.TimeframeId
	FROM ota.Timeframe tf
   INNER JOIN ota.Timeframe tf2 ON tf2.Name='H3'
   WHERE tf.Name='H8';
   
INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	SELECT 'W1', tf.TimeframeId, tf2.TimeframeId
	FROM ota.Timeframe tf
   INNER JOIN ota.Timeframe tf2 ON tf2.Name='D1'
   WHERE tf.Name='D1';
   
INSERT INTO Timeframe (Name, ParentTimeframeId, RefiningTimeframeId) 
	SELECT 'M1', tf.TimeframeId, tf2.TimeframeId
	FROM ota.Timeframe tf
   INNER JOIN ota.Timeframe tf2 ON tf2.Name='W1'
   WHERE tf.Name='W1';
