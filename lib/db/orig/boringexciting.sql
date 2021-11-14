USE ota;

CREATE TABLE BoringExciting (
   BoringExcitingId int unsigned PRIMARY KEY,
   Name varchar(20) BINARY NOT NULL,

   CONSTRAINT CkBoringExciting_Name UNIQUE(Name)
);

INSERT INTO BoringExciting (BoringExcitingId, Name) values (1, 'Boring');
INSERT INTO BoringExciting (BoringExcitingId, Name) values (2, 'Exciting');
INSERT INTO BoringExciting (BoringExcitingId, Name) values (3, 'Indeterminate');
