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
 * @file   OandaPersistenceManagerApp.cpp
 * @author Scott Brauer
 * @date   05-18-2021
 */

#include <string>
#include <iostream>
#include <regex>
#include <exception>

#include <nlohmann/json.hpp>
#include "easylogging++.h"

#include "offcenter/trading/oandapersistencemanager/OandaPersistenceManagerApp.hpp"
#include "offcenter/trading/datatypes/oanda/InstrumentJson.hpp"
#include "offcenter/trading/datatypes/InstrumentJson.hpp"
#include "offcenter/trading/datatypes/CandlestickDataSeriesJson.hpp"
#include "offcenter/trading/datatypes/CandlestickDataJson.hpp"
#include "offcenter/trading/datatypes/InstrumentCountJson.hpp"
#include "offcenter/trading/datatypes/TableInfoJson.hpp"
#include "offcenter/trading/datatypes/LookupTables.hpp"

namespace offcenter {
namespace trading {
namespace oandapersistencemanager {

OandaPersistenceManagerApp::OandaPersistenceManagerApp():
	IRestServerApp(),
	m_oandaTradingDB()
{

}

OandaPersistenceManagerApp::~OandaPersistenceManagerApp()
{
	// TODO Auto-generated destructor stub
}

void OandaPersistenceManagerApp::onInitProgramOptions(program_options::ProgramOptionsManager &optionsManager)
{
	m_mysqlConfig = optionsManager.add<offcenter::soci::MySQLProgramOptions>();
	m_oandaPersistenceManagerConfig = optionsManager.add<offcenter::trading::oandapersistencemanager::OandaPersistenceManagerProgramOptions>();
	m_restServerConfig = optionsManager.add<offcenter::common::restserver::RestServerProgramOptions>();
}

void OandaPersistenceManagerApp::onSetUp()
{
	// Initialize DB
	std::cout << "Initializing Oanda trading database" << std::endl;
	m_oandaTradingDB.initialize(*m_mysqlConfig);
	std::cout << "Initializing trading database" << std::endl;
	m_tradingDB.initialize(*m_mysqlConfig);
}

void OandaPersistenceManagerApp::onInitMethodHandlers(restserver::AutoMethodHandler &methodHandler)
{
	std::cout << "Initializing HTTP handling" << std::endl;

	/**
	 * Create oanda instrument
	 */
	methodHandler.addHandler(web::http::methods::PUT,
		"/oanda/([^/]*)/oandainstrument",
		"Oanda Instrument Create",
		[&oandaTradingDB=m_oandaTradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			offcenter::trading::datatypes::oanda::InstrumentWithIDs instrument;
			try {
				std::string bodyAsString = message.extract_string().get();
				nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
				instrument = bodyAsJson.get<offcenter::trading::datatypes::oanda::InstrumentWithIDs>();
				LOG(INFO) << "Creating Oanda Instrument: source(" << source << ") name(" << instrument.name << ")";
				oandaTradingDB.instrumentCreate(instrument);

				offcenter::trading::datatypes::common::CreateRecord createRecord(
						"Successfully added " + std::to_string(instrument.instrument_id) + ", " + instrument.name);
				nlohmann::json json = createRecord;
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				offcenter::trading::datatypes::common::CreateRecord createRecord(
						"Failed to add " + std::to_string(instrument.instrument_id) + ", " + instrument.name, false, e.what());
				nlohmann::json json = createRecord;
				LOG(ERROR) << "Unable to create Oanda Instrument: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			}
		}
	);

	/**
	 * Read oanda instrument based on name or id
	 */
	methodHandler.addHandler(web::http::methods::GET,
		"/oanda/([^/]*)/oandainstrument/([^/]*)",
		"Oanda Instrument Read",
		[&oandaTradingDB=m_oandaTradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			std::string name = smatch[2];
			LOG(INFO) << "Reading Instrument: source(" << source << ") name(" << name << ")";
			offcenter::trading::datatypes::oanda::Instrument instrument;
			try {
				try {
					oandaTradingDB.instrumentRead(instrument, std::stoul(name));
				} catch(std::exception& e) {
					oandaTradingDB.instrumentRead(instrument, name);
				}

				nlohmann::json json = instrument;
				LOG(DEBUG) << "Oanda Instrument Read" << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				offcenter::trading::datatypes::common::ReadRecordError error(
						"Reading Instrument: source(" + source + ") name(" + name + ")",
						e.what());
				nlohmann::json json = instrument;
				LOG(ERROR) << "Unable to read instrument: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			}
		}
	);

	/**
	 * Delete oanda instrument based on name or id
	 */
	methodHandler.addHandler(web::http::methods::DEL,
		"/oanda/([^/]*)/oandainstrument/([^/]*)",
		"Oanda Instrument Delete",
		[&oandaTradingDB=m_oandaTradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			std::string name = smatch[2];
			LOG(INFO) << "Deleting Instrument: source(" << source << ") name(" << name << ")";
			try {
				unsigned instrument_id;
				bool useInstrumentID = false;
				try {
					instrument_id = std::stoul(name);
					useInstrumentID = true;
				} catch(std::exception& e) {
					useInstrumentID = false;
				}

				if (useInstrumentID) {
					LOG(DEBUG) << "Delete Instrument based on instrument_id: " << instrument_id;
					oandaTradingDB.instrumentDelete(instrument_id);
				} else {
					LOG(DEBUG) << "Delete Instrument based on name: " << name;
					oandaTradingDB.instrumentDelete(name);
				}

				offcenter::trading::datatypes::common::DeleteRecord deleteRecord;
				deleteRecord.name = "Delete record (" + name + ")";
				deleteRecord.success = true;
				nlohmann::json json = deleteRecord;
				LOG(DEBUG) << "Oanda Instrument Delete" << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				LOG(ERROR) << "Unable to delete record (" + name + ") - " + e.what();
				message.reply(
						web::http::status_codes::InternalError,
						"Unable to delete record (" + name + ") - " + e.what()).wait();
			}
		}
	);

	/**
	 * Create instrument
	 */
	methodHandler.addHandler(web::http::methods::PUT,
		"/oanda/([^/]*)/instrument",
		"Instrument Create",
		[&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			offcenter::trading::datatypes::Instrument instrument;
			try {
				std::string bodyAsString = message.extract_string().get();
				nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
				instrument = bodyAsJson.get<offcenter::trading::datatypes::Instrument>();
				LOG(INFO) << "Creating Instrument: source(" << source << ") name(" << instrument.name << ")";
				tradingDB.instrumentCreate(instrument);

				offcenter::trading::datatypes::common::CreateRecord createRecord(
						"Successfully added " + std::to_string(instrument.instrument_id) + ", " + instrument.name);
				nlohmann::json json = createRecord;
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				offcenter::trading::datatypes::common::CreateRecord createRecord(
						"Failed to add " + std::to_string(instrument.instrument_id) + ", " + instrument.name, false, e.what());
				nlohmann::json json = createRecord;
				LOG(ERROR) << "Unable to create Instrument: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			}
		}
	);

	/**
	 * Read instrument based on name or id
	 */
	methodHandler.addHandler(web::http::methods::GET,
		"/oanda/([^/]*)/instrument/([^/]*)",
		"Instrument Read",
		[&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			std::string name = smatch[2];
			LOG(INFO) << "Reading Instrument: source(" << source << ") name(" << name << ")";
			offcenter::trading::datatypes::Instrument instrument;
			try {
				try {
					tradingDB.instrumentRead(instrument, std::stoul(name));
				} catch(std::exception& e) {
					tradingDB.instrumentRead(instrument, name);
				}

				nlohmann::json json = instrument;
				LOG(DEBUG) << "Instrument Read" << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				offcenter::trading::datatypes::common::ReadRecordError error(
						"Reading Instrument: source(" + source + ") name(" + name + ")",
						e.what());
				nlohmann::json json = instrument;
				LOG(ERROR) << "Unable to read instrument: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			}
		}
	);

	/**
	 * Delete instrument based on name or id
	 */
	methodHandler.addHandler(web::http::methods::DEL,
		"/oanda/([^/]*)/instrument/([^/]*)",
		"Instrument Delete",
		[&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			std::string name = smatch[2];
			LOG(INFO) << "Deleting Instrument: source(" << source << ") name(" << name << ")";
			try {
				unsigned instrument_id;
				bool useInstrumentID = false;
				try {
					instrument_id = std::stoul(name);
					useInstrumentID = true;
				} catch(std::exception& e) {
					useInstrumentID = false;
				}

				if (useInstrumentID) {
					LOG(DEBUG) << "Delete Instrument based on instrument_id: " << instrument_id;
					tradingDB.instrumentDelete(instrument_id);
				} else {
					LOG(DEBUG) << "Delete Instrument based on name: " << name;
					tradingDB.instrumentDelete(name);
				}

				offcenter::trading::datatypes::common::DeleteRecord deleteRecord;
				deleteRecord.name = "Delete record (" + name + ")";
				deleteRecord.success = true;
				nlohmann::json json = deleteRecord;
				LOG(DEBUG) << "Instrument Delete" << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				LOG(ERROR) << "Unable to delete record (" + name + ") - " + e.what();
				message.reply(
						web::http::status_codes::InternalError,
						"Unable to delete record (" + name + ") - " + e.what()).wait();
			}
		}
	);

	/**
	 * Count instruments
	 */
	methodHandler.addHandler(web::http::methods::GET,
		"/oanda/([^/]*)/instrumentcount",
		"Count Instruments",
		[&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			LOG(INFO) << "Count Instruments: source(" << source << ")";
			try {
				int instrumentsCount = tradingDB.instrumentsCount();

				offcenter::trading::datatypes::common::CountRecords countRecords(instrumentsCount);
				nlohmann::json json = countRecords;
				LOG(DEBUG) << "Count Instruments json: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				LOG(ERROR) << "Unable to count instruments - " << e.what();
				offcenter::trading::datatypes::common::CountRecords countRecords(0, false, e.what());
				nlohmann::json json = countRecords;
				message.reply(web::http::status_codes::InternalError, json.dump()).wait();
			}
		}
	);

	/**
	 * Create candlestick data series
	 */
	methodHandler.addHandler(web::http::methods::PUT,
		"/oanda/([^/]*)/candlestickseries/([^/]*)/([^/]*)",
		"Candlestick Data Series Create",
		[&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			std::string instrument = smatch[2];
			std::string granularity = smatch[3];
			offcenter::trading::datatypes::CandlestickDataSeriesByName dataSeries;
			try {
				std::string bodyAsString = message.extract_string().get();
				nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
				dataSeries = bodyAsJson.get<offcenter::trading::datatypes::CandlestickDataSeriesByName>();
				LOG(INFO) << "Creating Candlestick Data Series: source(" << source << ") instrument(" << instrument << ") granularity(" << granularity << ")";
				tradingDB.candlestickDataSeriesCreate(dataSeries, true);

				offcenter::trading::datatypes::common::CreateRecord createRecord(
						"Successfully added " + source + ", " + instrument + ", " + granularity);
				nlohmann::json json = createRecord;
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				offcenter::trading::datatypes::common::CreateRecord createRecord(
						"Failed to add " + dataSeries.instrument_name + ", " + dataSeries.candlestick_granularity_name, false, e.what());
				nlohmann::json json = createRecord;
				LOG(ERROR) << "Unable to create Candlestick Data Series: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			}
		}
	);

	/**
	 * Read all candlestick data series based on name or id
	 */
	methodHandler.addHandler(web::http::methods::GET,
		"/oanda/([^/]*)/candlestickseries",
		"Candlestick Series Read All",
		[&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			LOG(INFO) << "Reading All Candlestick Series: source(" << source << ")";
			std::vector<offcenter::trading::datatypes::CandlestickDataSeriesComplete> candlestickSeries;
			try {
				tradingDB.candlestickDataSeriesRead(candlestickSeries);

				nlohmann::json json = candlestickSeries;
				LOG(DEBUG) << "Candlestick Data Series Read: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				offcenter::trading::datatypes::common::ReadRecordError error(
						"Reading Candlestick Data Series: source(" + source + ")",
						e.what());
				nlohmann::json json = candlestickSeries;
				LOG(ERROR) << "Unable to read candlestick data series: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			}
		}
	);

	/**
	 * Read candlestick data series based on name or id
	 */
	methodHandler.addHandler(web::http::methods::GET,
		"/oanda/([^/]*)/candlestickseries/([^/]*)",
		"Candlestick Series Read",
		[&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			std::string data_series_id = smatch[2];
			LOG(INFO) << "Reading Candlestick Series: source(" << source << ") data_series_id(" << data_series_id << ")";
			offcenter::trading::datatypes::CandlestickDataSeriesComplete candlestickSeries;
			try {
				tradingDB.candlestickDataSeriesRead(candlestickSeries, std::stoul(data_series_id));

				nlohmann::json json = candlestickSeries;
				LOG(DEBUG) << "Candlestick Data Series Read: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				offcenter::trading::datatypes::common::ReadRecordError error(
						"Reading Candlestick Data Series: source(" + source + ") name(" + data_series_id + ")",
						e.what());
				nlohmann::json json = candlestickSeries;
				LOG(ERROR) << "Unable to read candlestick data series: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			}
		}
	);

	/**
	 * Read candlestick data series based names
	 */
	methodHandler.addHandler(web::http::methods::GET,
		"/oanda/([^/]*)/candlestickseriesid/([^/]*)/([^/]*)/([^/]*)",
		"Candlestick Series ID Read",
		[&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			std::string broker = smatch[2];
			std::string instrument = smatch[3];
			std::string candlestick_granularity = smatch[4];
			LOG(INFO) << "Reading Candlestick Series ID by Names: source(" << source
					<< ") broker(" << broker
					<< ") instrument(" << instrument
					<< ") granularity(" << candlestick_granularity << ")";
			offcenter::trading::datatypes::CandlestickDataSeriesByName dataSeries;
			try {
				tradingDB.candlestickDataSeriesIDRead(dataSeries, source, broker, instrument, candlestick_granularity);

				nlohmann::json json = dataSeries;
				LOG(DEBUG) << "Candlestick Data Series ID Read: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				offcenter::trading::datatypes::common::ReadRecordError error(
						"Reading Candlestick Data Series: source(" + source + ")",
						e.what());
				nlohmann::json json = dataSeries;
				LOG(ERROR) << "Unable to read candlestick data id series: " << json.dump() << " - " << e.what();
				message.reply(web::http::status_codes::InternalError, json.dump()).wait();
			}
		}
	);

	/**
	 * Read candlestick data series first/last based on name or id
	 */
	methodHandler.addHandler(web::http::methods::GET,
		"/oanda/([^/]*)/candlestickseries/([^/]*)/firstlast",
		"Candlestick Series First/Last",
		[&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
			const std::string source = smatch[1];
			const std::string data_series_id = smatch[2];
			const std::string logHeader ="/oanda/" + source + "/candlestickseries/" + data_series_id + "/firstlast: ";

			LOG(INFO) << logHeader << "source(" << source << ") data_series_id(" << data_series_id << ")";
			offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord record;
			try {
				tradingDB.candlestickDataFirstLastRecord(std::stoi(data_series_id), record);

				nlohmann::json json = record;
				LOG(DEBUG) << logHeader << "Read: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				offcenter::trading::datatypes::common::ReadRecordError error(
						"Reading Candlestick Data Series First/Last: source(" + source + ") name(" + data_series_id + ")",
						e.what());
				nlohmann::json json = record;
				LOG(ERROR) << logHeader << "Unable to read candlestick data series: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			}
		}
	);

	/**
	 * Delete candlestick data series based on name or id
	 */
	methodHandler.addHandler(web::http::methods::DEL,
		"/oanda/([^/]*)/candlestickseries/([^/]*)",
		"Candlestick Series Delete",
		[&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			std::string data_series_id_as_string = smatch[2];
			LOG(INFO) << "Deleting Candlestick Series: source(" << source << ") name(" << data_series_id_as_string << ")";
			try {
				unsigned data_series_id = std::stoul(data_series_id_as_string);
				tradingDB.candlestickDataSeriesDelete(data_series_id);

				offcenter::trading::datatypes::common::DeleteRecord deleteRecord;
				deleteRecord.name = "Delete record (" + data_series_id_as_string + ")";
				deleteRecord.success = true;
				nlohmann::json json = deleteRecord;
				LOG(DEBUG) << "Candlestick Series Delete" << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				LOG(ERROR) << "Unable to delete record (" + data_series_id_as_string + ") - " + e.what();
				message.reply(
						web::http::status_codes::InternalError,
						"Unable to delete record (" + data_series_id_as_string + ") - " + e.what()).wait();
			}
		}
	);

	/**
	 * Create candlestick data
	 */
	methodHandler.addHandler(web::http::methods::PUT,
		"/oanda/([^/]*)/candlestick/([^/]*)/([^/]*)",
		"Candlestick Create",
		[&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			std::string instrument = smatch[2];
			std::string granularity = smatch[3];
			offcenter::trading::datatypes::CandlestickDataCreate candlestickDataCreate;
			try {
				std::string bodyAsString = message.extract_string().get();
				nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
				candlestickDataCreate = bodyAsJson.get<offcenter::trading::datatypes::CandlestickDataCreate>();
				LOG(INFO) << "Creating Candlestick Data: source(" << source << ") instrument(" << instrument << ") granularity(" << granularity << ")";
				tradingDB.candlestickDataCreate(candlestickDataCreate);

				offcenter::trading::datatypes::common::CreateRecord createRecord(
						"Successfully added " + source + ", " + instrument + ", " + granularity);
				nlohmann::json json = createRecord;
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				offcenter::trading::datatypes::common::CreateRecord createRecord(
						"Failed to add " + candlestickDataCreate.instrument + ", " + candlestickDataCreate.granularity, false, e.what());
				nlohmann::json json = createRecord;
				LOG(ERROR) << "Unable to create Candlestick Data: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			}
		}
	);

	/**
	 * Read candlestick data based on name or id
	 */
	methodHandler.addHandler(web::http::methods::GET,
		"/oanda/([^/]*)/candlestick/([^/]*)/([^/]*)",
		"Candlestick Read",
		[&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			std::string instrument = smatch[2];
			std::string granularity = smatch[3];
			LOG(INFO) << "Reading Candlestick: source(" << source << ") instrument(" << instrument << ") granularity(" << granularity << ")";
			offcenter::trading::datatypes::CandlestickDataRange candlestickRange;
			offcenter::trading::datatypes::CandlestickDataSearch candlestickSearch;
			try {
				std::string bodyAsString = message.extract_string().get();
				LOG(INFO) << "Body: " << bodyAsString;
				nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
				candlestickSearch = bodyAsJson.get<offcenter::trading::datatypes::CandlestickDataSearch>();
				LOG(INFO) << "Read Candlestick Data: source(" << source << ") instrument(" << candlestickSearch.instrument << ") granularity(" << candlestickSearch.granularity << ")";

				tradingDB.candlestickDataRead(candlestickRange, candlestickSearch);

				nlohmann::json json = candlestickRange;
				LOG(DEBUG) << "Candlestick Data Read: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				offcenter::trading::datatypes::common::ReadRecordError error(
						"Reading Candlestick Data Series: source(" + source + ") instrument(" + instrument + ") granularity(" + granularity + "): " + e.what());
				nlohmann::json json = error;
				LOG(ERROR) << "Unable to read candlestick data: " << json.dump() << ":" << e.what();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			}
		}
	);

	/**
	 * Read next candlestick data based on time
	 */
	methodHandler.addHandler(web::http::methods::GET,
		"/oanda/([^/]*)/nextcandlestick/([^/]*)/([^/]*)/([^/]*)",
		"Next Candlestick Read",
		[&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			std::string instrument = smatch[2];
			std::string granularity = smatch[3];
			std::string timeText = smatch[4];
			LOG(INFO) << "Reading Next Candlestick: source(" << source << ") instrument(" << instrument << ") granularity(" << granularity << ") timeText(" << timeText << ")";
			offcenter::trading::datatypes::CandlestickData candlestickData;
			offcenter::trading::datatypes::CandlestickDataAfterDate candlestickSearch;
			try {
				//std::string bodyAsString = message.extract_string().get();
				//LOG(INFO) << "Body: " << bodyAsString;
				//nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
				//candlestickSearch = bodyAsJson.get<offcenter::trading::datatypes::CandlestickDataSearch>();
				//LOG(INFO) << "Read Candlestick Data: source(" << source << ") instrument(" << candlestickSearch.instrument << ") granularity(" << candlestickSearch.granularity << ")";

				candlestickSearch.broker = "oanda";
				candlestickSearch.broker_source = source;
				candlestickSearch.instrument = instrument;
				candlestickSearch.granularity = granularity;
				candlestickSearch.search_time = offcenter::common::make_UTCDateTimeFromISO8601(timeText);

				tradingDB.candlestickDataAfterDate(candlestickData, candlestickSearch);

				nlohmann::json json = candlestickData;
				LOG(DEBUG) << "Candlestick Data Read: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				offcenter::trading::datatypes::common::ReadRecordError error(
						"Reading Next Candlestick Data Series: source(" + source + ") instrument(" + instrument + ") granularity(" + granularity + ") timeText(" + timeText + "): " + e.what());
				nlohmann::json json = error;
				LOG(ERROR) << "Unable to read next candlestick data: " << json.dump() << ":" << e.what();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			}
		}
	);

	/**
	 * Read all broker data
	 */
	methodHandler.addHandler(
		web::http::methods::GET,
		"/oanda/brokers",
		"All Brokers Read",
		getLookupTable<offcenter::trading::datatypes::AllBroker>(
				[&tradingDB=m_tradingDB] (offcenter::trading::datatypes::AllBroker& pRecords) {
					tradingDB.brokersRead(pRecords);
				}
		)
	);

	/**
	 * Read all broker data source data
	 */
	methodHandler.addHandler(
		web::http::methods::GET,
		"/oanda/brokerdatasource",
		"All Brokers Data Source Read",
		getLookupTable<offcenter::trading::datatypes::AllBrokerDataSource>(
				[&tradingDB=m_tradingDB] (offcenter::trading::datatypes::AllBrokerDataSource& pRecords) {
					tradingDB.brokerDataSourceRead(pRecords);
				}
		)
	);

	/**
	 * Read all instrument type data
	 */
	methodHandler.addHandler(
		web::http::methods::GET,
		"/oanda/instrumenttype",
		"All Instrument Type Read",
		getLookupTable<offcenter::trading::datatypes::AllInstrumentType>(
				[&tradingDB=m_tradingDB] (offcenter::trading::datatypes::AllInstrumentType& pRecords) {
					tradingDB.instrumentTypeRead(pRecords);
				}
		)
	);

	/**
	 * Read all guaranteed stop loss order mode for instrument data
	 */
	methodHandler.addHandler(
		web::http::methods::GET,
		"/oanda/guaranteedstoplossordermodeforinstrument",
		"All Guaranteed Stop Loss Order Mode For Instrument Read",
		getLookupTable<offcenter::trading::datatypes::AllGuaranteedStopLossOrderModeForInstrument>(
				[&tradingDB=m_tradingDB] (offcenter::trading::datatypes::AllGuaranteedStopLossOrderModeForInstrument& pRecords) {
					tradingDB.guaranteedStopLossOrderModeForInstrumentRead(pRecords);
				}
		)
	);

	/**
	 * Read all day of week data
	 */
	methodHandler.addHandler(
		web::http::methods::GET,
		"/oanda/dayofweek",
		"All Day Of Week Read",
		getLookupTable<offcenter::trading::datatypes::AllDayOfWeek>(
				[&tradingDB=m_tradingDB] (offcenter::trading::datatypes::AllDayOfWeek& pRecords) {
					tradingDB.dayOfWeek(pRecords);
				}
		)
	);

	/**
	 * Read all candlestick granularity data
	 */
	methodHandler.addHandler(
		web::http::methods::GET,
		"/oanda/candlestickgranularity",
		"All Candlestick Granularity Read",
		getLookupTable<offcenter::trading::datatypes::AllCandlestickGranularity>(
				[&tradingDB=m_tradingDB] (offcenter::trading::datatypes::AllCandlestickGranularity& pRecords) {
					tradingDB.candlestickGranularity(pRecords);
				}
		)
	);

	/**
	 * Read all currency data
	 */
	methodHandler.addHandler(
		web::http::methods::GET,
		"/oanda/currency",
		"All Currency Read",
		getLookupTable<offcenter::trading::datatypes::AllCurrency>(
				[&tradingDB=m_tradingDB] (offcenter::trading::datatypes::AllCurrency& pRecords) {
					tradingDB.currency(pRecords);
				}
		)
	);

	/**
	 * update candlestick data
	 */
	/*
	methodHandler.addHandler(web::http::methods::PATCH,
		"/oanda/([^/]*)/candlestick/([^/]*)/([^/]*)",
		"Candlestick Create",
		[&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
			std::string source = smatch[1];
			std::string instrument = smatch[2];
			std::string granularity = smatch[3];
			offcenter::trading::datatypes::CandlestickData candlestickData;
			try {
				std::string bodyAsString = message.extract_string().get();
				nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
				candlestickData = bodyAsJson.get<offcenter::trading::datatypes::CandlestickData>();
				LOG(INFO) << "Patching Candlestick Data: source(" << source << ") instrument(" << instrument << ") granularity(" << granularity << ")";
				tradingDB.candlestickDataUpdate(candlestickData);

				offcenter::trading::datatypes::common::CreateRecord createRecord(
						"Successfully added " + source + ", " + instrument + ", " + granularity);
				nlohmann::json json = createRecord;
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				offcenter::trading::datatypes::common::CreateRecord createRecord(
						"Failed to add " + candlestickDataCreate.instrument + ", " + candlestickDataCreate.granularity, false, e.what());
				nlohmann::json json = createRecord;
				LOG(ERROR) << "Unable to create Candlestick Data: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			}
		}
	);
	*/

	std::cout << "Initialization complete" << std::endl << "Waiting ..." << std::endl;
}

void OandaPersistenceManagerApp::onInitEndpoint(web::uri &uri)
{
	LOG(DEBUG) << "Endpoint: " << m_restServerConfig->uri().to_string();
	uri = m_restServerConfig->uri();
}

void OandaPersistenceManagerApp::onTearDown()
{
	std::cout << std::endl << "Shutting down" << std::endl;
}

void OandaPersistenceManagerApp::onHelp(const std::string &help)
{
	std::cout << std::endl << help << std::endl;
}

//void RestServerExampleApp::onVersion()
//{
//}

std::string OandaPersistenceManagerApp::getURL(Handlers handler)
{
	//std::string url = m_oandaPersistenceManagerConfig->urlBase();
	//Handlers::Instrument
	return "/";
}

} /* namespace oandapersistencemanager */
} /* namespace trading */
} /* namespace offcenter */
