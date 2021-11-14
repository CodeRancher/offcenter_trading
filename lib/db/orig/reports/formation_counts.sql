USE ota;

DROP VIEW IF EXISTS formation_colorchange;

CREATE VIEW formation_colorchange AS
   SELECT 
      CONCAT(f.Name, IF(cc.ColorChangeId=1,'-CC','')) AS Name,
      f.Name AS Formation,
      cc.Name AS ColorChange,
      f.FormationId,
      cc.ColorChangeId
   FROM ota.Formation f
   CROSS JOIN ota.ColorChange cc
   ;
   
