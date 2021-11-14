USE ota;

CREATE TABLE Formation (
   FormationId int unsigned PRIMARY KEY,
   Name varchar(20) BINARY NOT NULL,

   CONSTRAINT CkFormation_Name UNIQUE(Name)
);

INSERT INTO Formation (FormationId, Name) values (1, 'RBR');
INSERT INTO Formation (FormationId, Name) values (2, 'RBD');
INSERT INTO Formation (FormationId, Name) values (3, 'DBR');
INSERT INTO Formation (FormationId, Name) values (4, 'DBD');

