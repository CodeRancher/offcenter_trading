/**
 * Copyright 2021 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an  BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   ProcessInstrumentDataThread.cpp
 * @author Scott Brauer
 * @date   09-14-2021
 */

#include <chrono>

#include "easylogging++.h"

#include "oanda/v20/instrument/InstrumentDefinitions.hpp"
#include "oanda/v20/endpoint/Pricing.hpp"
#include "offcenter/trading/common/Logging.hpp"

#include "offcenter/trading/oandapersistenceclient/ProcessInstrumentDataThread.hpp"

namespace offcenter {
namespace trading {
namespace oandapersistenceclient {

ProcessInstrumentDataThread::ProcessInstrumentDataThread(
		const std::string& broker,
		const std::string& brokerSource,
		const std::string& instrument,
		const std::string& granularity,
		const std::string& userAccount,
		const int recordCountToRead,
		offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints& persistenceEndpoints,
		oanda::v20::endpoint::OandaEndpoints::Ptr oandaEndpoints
	):
		m_broker(broker),
		m_brokerSource(brokerSource),
		m_instrument(instrument),
		m_granularity(granularity),
		m_userAccount(userAccount),
		m_recordCountToRead(recordCountToRead),
		m_loggerID(offcenter::trading::common::logging::loggerID(broker, brokerSource, instrument, granularity)),
		m_lastBidClose(),
		m_lastAskClose(),
		m_persistenceEndpoints(persistenceEndpoints),
		m_oandaEndpoints(oandaEndpoints)
{
	el::Loggers::reconfigureLogger(m_loggerID, el::ConfigurationType::ToFile, "true");
	el::Loggers::reconfigureLogger(m_loggerID, el::ConfigurationType::ToStandardOutput, "false");
	el::Loggers::reconfigureLogger(m_loggerID, el::ConfigurationType::Format, "%datetime:%thread [%level] %msg");
	el::Loggers::reconfigureLogger(m_loggerID, el::ConfigurationType::Filename, "./ProcessInstrument." + m_loggerID + ".log");

	CLOG(INFO, m_loggerID.c_str()) << "-------------------------------------------------------------------------------------------------";
	CLOG(INFO, m_loggerID.c_str()) << "Creating ProcessInstrumentDataThread: "
			<< "broker(" << m_broker << ") "
			<< "brokerSource(" << m_brokerSource << ") "
			<< "instrument(" << m_instrument << ") "
			<< "granularity(" << m_granularity << ") "
			<< "recordCountToRead(" << m_recordCountToRead << ") "
			<< "loggerID(" << m_loggerID << ")";

	m_candlestickDataSeries = m_persistenceEndpoints.candlestickDataSeriesIDRead(m_brokerSource, m_broker, m_instrument, m_granularity);
	CLOG(INFO, m_loggerID.c_str()) << "Download Instrument Data (" << m_loggerID << ") DateSeriesID(" << m_candlestickDataSeries.candlestick_data_series_id << ")";

	m_candlestickDataCreate.broker = m_broker;
	m_candlestickDataCreate.broker_source = m_brokerSource;
	m_candlestickDataCreate.instrument = m_instrument;
	m_candlestickDataCreate.granularity = m_granularity;

	m_candlesParameters.accountID = m_userAccount;
	m_candlesParameters.instrument = instrument;
	m_candlesParameters.count = std::to_string(m_recordCountToRead);
	m_candlesParameters.includeFirst = "False";
	m_candlesParameters.acceptDateTimeFormat = oanda::v20::primitives::AcceptDatetimeFormat::RFC3339;
	m_candlesParameters.price = "BA";
	m_candlesParameters.granularity = m_granularity;
}

ProcessInstrumentDataThread::~ProcessInstrumentDataThread()
{
	// TODO Auto-generated destructor stub
}

void ProcessInstrumentDataThread::task()
{
	offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord firstLastRecord;
	getFirstLastRecord(firstLastRecord);
	FirstRecordToRead firstRecordToRead = getFirstRecordToRead(firstLastRecord);

	m_lastBidClose = firstLastRecord.last_record_bid_close;
	m_lastAskClose = firstLastRecord.last_record_ask_close;

	m_candlesParameters.from = offcenter::common::UTCDateTimeToISO8601(firstRecordToRead.first);
	m_candlesParameters.includeFirst = firstRecordToRead.second ? "True" : "False";

	try {
		// Synchronously retrieve the candle values
//		CLOG(DEBUG, m_loggerID.c_str()) << "Requesting Pricing Candles: "
//				<< "acceptDateTimeFormat(" << m_candlesParameters.acceptDateTimeFormat.value() << ") "
//				<< "accountID(" << m_candlesParameters.accountID.value() << ") "
//				<< "instrument(" << m_candlesParameters.instrument.value() << ") "
//				<< "price(" << m_candlesParameters.price.value() << ") "
//				<< "granularity(" << m_candlesParameters.granularity.value() << ") "
//				<< "count(" << m_candlesParameters.count.value() << ") "
//				<< "from(" << m_candlesParameters.from.value() << ") "
//				<< "to(" << m_candlesParameters.to.value() << ") "
//				<< "smooth(" << m_candlesParameters.smooth.value() << ") "
//				<< "includeFirst(" << m_candlesParameters.includeFirst.value() << ") "
//				<< "dailyAlignment(" << m_candlesParameters.dailyAlignment.value() << ") "
//				<< "alignmentTimezone(" << m_candlesParameters.alignmentTimezone.value() << ") "
//				<< "weeklyAlignment(" << m_candlesParameters.weeklyAlignment.value() << ") "
//				<< "units(" << m_candlesParameters.units.value() << ")";

		m_oandaEndpoints->pricing.candles(m_candlesRequest, m_candlesParameters)->sync(
			[	&candlestickDataCreate=m_candlestickDataCreate,
			 	&persistenceEndpoints=m_persistenceEndpoints,
			 	&oandaSource=m_brokerSource,
			 	&candlestickDataSeries=m_candlestickDataSeries,
			 	&lastBidClose=m_lastBidClose,
			 	&lastAskClose=m_lastAskClose,
			 	&loggerID=m_loggerID
			](endpoint::pricing::candles::Response candles) -> void {
				std::string granularity;
				to_string(candles.granularity, granularity);

//				CLOG(DEBUG, loggerID.c_str())
//						<< "requestID(" << candles.requestID << ") "
//						<< "instrument(" << candles.instrument << ") "
//						<< "granularity(" << granularity << ")";

//				for (oanda::v20::instrument::Candlestick candlestick : candles.candles) {
//					CLOG(DEBUG, loggerID.c_str())
//							<< "time(" << candlestick.time << ") "
//							<< "bid.o(" << candlestick.bid.o << ") "
//							<< "bid.h(" << candlestick.bid.h << ") "
//							<< "bid.l(" << candlestick.bid.l << ") "
//							<< "bid.c(" << candlestick.bid.c << ") "
//							<< "ask.o(" << candlestick.ask.o << ") "
//							<< "ask.h(" << candlestick.ask.h << ") "
//							<< "ask.l(" << candlestick.ask.l << ") "
//							<< "ask.c(" << candlestick.ask.c << ") "
//							<< "mid.o(" << candlestick.mid.o << ") "
//							<< "mid.h(" << candlestick.mid.h << ") "
//							<< "mid.l(" << candlestick.mid.l << ") "
//							<< "mid.c(" << candlestick.mid.c << ") "
//							<< "volume(" << candlestick.volume << ") "
//							<< "complete(" << ((candlestick.complete==oanda::v20::common::BoolType::True) ? "True" : "False") << ")";
//				}

				for (oanda::v20::instrument::Candlestick candle : candles.candles) {
					offcenter::trading::datatypes::CandlestickData candlestickData;
					candlestickData.candlestick_data_id = 0;
					candlestickData.candlestick_data_series_id = candlestickDataSeries.candlestick_data_series_id;
					candlestickData.start_time = offcenter::common::make_UTCDateTimeFromISO8601(candle.time);
					candlestickData.bid_open = candle.bid.o;
					candlestickData.bid_high = candle.bid.h;
					candlestickData.bid_low = candle.bid.l;
					candlestickData.bid_close = candle.bid.c;
					candlestickData.bid_gap_open = lastBidClose.empty() ? candlestickData.bid_open : lastBidClose;
					candlestickData.ask_open = candle.ask.o;
					candlestickData.ask_high = candle.ask.h;
					candlestickData.ask_low = candle.ask.l;
					candlestickData.ask_close = candle.ask.c;
					candlestickData.ask_gap_open = lastAskClose.empty() ? candlestickData.ask_open : lastAskClose;
					candlestickData.volume = candle.volume;
					candlestickDataCreate.candlestick_data.push_back(candlestickData);

					lastBidClose = candle.bid.c;
					lastAskClose = candle.ask.c;
					//lastCandleStartTime = candlestickData.start_time;
				}

				CLOG(DEBUG, loggerID.c_str()) << "Persisting candlestick data. "
						<< "broker(" << candlestickDataCreate.broker << ") "
						<< "broker_source (" << candlestickDataCreate.broker_source << ") "
						<< "instrument (" << candlestickDataCreate.instrument << ") "
						<< "granularity (" << candlestickDataCreate.granularity << ") "
						<< "from (" << offcenter::common::UTCDateTimeToISO8601(candlestickDataCreate.candlestick_data[0].start_time) << ") "
						<< "to (" << offcenter::common::UTCDateTimeToISO8601(candlestickDataCreate.candlestick_data[candlestickDataCreate.candlestick_data.size() - 1].start_time) << ") "
						<< "count (" << candlestickDataCreate.candlestick_data.size() << ")";
				persistenceEndpoints.candlestickDataCreate(oandaSource, candlestickDataCreate);
			}
		);
		m_candlestickDataCreate.candlestick_data.clear();
	} catch(const std::exception& e) {
		CLOG(ERROR, m_loggerID.c_str()) << "Error retrieving candlestick records. "
				<< "broker(" << m_candlestickDataCreate.broker << ") "
				<< "broker_source (" << m_candlestickDataCreate.broker_source << ") "
				<< "instrument (" << m_candlestickDataCreate.instrument << ") "
				<< "granularity (" << m_candlestickDataCreate.granularity << ") "
				<< "from (" << m_candlesParameters.from.value() << ") "
				<< "count (" << m_candlesParameters.count.value() << "): "
				<< e.what();
		std::cerr << "Error retrieving candlestick records. "
				<< "broker(" << m_candlestickDataCreate.broker << ") "
				<< "broker_source (" << m_candlestickDataCreate.broker_source << ") "
				<< "instrument (" << m_candlestickDataCreate.instrument << ") "
				<< "granularity (" << m_candlestickDataCreate.granularity << ") "
				<< "from (" << m_candlesParameters.from.value() << ") "
				<< "count (" << m_candlesParameters.count.value() << "): "
				<< e.what()
				<< std::endl;
		throw;
	}
}

/*
 * Executed when the thread has been stopped externally.
 */
void ProcessInstrumentDataThread::stopped()
{
	CLOG(INFO, m_loggerID.c_str()) << "Stopped processing: "
			<< "broker(" << m_broker << ") "
			<< "brokerSource(" << m_brokerSource << ") "
			<< "instrument(" << m_instrument << ") "
			<< "granularity(" << m_granularity << ") "
			<< "recordCountToRead(" << m_recordCountToRead << ") "
			<< "loggerID(" << m_loggerID << ")";
}

offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord ProcessInstrumentDataThread::getFirstLastRecord(
		offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord& firstLastRecord)
{
	firstLastRecord = m_persistenceEndpoints.candlestickDataSeriesFirstLast(m_brokerSource, m_candlestickDataSeries.candlestick_data_series_id, m_loggerID);
	CLOG(INFO, m_loggerID.c_str()) << "DB->First Last Record: "
			<< "candlestick_data_series_id(" << firstLastRecord.candlestick_data_series_id << ") "
			<< "first_record_time(" << offcenter::common::UTCDateTimeToISO8601(firstLastRecord.first_record_time) << ") "
			<< "first_record_id(" << firstLastRecord.first_record_id << ") "
			<< "last_record_time(" << offcenter::common::UTCDateTimeToISO8601(firstLastRecord.last_record_time) << ") "
			<< "last_record_id(" << firstLastRecord.last_record_id << ") "
			<< "last_record_bid_close(" << firstLastRecord.last_record_bid_close << ") "
			<< "last_record_ask_close(" << firstLastRecord.last_record_ask_close << ") ";
	return firstLastRecord;
}

ProcessInstrumentDataThread::FirstRecordToRead ProcessInstrumentDataThread::getFirstRecordToRead(
        const offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord &firstLastRecord)
{
	static const std::string startDateTime {"1971-01-01T00:00:00.000000000Z"};

	if (firstLastRecord.first_record_id == 0) {
		CLOG(INFO, m_loggerID.c_str()) << "First record not defined. Retrieving from start of data: " << startDateTime;
		return std::make_pair(offcenter::common::make_UTCDateTimeFromISO8601(startDateTime), true);
	} else {
		if (firstLastRecord.last_record_id == 0) {
			CLOG(ERROR, m_loggerID.c_str()) << "First record is not zero but Last record is. Error condition: " << offcenter::common::UTCDateTimeToISO8601(firstLastRecord.first_record_time);
			return std::make_pair(firstLastRecord.first_record_time, false);
		} else {
			return std::make_pair(firstLastRecord.last_record_time, false);
		}
	}
}

} /* namespace oandapersistenceclient */
} /* namespace trading */
} /* namespace offcenter */
