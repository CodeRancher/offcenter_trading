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
 * @file   OandaPersistenceClient.cpp
 * @author Scott Brauer
 * @date   05-20-2021
 */

#include <nlohmann/json.hpp>

#include "easylogging++.h"

#include "offcenter/trading/oandapersistenceclient/OandaPersistenceClient.hpp"
#include "offcenter/trading/oandapersistenceclient/LookupTableData.hpp"
#include "offcenter/trading/datatypes/LookupTablesJson.hpp"

namespace offcenter {
namespace trading {
namespace oandapersistenceclient {

OandaPersistenceClient::OandaPersistenceClient():
		m_programManagerOptions(),
		m_oanda()
{
	// TODO Auto-generated constructor stub

}

OandaPersistenceClient::~OandaPersistenceClient()
{
	// TODO Auto-generated destructor stub
}

void OandaPersistenceClient::setProgramManagerOptions(
        std::shared_ptr<offcenter::trading::oandapersistenceclient::PersistenceManagerOptions> programManagerOptions)
{
	m_programManagerOptions = programManagerOptions;
	web::http::client::http_client_config clientConfig;
	if (programManagerOptions->isTimeoutDirty()) {
		clientConfig.set_timeout(programManagerOptions->getTimeout());
	}
	if (programManagerOptions->isChunksizeDirty()) {
		clientConfig.set_chunksize(programManagerOptions->getChunksize());
	}
	m_oanda = std::make_shared<web::http::client::http_client>(m_programManagerOptions->getURI(), clientConfig);
}

/*
web::uri OandaPersistenceClient::oandaPersistenceManagerURI()
{
	web::uri_builder uriBuilder;

	uriBuilder.set_scheme("http");
	//uriBuilder.set_user_info(userInfo());
	uriBuilder.set_host("127.0.1.1");
	uriBuilder.set_port("6503");
	//uriBuilder.set_path("/offcenter/trade/" + fragment);
	LOG(DEBUG) << "Oanda HTTP: " << uriBuilder.to_string();
	return uriBuilder.to_uri();
}
*/

/**
 *
 */
offcenter::trading::datatypes::BrokerLookupTablePtr OandaPersistenceClient::brokers()
{
	static offcenter::trading::datatypes::BrokerLookupTablePtr g_brokers =
			std::make_shared<offcenter::trading::datatypes::BrokerLookupTable>(
					getLookupTable<offcenter::trading::datatypes::AllBroker>("/oanda/brokers").records
			);
	return g_brokers;
}

/**
 *
 */
offcenter::trading::datatypes::BrokerDataSourceLookupTablePtr OandaPersistenceClient::brokerDataSource()
{
	static offcenter::trading::datatypes::BrokerDataSourceLookupTablePtr g_brokerDataSource =
			std::make_shared<offcenter::trading::datatypes::BrokerDataSourceLookupTable>(
					getLookupTable<offcenter::trading::datatypes::AllBrokerDataSource>("/oanda/brokerdatasource").records
			);
	return g_brokerDataSource;
}

/**
 *
 */
offcenter::trading::datatypes::InstrumentTypeLookupTablePtr OandaPersistenceClient::instrumentType()
{
	static offcenter::trading::datatypes::InstrumentTypeLookupTablePtr g_instrument =
			std::make_shared<offcenter::trading::datatypes::InstrumentTypeLookupTable>(
					getLookupTable<offcenter::trading::datatypes::AllInstrumentType>("/oanda/instrumenttype").records
			);
	return g_instrument;
}

/**
 *
 */
offcenter::trading::datatypes::GuaranteedStopLossOrderModeForInstrumentLookupTablePtr OandaPersistenceClient::guaranteedStopLossOrderModeForInstrument()
{
	static offcenter::trading::datatypes::GuaranteedStopLossOrderModeForInstrumentLookupTablePtr g_gslomfi =
			std::make_shared<offcenter::trading::datatypes::GuaranteedStopLossOrderModeForInstrumentLookupTable>(
					getLookupTable<offcenter::trading::datatypes::AllGuaranteedStopLossOrderModeForInstrument>("/oanda/guaranteedstoplossordermodeforinstrument").records
			);
	return g_gslomfi;
}

/**
 *
 */
offcenter::trading::datatypes::DayOfWeekLookupTablePtr OandaPersistenceClient::dayOfWeek()
{
	static offcenter::trading::datatypes::DayOfWeekLookupTablePtr g_dayOfWeek =
			std::make_shared<offcenter::trading::datatypes::DayOfWeekLookupTable>(
					getLookupTable<offcenter::trading::datatypes::AllDayOfWeek>("/oanda/dayofweek").records
			);
	return g_dayOfWeek;
}

/**
 *
 */
offcenter::trading::datatypes::CandlestickGranularityLookupTablePtr OandaPersistenceClient::candlestickGranularity()
{
	static offcenter::trading::datatypes::CandlestickGranularityLookupTablePtr g_candlestickGranularity =
			std::make_shared<offcenter::trading::datatypes::CandlestickGranularityLookupTable>(
					getLookupTable<offcenter::trading::datatypes::AllCandlestickGranularity>("/oanda/candlestickgranularity").records
			);
	return g_candlestickGranularity;
}

/**
 *
 */
offcenter::trading::datatypes::CurrencyLookupTablePtr OandaPersistenceClient::currency()
{
	static offcenter::trading::datatypes::CurrencyLookupTablePtr g_currency =
			std::make_shared<offcenter::trading::datatypes::CurrencyLookupTable>(
					getLookupTable<offcenter::trading::datatypes::AllCurrency>("/oanda/currency").records
			);
	return g_currency;
}

//offcenter::trading::datatypes::AllBroker OandaPersistenceClient::getLookupTable()
//{
//	LOG(INFO) << "Read All Brokers";
//
//	web::http::client::http_client oanda(oandaPersistenceManagerURI());
//
//	pplx::task<offcenter::trading::datatypes::AllBroker> response =
//			oanda.request(
//					web::http::methods::GET,
//					"/offcenter/trade/oanda/brokers",
//					"application/json; charset=utf-8")
//	.then([](http_response response) {
//		//LOG(ERROR) << "Status: " << response.status_code() << ":" << response.extract_string().get();
//		if (response.status_code() != web::http::status_codes::OK) {
//			nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
//			LOG(DEBUG) << "Read All Brokers Error: status(" << response.status_code() << ") " << bodyAsJson.dump(4);
//			auto readRecordError = bodyAsJson.get<offcenter::trading::datatypes::common::ReadRecordError>();
//			throw HttpResponseException(readRecordError.message(), response.status_code());
//		}
//		return response.extract_string();
//	})
//	.then([](const std::string bodyAsString) {
//		LOG(DEBUG) << "Read All: " << bodyAsString;
//		nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
//		return bodyAsJson.get<offcenter::trading::datatypes::AllBroker>();
//	});
//	//LOG(INFO) << "Read AllBroker Success: source(" << source << "))";
//	try {
//		return response.get();
//	} catch(std::exception& e) {
//		LOG(ERROR) << "Read AllBroker Error: exception(" << e.what() << ")";
//		throw;
//	}
//}

} /* namespace oandapersistenceclient */
} /* namespace trading */
} /* namespace offcenter */
