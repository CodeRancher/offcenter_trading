SET @iName = 'USD/JPY';
SET @tfName = 'H3';
SET @baName = 'Bid';

SELECT 
   Retrace, 
   COUNT(CASE WHEN fName = 'DBD' THEN Retrace END) AS DBD, 
   COUNT(CASE WHEN fName = 'DBR' THEN Retrace END) AS DBR, 
   COUNT(CASE WHEN fName = 'RBD' THEN Retrace END) AS RBD, 
   COUNT(CASE WHEN fName = 'RBR' THEN Retrace END) AS RBR,
   COUNT(*) AS TOTAL
FROM ota.ZoneRetracementCount
WHERE iName = @iName
  AND tfName = @tfName
  AND baName = @baName
GROUP BY Retrace WITH ROLLUP ;