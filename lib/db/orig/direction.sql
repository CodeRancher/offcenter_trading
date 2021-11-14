USE ota;

CREATE TABLE Direction (
   DirectionId int unsigned PRIMARY KEY,
   Name varchar(20) BINARY NOT NULL,

   CONSTRAINT CkDirection_Name UNIQUE(Name)
);

INSERT INTO Direction (DirectionId, Name) values (1, 'Up');
INSERT INTO Direction (DirectionId, Name) values (2, 'Down');
INSERT INTO Direction (DirectionId, Name) values (3, 'Neutral');
INSERT INTO Direction (DirectionId, Name) values (4, 'Indeterminate');

