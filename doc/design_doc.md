# Trading System Design

## Overarching Design

The overall goal of the system:
* Analyze the historical data for an instrument and find 'points of interest' where price movement will fit predetermined patterns.
* The system will then backtest as the historical and realtime data moves into and out of these 'points of interest'  and where when the current price approaches or enters these bands, a successful trade could occur.

A successful trade is made up of these parts:
* An *Historical Price Pattern*
* *Current Price* interacting with the *Historical Price Pattern*
* *Current Price* moving in an *expected* direction away from the *Historical Price Pattern*
* *Current Price* signalling it is time to leave the trade
  * *Current Price* forming a pattern that *could* signal a reversal of trend
  * *Current Price* interacting with an *Historical Price Pattern* that *could* signal a reversal of trend

### Processing Phases

1. Pull the data from its source into the local store
2. Calculate areas of interest
3. Minitor moving data as it approaches areas of interest
   1. If Trade Analysis shows the aproach is tradable, trade it
   2. Perform backtesting on data
      1. Store the backtest 'element'
      2. Update the backtest 'element'
      3. Calculate results

### Historical vs. Realtime Data

One goal of the system is to make as much of it as possible oblivious to whether the data is historical or realtime. This shouldn't be a problem because the calculations for the 

## General Notes

* All dates and times are UTC during storage and manipulation. A date and time will be converted to a timezone only when displayed or when interacting with a user.

## Applications

---
### Persist Oanda Candle Data

Determine the data that has been already stored in the database, and what data is currently available from the broker. There are two scenarios of what data must now be read.

* Historical Data
  * Start to read historical data from the point of the last data stored.
  * Store that data to the database.
  * Signal the next step in the system that data is ready.
  * If the system has read all available historical data then it needs to move to reading realtime data.
* Realtime Data
  * Monitor for realtime data being pushed from the broker.
  * Store that data to the database.
  * Signal the next step in the system that data is ready.

| Direction | Signal | Data | Description |
| --- | --- | --- | --- |
| out | SignalCurrentCandle | ? | All trading data |

---
### Signal Current Candle

Send a signal that the system is to process the next candle in the data stream. This is a separate service so that it can easily be replaced with a simulator or test.

There are two types of data to process.
* Historical data
  * Determine the last record sent to the system
  * Get the next record
  * Send the next record to the system
* Realtime data
  * Send the next record to the system

| Direction | Signal | Data | Description |
| --- | --- | --- | --- |
| in | SignalCurrentCandle | ? | ? |
| out | ProcessCandlestickHierarchy | CandlestickDataAmqp | ? |
| out | ProcessProprietaryCandlestickHierarchy | CandlestickDataAmqp | ? |

---
### Process Candlestick Hierarchy

Take input of a candlestick and generate all higher timeframes. The goal of this service is to allow downloading of a small amount of data and calculating all other candlestick data plus other related data locally.

The results will be saved to the database, then the rest of the system will be signalled that the data is ready to process.

| Value | Description |
| --- | --- |
| S5 | 5 second candlesticks, minute alignment |
| S10 | 10 second candlesticks, minute alignment |
| S15 | 15 second candlesticks, minute alignment |
| S30 | 30 second candlesticks, minute alignment |
| M1 | 1 minute candlesticks, minute alignment |
| M2 | 2 minute candlesticks, hour alignment |
| M4 | 4 minute candlesticks, hour alignment |
| M5 | 5 minute candlesticks, hour alignment |
| M10 | 10 minute candlesticks, hour alignment |
| M15 | 15 minute candlesticks, hour alignment |
| M30 | 30 minute candlesticks, hour alignment |
| H1 | 1 hour candlesticks, hour alignment |
| H2 | 2 hour candlesticks, day alignment |
| H3 | 3 hour candlesticks, day alignment |
| H4 | 4 hour candlesticks, day alignment |
| H6 | 6 hour candlesticks, day alignment |
| H8 | 8 hour candlesticks, day alignment |
| H12 | 12 hour candlesticks, day alignment |
| D | 1 day candlesticks, day alignment |
| W | 1 week candlesticks, aligned to start of week |
| M | 1 month candlesticks, aligned to first day of the month |

