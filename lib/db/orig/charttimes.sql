USE jody;

CREATE TABLE ChartTimes (
	Name varchar(30) NOT NULL,
	HTF varchar(10) NOT NULL,
	HTFMinutes int,
	ITF varchar(10) NOT NULL,
	ITFMinutes int,
	STF varchar(10) NOT NULL,
	STFMinutes int,
	
	PRIMARY KEY (Name) USING BTREE
)
