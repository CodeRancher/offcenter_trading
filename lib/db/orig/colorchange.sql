USE ota;

CREATE TABLE ColorChange (
   ColorChangeId int unsigned PRIMARY KEY,
   Name varchar(20) BINARY NOT NULL,

   CONSTRAINT CkColorChange_Name UNIQUE(Name)
);

INSERT INTO ColorChange (ColorChangeId, Name) values (1, 'Color Change');
INSERT INTO ColorChange (ColorChangeId, Name) values (2, 'No Color Change');