Notes:
| Alignment | Description |
| --- | --- |
| Day Alignment | What hour of the day is considered the start of the day (UTC) |
| Week Alignment | What day (Sun, Mon, Tues, Wed, Thur, Fri, Sat) and hour is considered the start of the week (UTC) |
| Month Alignment | What day (offset from 1st (0=1st, 1=2nd, -1=last day of previous month) and hour is considered the start of the month (UTC) |


| Direction | Signal | Data | Count | Description |
| --- | --- | --- | --- | --- |
| in | ProcessCandlestickHierarchy | ? | One low timeframe candlestick | ? |
| out | SignalCurrentProcessingCandle | ? | One for each high level generated timeframe | ? |

---
### Signal Current Processing Candle

Take the results from the "Process Candlestick Hierarchy" service and pass them on to the rest of the system.

This service needs to handle two modes for the input data.
* Historical data. There may be historical data that has not been processed.
  * The processed data for services past this service may have been deleted. If the algorithms in those services has changed, then the data needs to be recalculated and the easist way to achieve that is to delete the data and rerun this service.
  * Once all the historical data has been processed, this service needs to move into processing realtime data.
* Realtime data
  * As data is processed as it becomes available.

This is a seperate service so that it can be simulated.

Note: Only one of "Signal Current Processing Candle" or this service may be running at a time. If there is no proprietary processing going on, then the "Signal Current Processing Candle" service must be running.

| Direction | Signal | Data | Description |
| --- | --- | --- | --- |
| in | SignalCurrentProcessingCandle | TradingData | All trading data |
| out | ProcessTradingData | ? | ? |

---
### Process Trading Data

Calculate indicators and other trading data related to candlesticks in each timeframe. Looking for patterns that will become historical 'points of interest' where a successful trade could happen in the future.

#### Velocity



| Direction | Signal | Data | Description |
| --- | --- | --- | --- |
| in | ProcessTradingData | TradingData | All trading data |
| out | AnalyzeTradingData | TradingData | All trading data |

---
### Analyze Trading Data

Look at all the 'points of interest' and calculate a numerical determination of how strong a chance of success this 'point of interest' could have.

| Direction | Signal | Data | Description |
| --- | --- | --- | --- |
| in | AnalyzeTradingData | ? | ? |
| out | TradeDecisionManager | ? | ? |

---
### Trade Decision Manager

Take the current price for an instrument and run all the tests against the 'points of interest' that could signal a successful trade.

| Direction | Signal | Data | Description |
| --- | --- | --- | --- |
| in | TradeDecisionManager | ? | ? |
| out | OandaTradeManager | ? | ? |

---
### Oanda Trade Manager
| Direction | Signal | Data | Description |
| --- | --- | --- | --- |
| in | OandaTradeManager | ? | ? |

---
## Messages
| Message | Value |
| --- | --- |
| SignalCurrentCandle | offcenter.trading.signalcurrentcandle.<broker>.<server>.<instrument>.<granularity> |
| ProcessCandlestickHierarchy | offcenter.trading.processcandlestickhierarchy.<broker>.<server>.<instrument>.<granularity> |
| ProcessProprietaryCandlestickHierarchy | offcenter.trading.processproprietarycandlestickhierarchy.<broker>.<server>.<instrument>.<granularity> |
| SignalCurrentProcessingCandle | offcenter.trading.signalcurrentprocessingcandle.<broker>.<server>.<instrument>.<granularity> |
| ProcessTradingData | offcenter.trading.processtradingdata.<broker>.<server>.<instrument>.<granularity> |
| ProcessProprietaryTradingData | offcenter.trading.processproprietarytradingdata.<broker>.<server>.<instrument>.<granularity> |
| AnalyzeTradingData | offcenter.trading.analyzetradingdata.<broker>.<server>.<instrument>.<granularity> |
| AnalyzeProprietaryTradingData | offcenter.trading.analyzeproprietarytradingdata.<broker>.<server>.<instrument>.<granularity> |
| TradeDecisionManager | offcenter.trading.tradedecisionmanager.<broker>.<server>.<instrument>.<granularity> |
| OandaTradeManager | offcenter.trading.oandatrademanager.<broker>.<server>.<instrument>.<granularity> |

## Data Types

### AnalyzeTradingData
| Name | Description |
| --- | --- |
| Current Trading Candle |  |