USE ota;

CREATE TABLE Tick (
   TickId int unsigned AUTO_INCREMENT PRIMARY KEY,
   InstrumentId int unsigned NOT NULL,

   Ask decimal(9,5) NOT NULL,
   Bid decimal(9,5) NOT NULL,
   Start DATETIME NOT NULL,

   FOREIGN KEY (InstrumentId)
      REFERENCES Instrument(InstrumentId)
      ON DELETE CASCADE
)
