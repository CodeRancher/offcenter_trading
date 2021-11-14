/**
 * Copyright 2021 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the );
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
 * @file   OandaPersistenceEndpoints.cpp
 * @author Scott Brauer
 * @date   05-20-2021
 */

#include <string>
#include <exception>

#include "easylogging++.h"

#include "offcenter/trading/oandapersistenceclient/OandaPersistenceEndpoints.hpp"

#include "../../data_types/include/offcenter/trading/datatypes/common/ForexDateTime.hpp"
#include "offcenter/trading/datatypes/oanda/InstrumentJson.hpp"
#include "offcenter/trading/datatypes/InstrumentJson.hpp"
#include "offcenter/trading/datatypes/CandlestickDataSeriesJson.hpp"
#include "offcenter/trading/datatypes/CandlestickDataJson.hpp"
#include "offcenter/trading/datatypes/CommonJson.hpp"
#include "offcenter/trading/datatypes/TableInfoJson.hpp"
#include "offcenter/trading/oandapersistenceclient/Exceptions.hpp"
#include "offcenter/trading/common/Logging.hpp"

namespace offcenter {
namespace trading {
namespace oandapersistenceclient {

OandaPersistenceEndpoints::OandaPersistenceEndpoints()
{
	// TODO Auto-generated constructor stub

}

OandaPersistenceEndpoints::~OandaPersistenceEndpoints()
{
	// TODO Auto-generated destructor stub
}


/**
 *
 */
void OandaPersistenceEndpoints::oandaInstrumentCreate(
		const std::string &source,
        const offcenter::trading::datatypes::oanda::InstrumentWithIDs &instrument)
{
	LOG(INFO) << "Create Oanda Instrument: instrument_id(" << instrument.instrument_id << ") name(" << instrument.name << ")";
	//web::http::client::http_client oanda(oandaPersistenceManagerURI());
	nlohmann::json j = instrument;

	pplx::task<void> voidResponse = m_oanda->request(
			web::http::methods::PUT,
			"/offcenter/trade/oanda/" + source + "/oandainstrument",
			j.dump(),
			"application/json; charset=utf-8")
	.then([&instrument=instrument](http_response response) {
		//std::string bodyAsString = response.extract_string().get();
		//LOG(ERROR) << "bodyAsString: " << bodyAsString;
		nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
		LOG(DEBUG) << "bodyAsJson: " << bodyAsJson.dump(4);
		auto createRecord = bodyAsJson.get<offcenter::trading::datatypes::common::CreateRecord>();
		if (response.status_code() != web::http::status_codes::OK) {
			LOG(ERROR) << "Create Instrument error: " << bodyAsJson.dump(4);
			throw HttpResponseException(createRecord.message(), response.status_code());
		}
		LOG(INFO) << "Create Oanda Instrument Success: instrument_id(" << instrument.instrument_id << ") name(" << instrument.name << ") result(" << createRecord.name << ")";
	});

	voidResponse.wait();
}

/**
 *
 */
const offcenter::trading::datatypes::oanda::Instrument OandaPersistenceEndpoints::oandaInstrumentRead(
        const std::string &source,
        const std::string &name)
{
	LOG(INFO) << "Read Oanda Instrument: source(" << source << ") name(" << name << ")";
	pplx::task<offcenter::trading::datatypes::oanda::Instrument> instrumentResponse =
			m_oanda->request(web::http::methods::GET, "/offcenter/trade/oanda/" + source + "/oandainstrument/" + name)
	.then([name](http_response response) {
		if (response.status_code() != web::http::status_codes::OK) {
			nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
			LOG(DEBUG) << "Read Instrument Error: name(" << name << ") status(" << response.status_code() << ") " << bodyAsJson.dump(4);
			auto readRecordError = bodyAsJson.get<offcenter::trading::datatypes::common::ReadRecordError>();
			throw HttpResponseException(readRecordError.message(), response.status_code());
		}
		return response.extract_string();
	})
	.then([](const std::string bodyAsString) {
		LOG(INFO) << "Read Oanda Instrument String: bodyAsString(" << bodyAsString << ")";
		nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
		return bodyAsJson.get<offcenter::trading::datatypes::oanda::Instrument>();
	});
	LOG(INFO) << "Read Oanda Instrument Success: source(" << source << ") name(" << name << ")";
	return instrumentResponse.get();
}

/**
 *
 */
const offcenter::trading::datatypes::oanda::Instrument OandaPersistenceEndpoints::oandaInstrumentRead(
        const std::string &source,
        unsigned instrument_id)
{
	return oandaInstrumentRead(source, std::to_string(instrument_id));
}

/**
 *
 */
void OandaPersistenceEndpoints::oandaInstrumentUpdate(const std::string &source,
        const offcenter::trading::datatypes::oanda::Instrument &instrument)
{
}

/**
 *
 */
offcenter::trading::datatypes::common::DeleteRecord OandaPersistenceEndpoints::oandaInstrumentDelete(
		const std::string &source,
        const std::string &name)
{
	LOG(INFO) << "Delete Oanda Instrument: source(" << source << ") name(" << name << ")";
	pplx::task<offcenter::trading::datatypes::common::DeleteRecord> response =
			m_oanda->request(web::http::methods::DEL, "/offcenter/trade/oanda/" + source + "/oandainstrument/" + name)
	.then([name](http_response response) {
		nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
		auto deleteRecordError = bodyAsJson.get<offcenter::trading::datatypes::common::DeleteRecord>();
		if (response.status_code() != web::http::status_codes::OK) {
			LOG(DEBUG) << "Delete Oanda Instrument Error: name(" << name << ") status(" << response.status_code() << ") " << bodyAsJson.dump(4);
			throw HttpResponseException(deleteRecordError.message(), response.status_code());
		}
		return deleteRecordError;
	});
	return response.get();
}

/**
 *
 */
offcenter::trading::datatypes::common::DeleteRecord OandaPersistenceEndpoints::oandaInstrumentDelete(
		const std::string &source,
        unsigned instrument_id)
{
	return oandaInstrumentDelete(source, std::to_string(instrument_id));
}

/**
 *
 */
unsigned int OandaPersistenceEndpoints::oandaInstrumentCount(const std::string &source)
{
	return 0;
}

/**
 *
 */
void OandaPersistenceEndpoints::instrumentCreate(
		const std::string &source,
        const offcenter::trading::datatypes::Instrument &instrument)
{
	LOG(INFO) << "Create Instrument: instrument_id(" << instrument.instrument_id << ") name(" << instrument.name << ")";
	nlohmann::json j = instrument;

	pplx::task<void> voidResponse = m_oanda->request(
			web::http::methods::PUT,
			"/offcenter/trade/oanda/" + source + "/instrument",
			j.dump(),
			"application/json; charset=utf-8")
	.then([&instrument=instrument](http_response response) {
		nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
		LOG(DEBUG) << "bodyAsJson: " << bodyAsJson.dump(4);
		auto createRecord = bodyAsJson.get<offcenter::trading::datatypes::common::CreateRecord>();
		if (response.status_code() != web::http::status_codes::OK) {
			LOG(ERROR) << "Create Instrument error: " << bodyAsJson.dump(4);
			throw HttpResponseException(createRecord.message(), response.status_code());
		}
		LOG(INFO) << "Create Instrument Success: instrument_id(" << instrument.instrument_id << ") name(" << instrument.name << ") result(" << createRecord.name << ")";
	});

	voidResponse.wait();
}

/**
 *
 */
const offcenter::trading::datatypes::Instrument OandaPersistenceEndpoints::instrumentRead(
        const std::string &source,
        const std::string &name)
{
	LOG(INFO) << "Read Instrument: source(" << source << ") name(" << name << ")";
	pplx::task<offcenter::trading::datatypes::Instrument> countRecordsResponse =
			m_oanda->request(web::http::methods::GET, "/offcenter/trade/oanda/" + source + "/instrument/" + name)
	.then([name](http_response response) {
		if (response.status_code() != web::http::status_codes::OK) {
			nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
			LOG(DEBUG) << "Read Instrument Error: name(" << name << ") status(" << response.status_code() << ") " << bodyAsJson.dump(4);
			auto readRecordError = bodyAsJson.get<offcenter::trading::datatypes::common::ReadRecordError>();
			throw HttpResponseException(readRecordError.message(), response.status_code());
		}
		return response.extract_string();
	})
	.then([](const std::string bodyAsString) {
		nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
		return bodyAsJson.get<offcenter::trading::datatypes::Instrument>();
	});
	LOG(INFO) << "Read Instrument Success: source(" << source << ") name(" << name << ")";
	return countRecordsResponse.get();
}

const offcenter::trading::datatypes::Instrument OandaPersistenceEndpoints::instrumentRead(
        const std::string &source,
        unsigned instrument_id)
{
	return instrumentRead(source, std::to_string(instrument_id));
}

void OandaPersistenceEndpoints::instrumentUpdate(const std::string &source,
        const offcenter::trading::datatypes::Instrument &instrument)
{
}

/**
 * Instruments count
 *
 * Query the persistence endpoint for the number of instruments.
 *
 * @param source The data source
 */
unsigned int OandaPersistenceEndpoints::instrumentsCount(const std::string &source)
{
	int response = 0;
	try {
		pplx::task<offcenter::trading::datatypes::common::CountRecords> countRecordsResponse =
				m_oanda->request(web::http::methods::GET, "/offcenter/trade/oanda/" + source + "/instrumentcount")
		.then([](http_response response) {
			return response.extract_string();
		})
		.then([](const std::string bodyAsString) {
			nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
			return bodyAsJson.get<offcenter::trading::datatypes::common::CountRecords>();
		});
		response = countRecordsResponse.get().recordCount;
	} catch(web::http::http_exception& e) {
		throw offcenter::trading::oandapersistenceclient::HttpResponseException(e.what(), e.error_code().value());
		LOG(ERROR) << "OandaPersistenceEndpoints::instrumentsCount (" << e.error_code().value() << "): " << e.what();
	} catch(std::exception& e) {
		throw offcenter::trading::oandapersistenceclient::OandaPersistenceClientException(e.what());
		LOG(ERROR) << "OandaPersistenceEndpoints::instrumentsCount: " << e.what();
	}
	return response;
}

/**
 *
 */
offcenter::trading::datatypes::common::DeleteRecord OandaPersistenceEndpoints::instrumentDelete(
        const std::string &source,
        const std::string &name)
{
	LOG(INFO) << "Delete Instrument: source(" << source << ") name(" << name << ")";
	pplx::task<offcenter::trading::datatypes::common::DeleteRecord> response =
			m_oanda->request(web::http::methods::DEL, "/offcenter/trade/oanda/" + source + "/instrument/" + name)
	.then([name](http_response response) {
		nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
		auto deleteRecordError = bodyAsJson.get<offcenter::trading::datatypes::common::DeleteRecord>();
		if (response.status_code() != web::http::status_codes::OK) {
			LOG(DEBUG) << "Delete Instrument Error: name(" << name << ") status(" << response.status_code() << ") " << bodyAsJson.dump(4);
			throw HttpResponseException(deleteRecordError.message(), response.status_code());
		}
		return deleteRecordError;
	});
	return response.get();
}

offcenter::trading::datatypes::common::DeleteRecord OandaPersistenceEndpoints::instrumentDelete(
        const std::string &source, unsigned instrument_id)
{
	return instrumentDelete(source, std::to_string(instrument_id));
}

void OandaPersistenceEndpoints::candlestickDataSeriesCreate(
        const std::string &source,
        const offcenter::trading::datatypes::CandlestickDataSeriesByName &candlestick_data_series)
{
	LOG(INFO) << "Create Candlestick Data Series: instrument(" << candlestick_data_series.instrument_name << ") granularity(" << candlestick_data_series.candlestick_granularity_name << ")";
	nlohmann::json j = candlestick_data_series;

	pplx::task<void> voidResponse = m_oanda->request(
			web::http::methods::PUT,
			"/offcenter/trade/oanda/" + source + "/candlestickseries/" + candlestick_data_series.instrument_name + "/" + candlestick_data_series.candlestick_granularity_name,
			j.dump(),
			"application/json; charset=utf-8")
	.then([&candlestick_data_series=candlestick_data_series](http_response response) {
		nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
		LOG(DEBUG) << "bodyAsJson: " << bodyAsJson.dump(4);
		auto createRecord = bodyAsJson.get<offcenter::trading::datatypes::common::CreateRecord>();
		if (response.status_code() != web::http::status_codes::OK) {
			LOG(ERROR) << "Create Candlestick Data Series error: " << bodyAsJson.dump(4);
			throw HttpResponseException(createRecord.message(), response.status_code());
		}
		LOG(INFO) << "Create Instrument Success: instrument(" << candlestick_data_series.instrument_name << ") granularity(" << candlestick_data_series.candlestick_granularity_name << ")";
	});

	voidResponse.wait();
}

/**
 *
 */
const std::vector<offcenter::trading::datatypes::CandlestickDataSeriesComplete> OandaPersistenceEndpoints::candlestickDataSeriesRead(
        const std::string &source)
{
	LOG(INFO) << "Read All Candlestick Data Series: source(" << source << ")";
	pplx::task<std::vector<offcenter::trading::datatypes::CandlestickDataSeriesComplete>> response =
			m_oanda->request(web::http::methods::GET, "/offcenter/trade/oanda/" + source + "/candlestickseries")
	.then([](http_response response) {
		if (response.status_code() != web::http::status_codes::OK) {
			LOG(DEBUG) << "Reading all candlestick data series" << response.extract_string().get();
			nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
			LOG(DEBUG) << "Read Candlestick Data Series Error: status(" << response.status_code() << ") " << bodyAsJson.dump(4);
			auto readRecordError = bodyAsJson.get<offcenter::trading::datatypes::common::ReadRecordError>();
			throw HttpResponseException(readRecordError.message(), response.status_code());
		}
		return response.extract_string();
	})
	.then([](const std::string bodyAsString) {
		LOG(DEBUG) << "Read All: " << bodyAsString;
		nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
		return bodyAsJson.get<std::vector<offcenter::trading::datatypes::CandlestickDataSeriesComplete>>();
	});
	LOG(INFO) << "Read All Candlestick Data Series Success: source(" << source << "))";
	return response.get();
}

/**
 *
 */
const offcenter::trading::datatypes::CandlestickDataSeriesComplete OandaPersistenceEndpoints::candlestickDataSeriesRead(
        const std::string &source,
        unsigned candlestick_data_series_id)
{
	LOG(INFO) << "Read Candlestick Data Series: source(" << source << ") data_series_id(" << candlestick_data_series_id << ")";
	pplx::task<offcenter::trading::datatypes::CandlestickDataSeriesComplete> response =
			m_oanda->request(web::http::methods::GET, "/offcenter/trade/oanda/" + source + "/candlestickseries/" + std::to_string(candlestick_data_series_id))
	.then([candlestick_data_series_id](http_response response) {
		if (response.status_code() != web::http::status_codes::OK) {
			nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
			LOG(DEBUG) << "Read Candlestick Data Series Error: data_series_id(" << candlestick_data_series_id << ") status(" << response.status_code() << ") " << bodyAsJson.dump(4);
			auto readRecordError = bodyAsJson.get<offcenter::trading::datatypes::common::ReadRecordError>();
			throw HttpResponseException(readRecordError.message(), response.status_code());
		}
		return response.extract_string();
	})
	.then([](const std::string bodyAsString) {
		nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
		return bodyAsJson.get<offcenter::trading::datatypes::CandlestickDataSeriesComplete>();
	});
	LOG(INFO) << "Read Candlestick Data Series Success: source(" << source << ") data_series_id(" << candlestick_data_series_id << ")";
	return response.get();
}

/**
 *
 */
void OandaPersistenceEndpoints::candlestickDataSeriesUpdate(
        const std::string &source,
        const offcenter::trading::datatypes::CandlestickDataSeries &candlestick_data_series)
{
}

/**
 *
 */
offcenter::trading::datatypes::common::DeleteRecord OandaPersistenceEndpoints::candlestickDataSeriesDelete(
        const std::string &source,
        unsigned candlestick_data_series_id)
{
	LOG(INFO) << "Delete Candlestick Data Series: source(" << source << ") data_series_id(" << candlestick_data_series_id << ")";
	pplx::task<offcenter::trading::datatypes::common::DeleteRecord> response =
			m_oanda->request(web::http::methods::DEL, "/offcenter/trade/oanda/" + source + "/candlestickseries/" + std::to_string(candlestick_data_series_id))
	.then([candlestick_data_series_id](http_response response) {
		nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
		auto deleteRecordError = bodyAsJson.get<offcenter::trading::datatypes::common::DeleteRecord>();
		if (response.status_code() != web::http::status_codes::OK) {
			LOG(DEBUG) << "Delete Candlestick Data Series Error: data_series_id(" << candlestick_data_series_id << ") status(" << response.status_code() << ") " << bodyAsJson.dump(4);
			throw HttpResponseException(deleteRecordError.message(), response.status_code());
		}
		return deleteRecordError;
	});
	return response.get();
}

/**
 * Persist candlestick data to the PeristenceManager
 */
void OandaPersistenceEndpoints::candlestickDataCreate(
        const std::string &source,
        const offcenter::trading::datatypes::CandlestickDataCreate &candlestick_data)
{
	const std::string loggingID = offcenter::trading::common::logging::loggerID(
			candlestick_data.broker, candlestick_data.broker_source, candlestick_data.instrument, candlestick_data.granularity);
	CLOG(INFO, loggingID.c_str())
		<< "Create Candlestick Data: instrument(" << candlestick_data.instrument
		<< ") broker(" << candlestick_data.broker
		<< ") broker_source(" << candlestick_data.broker_source
		<< ") granularity(" << candlestick_data.granularity << ")";

	nlohmann::json j = candlestick_data;

	pplx::task<void> voidResponse = m_oanda->request(
			web::http::methods::PUT,
			"/offcenter/trade/oanda/" + source + "/candlestick/" + candlestick_data.instrument + "/" + candlestick_data.granularity,
			j.dump(),
			"application/json; charset=utf-8")
	.then([&candlestick_data=candlestick_data, &loggingID=loggingID](http_response response) {
		nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
		CLOG(DEBUG, loggingID.c_str()) << "Response(" << response.status_code() << ") bodyAsJson: " << bodyAsJson.dump(4);
		auto createRecord = bodyAsJson.get<offcenter::trading::datatypes::common::CreateRecord>();
		if (response.status_code() != web::http::status_codes::OK) {
			CLOG(ERROR, loggingID.c_str()) << "Create Candlestick Data Series error: " << bodyAsJson.dump(4);
			throw HttpResponseException(createRecord.message(), response.status_code());
		}
		CLOG(INFO, loggingID.c_str()) << "Create Candlestick Success: instrument(" << candlestick_data.instrument << ") broker(" << candlestick_data.broker
			<< ") broker_source(" << candlestick_data.broker_source << ") granularity(" << candlestick_data.granularity << ")";
	});

	voidResponse.wait();
}

/**
 *
 */
const offcenter::trading::datatypes::CandlestickDataRange OandaPersistenceEndpoints::candlestickDataRead(
        const std::string &source,
        const offcenter::trading::datatypes::CandlestickDataSearch &search)
{
	LOG(INFO) << "Read All Candlestick Data: source(" << source << ") instrument(" << search.instrument << ") granularity(" << search.granularity << ") start_time(" <<
			offcenter::common::UTCDateTimeToISO8601(search.start_time) << ") end_time(" << offcenter::common::UTCDateTimeToISO8601(search.end_time) << ")";
	nlohmann::json j = search;

	pplx::task<offcenter::trading::datatypes::CandlestickDataRange> response =
			m_oanda->request(web::http::methods::GET,
					"/offcenter/trade/oanda/" + source + "/candlestick/" + search.instrument + "/" + search.granularity,
					j.dump(),
					"application/json; charset=utf-8")
	.then([](http_response response) {
		if (response.status_code() != web::http::status_codes::OK) {
			nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
			LOG(DEBUG) << "Read Candlestick Data Series Error: status(" << response.status_code() << ") " << bodyAsJson.dump(4);
			auto readRecordError = bodyAsJson.get<offcenter::trading::datatypes::common::ReadRecordError>();
			throw HttpResponseException(readRecordError.message(), response.status_code());
		}
		return response.extract_string();
	})
	.then([](const std::string bodyAsString) {
		LOG(DEBUG) << "Read All: " << bodyAsString;
		nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
		return bodyAsJson.get<offcenter::trading::datatypes::CandlestickDataRange>();
	});
	LOG(INFO) << "Read Candlestick Data Success: source(" << source << "))";
	try {
		return response.get();
	} catch(std::exception& e) {
		LOG(ERROR) << "Read Candlestick Data Error: source(" << source << ") instrument(" << search.instrument << ") granularity(" << search.granularity << ") start_time(" <<
			offcenter::common::UTCDateTimeToISO8601(search.start_time) << ") end_time(" << offcenter::common::UTCDateTimeToISO8601(search.end_time) << ") exception" <<
			e.what() << ")";
		throw;
	}
}

/**
 *
 */
const offcenter::trading::datatypes::CandlestickData OandaPersistenceEndpoints::nextCandlestickDataRead(
        const std::string &source,
        const offcenter::trading::datatypes::CandlestickDataAfterDate &search)
{
	LOG(INFO)
			<< "Read Next Candlestick Data: source(" << source
			<< ") instrument(" << search.instrument
			<< ") granularity(" << search.granularity
			<< ")  search_time(" << offcenter::common::UTCDateTimeToISO8601(search.search_time) << ")";
	nlohmann::json j = search;

	pplx::task<offcenter::trading::datatypes::CandlestickData> response =
			m_oanda->request(web::http::methods::GET,
					"/offcenter/trade/oanda/" + source + "/nextcandlestick/" + search.instrument + "/" + search.granularity + "/" + offcenter::common::UTCDateTimeToISO8601(search.search_time),
					j.dump(),
					"application/json; charset=utf-8")
	.then([](http_response response) {
		if (response.status_code() != web::http::status_codes::OK) {
			nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
			LOG(DEBUG) << "Read Next Candlestick Data Series Error: status(" << response.status_code() << ") " << bodyAsJson.dump(4);
			auto readRecordError = bodyAsJson.get<offcenter::trading::datatypes::common::ReadRecordError>();
			throw HttpResponseException(readRecordError.message(), response.status_code());
		}
		return response.extract_string();
	})
	.then([](const std::string bodyAsString) {
		LOG(DEBUG) << "Read Next: " << bodyAsString;
		nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
		return bodyAsJson.get<offcenter::trading::datatypes::CandlestickData>();
	});
	LOG(INFO) << "Read Next Candlestick Data Success: source(" << source << "))";
	try {
		return response.get();
	} catch(std::exception& e) {
		LOG(ERROR) << "Read Next Candlestick Data Error: source(" << source << ") instrument(" << search.instrument << ") granularity(" << search.granularity << ") start_time(" <<
				offcenter::common::UTCDateTimeToISO8601(search.search_time) << ") exception" <<
			e.what() << ")";
		throw;
	}
}

/**
 *
 */
void OandaPersistenceEndpoints::candlestickDataUpdate(
        const std::string &source,
        const offcenter::trading::datatypes::CandlestickData &candlestick_data)
{
}

/**
 *
 */
const offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord OandaPersistenceEndpoints::candlestickDataSeriesFirstLast(
        const std::string &source,
        unsigned candlestick_data_series_id,
		const std::string& loggingID)
{
	CLOG(INFO, loggingID.c_str())
			<< "Read Candlestick Series First/Last: source(" << source
			<< ") data_series_id(" << candlestick_data_series_id << ")";

	pplx::task<offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord> response =
			m_oanda->request(web::http::methods::GET,
			"/offcenter/trade/oanda/" + source + "/candlestickseries/" + std::to_string(candlestick_data_series_id) + "/firstlast")
	.then([&loggingID=loggingID](http_response response) {
		if (response.status_code() != web::http::status_codes::OK) {
			nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
			CLOG(DEBUG, loggingID.c_str()) << "Read Candlestick Data First/Last Error: status(" << response.status_code() << ") " << bodyAsJson.dump(4);
			auto readRecordError = bodyAsJson.get<offcenter::trading::datatypes::common::ReadRecordError>();
			throw HttpResponseException(readRecordError.message(), response.status_code());
		}
		return response.extract_string();
	})
	.then([&loggingID=loggingID](const std::string bodyAsString) {
		CLOG(DEBUG, loggingID.c_str()) << "Read All: " << bodyAsString;
		nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
		return bodyAsJson.get<offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord>();
	});
	CLOG(INFO, loggingID.c_str()) << "Read Candlestick Data First/Last Success: source(" << source << "))";
	try {
		return response.get();
	} catch(std::exception& e) {
		CLOG(ERROR, loggingID.c_str())
				<< "Read Candlestick Data First/Last Error: source(" << source
				<< ") data_series_id(" << candlestick_data_series_id
				<< ") exception(" << e.what() << ")";
		throw;
	}
}

const offcenter::trading::datatypes::CandlestickDataSeriesByName OandaPersistenceEndpoints::candlestickDataSeriesIDRead(
		const std::string& source,
		const std::string& broker_name,
		const std::string& instrument_name,
		const std::string& candlestick_granularity_name)
{
	LOG(INFO) << "Read Candlestick Data Series ID: source(" << source
			<< ") broker(" << broker_name
			<< ") instrument(" << instrument_name
			<< ") granularity(" << candlestick_granularity_name << ")";
	pplx::task<offcenter::trading::datatypes::CandlestickDataSeriesByName> response =
			m_oanda->request(web::http::methods::GET, "/offcenter/trade/oanda/" + source + "/candlestickseriesid/" + broker_name + "/" + instrument_name + "/" + candlestick_granularity_name)
	.then([](http_response response) {
		if (response.status_code() != web::http::status_codes::OK) {
			LOG(DEBUG) << "Reading candlestick data id" << response.extract_string().get();
			nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
			LOG(DEBUG) << "Read Candlestick Data ID Error: status(" << response.status_code() << ") " << bodyAsJson.dump(4);
			auto readRecordError = bodyAsJson.get<offcenter::trading::datatypes::common::ReadRecordError>();
			throw HttpResponseException(readRecordError.message(), response.status_code());
		}
		return response.extract_string();
	})
	.then([](const std::string bodyAsString) {
		LOG(DEBUG) << "Read Candlestick Data Series ID success: " << bodyAsString;
		nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
		return bodyAsJson.get<offcenter::trading::datatypes::CandlestickDataSeriesByName>();
	});
	try {
		return response.get();
	} catch(std::exception& e) {
		LOG(ERROR) << "Read Candlestick Data Series ID Error: source(" << source
				<< ") broker(" << broker_name
				<< ") instrument(" << instrument_name
				<< ") granularity(" << candlestick_granularity_name
				<< ") exception(" << e.what() << ")";
		throw;
	}
}

/**
 *
 */
offcenter::trading::datatypes::common::DeleteRecord OandaPersistenceEndpoints::candlestickDataDelete(
		const std::string& source,
		unsigned candlestick_data_id)
{
	LOG(INFO) << "Delete Candlestick Data: source(" << source << ") candlestick_data_id(" << candlestick_data_id << ")";
	pplx::task<offcenter::trading::datatypes::common::DeleteRecord> response =
			m_oanda->request(web::http::methods::DEL, "/offcenter/trade/oanda/" + source + "/candlestick/" + std::to_string(candlestick_data_id))
	.then([candlestick_data_id](http_response response) {
		nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
		auto deleteRecordError = bodyAsJson.get<offcenter::trading::datatypes::common::DeleteRecord>();
		if (response.status_code() != web::http::status_codes::OK) {
			LOG(DEBUG) << "Delete Candlestick Data Error: candlestick_data_id(" << candlestick_data_id << ") status(" << response.status_code() << ") " << bodyAsJson.dump(4);
			throw HttpResponseException(deleteRecordError.message(), response.status_code());
		}
		return deleteRecordError;
	});
	return response.get();
}

} /* namespace oandapersistenceclient */
} /* namespace trading */
} /* namespace offcenter */
