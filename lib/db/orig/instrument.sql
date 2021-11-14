USE ota;

CREATE TABLE Instrument (
   InstrumentId int unsigned AUTO_INCREMENT PRIMARY KEY,
   
	Name varchar(30) BINARY NOT NULL,
	BaseUnitSize int unsigned NOT NULL,
	ContractCurrency varchar(20) NOT NULL,
	ContractMultiplier int unsigned NOT NULL,
	InstrumentTypeId int unsigned NOT NULL,
	PointSize decimal(10,6) NOT NULL,
	PricePrecision int unsigned NOT NULL,

   CONSTRAINT CkInstrument_Name UNIQUE(Name),
   FOREIGN KEY (InstrumentTypeId)
      REFERENCES InstrumentType(InstrumentTypeId)

)
