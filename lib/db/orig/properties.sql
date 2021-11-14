USE jody;

CREATE TABLE Properties (
	Name varchar(30) NOT NULL,
	StringValue varchar(100),
	IntegerValue int,
	DoubleValue double,
   
	PRIMARY KEY (Name) USING BTREE
)
