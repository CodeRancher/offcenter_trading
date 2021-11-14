USE ota;

CREATE TABLE MonitoredInstrument (
   MonitoredInstrumentId int AUTO_INCREMENT PRIMARY KEY,
   InstrumentId int unsigned NOT NULL,
   TimeFrameId int unsigned NOT NULL,
   CandleSourceId int unsigned NOT NULL,
   

   FOREIGN KEY (InstrumentId)
      REFERENCES Instrument(InstrumentId)
   FOREIGN KEY (TimeFrameId)
      REFERENCES TimeFrame(TimeFrameId)
   FOREIGN KEY (CandleSourceId)
      REFERENCES CandleSource(CandleSourceId)
)
