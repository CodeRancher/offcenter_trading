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
 * @file   OandaPersistenceManagerApp.hpp
 * @author Scott Brauer
 * @date   05-18-2021
 */

#ifndef OFFCENTER_TRADING_OANDAPERSISTENCEMANAGER_OANDAPERSISTENCEMANAGERAPP_HPP_
#define OFFCENTER_TRADING_OANDAPERSISTENCEMANAGER_OANDAPERSISTENCEMANAGERAPP_HPP_

#include <map>
#include <initializer_list>

#include "offcenter/common/restserver/IRestServerApp.hpp"
#include "offcenter/common/restserver/RestServerProgramOptions.hpp"
#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
using namespace offcenter::common;

#include "offcenter/common/soci/MySQLProgramOptions.hpp"
#include "offcenter/common/soci/Session.hpp"

#include "offcenter/trading/oandapersistencemanager/OandaPersistenceManagerProgramOptions.hpp"
#include "offcenter/trading/db/oanda/OandaTradingDB.hpp"
#include "offcenter/trading/db/TradingDB.hpp"
#include "offcenter/trading/datatypes/CommonJson.hpp"
#include "offcenter/trading/datatypes/LookupTablesJson.hpp"

namespace offcenter {
namespace trading {
namespace oandapersistencemanager {

/**
 *
 */
class OandaPersistenceManagerApp: public restserver::IRestServerApp
{
public:
	enum class Handlers {
		Instrument
	};

	/**
	 *
	 */
	/*
	class PathElements {
		PathElements(std::smatch& smatch, std::initializer_list<int> positions) {
			for (int position : positions) {
				m_values[position] = smatch[positions];
			}
		}
	private:
		std::map<int, std::string> m_values;
	};
	*/

public:
	explicit OandaPersistenceManagerApp();
	virtual ~OandaPersistenceManagerApp();

	void onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) override;
	void onSetUp() override;
	void onInitMethodHandlers(restserver::AutoMethodHandler& methodHandler) override;
	void onInitEndpoint(web::uri& uri) override;
	//virtual void onExecute() = 0; override;
	void onTearDown() override;
	void onHelp(const std::string& help) override;
	//void onVersion() override;

private:
	/**
	 *
	 */
	//auto getBrokersFromDB() {
	//	return [&tradingDB=m_tradingDB] (offcenter::trading::datatypes::AllBroker& pRecords) {
	//		tradingDB.brokersRead(pRecords);
	//	};
	//}

	/**
	 *
	 */
	/*
	template <class PathData, class Record, typename DBAccess>
	auto getLookupTable(DBAccess&& pDBAccess) {
		return [&tradingDB=m_tradingDB](web::http::http_request& message, std::smatch& smatch) {
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
		};
	}
	*/

	/**
	 *
	 */
	template <class Records, typename DBAccess>
	auto getLookupTable(DBAccess&& pDBAccess) {
		return [dbaccess=std::move(pDBAccess)](web::http::http_request& message, std::smatch& smatch) {
			LOG(DEBUG) << "Get Lookup Table";
			std::string source = smatch[1];
			try {
				Records records;
				dbaccess(records);
				nlohmann::json json = records;
				LOG(DEBUG) << "Read lookup data: " << json.dump();
				message.reply(web::http::status_codes::OK, json.dump()).wait();
			} catch(std::exception& e) {
				offcenter::trading::datatypes::common::ReadRecordError error(
						"Read lookup data: source(" + source + "): " + e.what());
				nlohmann::json json = error;
				LOG(ERROR) << "Unable to read data: " << json.dump() << ":" << e.what();
				message.reply(web::http::status_codes::BadRequest, json.dump()).wait();
			}
		};
	}

	std::string getURL(Handlers handler);

private:
	offcenter::soci::MySQLProgramOptions::ConfigPtr m_mysqlConfig;
	offcenter::trading::oandapersistencemanager::OandaPersistenceManagerProgramOptions::ConfigPtr m_oandaPersistenceManagerConfig;
	offcenter::common::restserver::RestServerProgramOptions::ConfigPtr m_restServerConfig;
	offcenter::trading::db::oanda::OandaTradingDB m_oandaTradingDB;
	offcenter::trading::db::TradingDB m_tradingDB;

};

} /* namespace oandapersistencemanager */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_OANDAPERSISTENCEMANAGER_OANDAPERSISTENCEMANAGERAPP_HPP_ */
