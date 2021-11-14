USE ota;

CREATE TABLE InstrumentType (
   InstrumentTypeId int unsigned PRIMARY KEY,
   Name varchar(30) BINARY NOT NULL,

   CONSTRAINT CkInstrument_Name UNIQUE(Name)
)
