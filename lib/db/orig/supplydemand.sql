USE ota;

CREATE TABLE SupplyDemand (
   SupplyDemandId int unsigned PRIMARY KEY,
   Name varchar(20) BINARY NOT NULL,

   CONSTRAINT CkSupplyDemand_Name UNIQUE(Name)
);

INSERT INTO SupplyDemand (SupplyDemandId, Name) values (1, 'Supply');
INSERT INTO SupplyDemand (SupplyDemandId, Name) values (2, 'Demand');

