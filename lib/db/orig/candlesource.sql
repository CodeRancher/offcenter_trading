USE ota;

CREATE TABLE CandleSource (
   CandleSourceId int AUTO_INCREMENT PRIMARY KEY,
   Name varchar(15) BINARY NOT NULL,
   
   CONSTRAINT CkInstrument_Name UNIQUE(Name)
)

INSERT INTO CandleSource (Name) values ('Downloaded');
INSERT INTO CandleSource (Name) values ('Calculated');

