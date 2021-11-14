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
 * @file   OandaPersistenceClient.hpp
 * @author Scott Brauer
 * @date   05-20-2021
 */

#ifndef OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_OANDAPERSISTENCECLIENT_HPP_
#define OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_OANDAPERSISTENCECLIENT_HPP_

#include <cpprest/http_client.h>
#include <cpprest/http_msg.h>
#include <cpprest/filestream.h>
#include <cpprest/containerstream.h>
#include <cpprest/filestream.h>
//#include <cpprest/json.h>
#include <cpprest/producerconsumerstream.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace ::pplx;
using namespace utility;
using namespace concurrency::streams;

#include "easylogging++.h"

#include "offcenter/trading/datatypes/LookupTables.hpp"
#include "offcenter/trading/oandapersistenceclient/Exceptions.hpp"
#include "offcenter/trading/datatypes/CommonJson.hpp"
#include "offcenter/trading/oandapersistenceclient/PersistenceManagerOptions.hpp"

namespace offcenter {
namespace trading {
namespace oandapersistenceclient {

/**
 *
 */
class OandaPersistenceClient
{
public:
	OandaPersistenceClient();
	virtual ~OandaPersistenceClient();

	void setProgramManagerOptions(std::shared_ptr<offcenter::trading::oandapersistenceclient::PersistenceManagerOptions> programManagerOptions);

	offcenter::trading::datatypes::BrokerLookupTablePtr brokers();
	offcenter::trading::datatypes::BrokerDataSourceLookupTablePtr brokerDataSource();
	offcenter::trading::datatypes::InstrumentTypeLookupTablePtr instrumentType();
	offcenter::trading::datatypes::GuaranteedStopLossOrderModeForInstrumentLookupTablePtr guaranteedStopLossOrderModeForInstrument();
	offcenter::trading::datatypes::DayOfWeekLookupTablePtr dayOfWeek();
	offcenter::trading::datatypes::CandlestickGranularityLookupTablePtr candlestickGranularity();
	offcenter::trading::datatypes::CurrencyLookupTablePtr currency();

//protected:
//	web::uri oandaPersistenceManagerURI();

protected:
	std::shared_ptr<offcenter::trading::oandapersistenceclient::PersistenceManagerOptions> m_programManagerOptions;
	std::shared_ptr<web::http::client::http_client> m_oanda;

private:
	template<class AllRecords>
	AllRecords getLookupTable(std::string clientFragment)
	{
		LOG(INFO) << "Read All Records: " << clientFragment;

		pplx::task<AllRecords> response =
				m_oanda->request(
						web::http::methods::GET,
						"/offcenter/trade" + clientFragment,
						"application/json; charset=utf-8")
		.then([](http_response response) {
			//LOG(ERROR) << "Status: " << response.status_code() << ":" << response.extract_string().get();
			if (response.status_code() != web::http::status_codes::OK) {
				nlohmann::json bodyAsJson = nlohmann::json::parse(response.extract_string().get());
				LOG(DEBUG) << "Read All Brokers Error: status(" << response.status_code() << ") " << bodyAsJson.dump(4);
				auto readRecordError = bodyAsJson.get<offcenter::trading::datatypes::common::ReadRecordError>();
				throw HttpResponseException(readRecordError.message(), response.status_code());
			}
			return response.extract_string();
		})
		.then([](const std::string bodyAsString) {
			LOG(DEBUG) << "Read All: " << bodyAsString;
			nlohmann::json bodyAsJson = nlohmann::json::parse(bodyAsString);
			return bodyAsJson.get<AllRecords>();
		});
		//LOG(INFO) << "Read AllBroker Success: source(" << source << "))";
		try {
			return response.get();
		} catch(std::exception& e) {
			LOG(ERROR) << "Read AllBroker Error: exception(" << e.what() << ")";
			throw;
		}
	}
};

} /* namespace oandapersistenceclient */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_OANDAPERSISTENCECLIENT_HPP_ */
