USE ota;

CREATE TABLE BidAsk (
   BidAskId int unsigned PRIMARY KEY,
   Name varchar(20) BINARY NOT NULL,

   CONSTRAINT CkBidAsk_Name UNIQUE(Name)
);

INSERT INTO BidAsk (BidAskId, Name) values (1, 'Bid');
INSERT INTO BidAsk (BidAskId, Name) values (2, 'Ask');

