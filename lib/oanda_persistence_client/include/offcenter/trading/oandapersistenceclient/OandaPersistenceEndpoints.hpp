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
 * @file   OandaPersistenceEndpoints.hpp
 * @author Scott Brauer
 * @date   05-20-2021
 */

#ifndef OANDA_PERSISTENCE_CLIENT_OANDAPERSISTENCEENDPOINTS_HPP_
#define OANDA_PERSISTENCE_CLIENT_OANDAPERSISTENCEENDPOINTS_HPP_

#include <memory>

#include <nlohmann/json.hpp>

#include "offcenter/soci/Session.hpp"

#include "offcenter/trading/oandapersistenceclient/OandaPersistenceClient.hpp"
#include "offcenter/trading/datatypes/oanda/Instrument.hpp"
#include "offcenter/trading/datatypes/Instrument.hpp"
#include "offcenter/trading/datatypes/CandlestickDataSeries.hpp"
#include "offcenter/trading/datatypes/CandlestickData.hpp"
#include "offcenter/trading/datatypes/Common.hpp"
#include "offcenter/trading/datatypes/Broker.hpp"
#include "offcenter/trading/datatypes/TableInfo.hpp"

namespace offcenter {
namespace trading {
namespace oandapersistenceclient {

/**
 *
 */
class OandaPersistenceEndpoints : public OandaPersistenceClient
{
public:
	OandaPersistenceEndpoints();
	virtual ~OandaPersistenceEndpoints();

	void oandaInstrumentCreate(const std::string& source, const offcenter::trading::datatypes::oanda::InstrumentWithIDs& instrument);
	const offcenter::trading::datatypes::oanda::Instrument oandaInstrumentRead(const std::string& source, const std::string& name);
	const offcenter::trading::datatypes::oanda::Instrument oandaInstrumentRead(const std::string& source, unsigned instrument_id);
	void oandaInstrumentUpdate(const std::string& source, const offcenter::trading::datatypes::oanda::Instrument& instrument);
	offcenter::trading::datatypes::common::DeleteRecord oandaInstrumentDelete(const std::string& source, const std::string& name);
	offcenter::trading::datatypes::common::DeleteRecord oandaInstrumentDelete(const std::string& source, unsigned instrument_id);

	unsigned int oandaInstrumentCount(const std::string& source);

	void instrumentCreate(const std::string& source, const offcenter::trading::datatypes::Instrument& instrument);
	const offcenter::trading::datatypes::Instrument instrumentRead(const std::string& source, const std::string& name);
	const offcenter::trading::datatypes::Instrument instrumentRead(const std::string& source, unsigned instrument_id);
	void instrumentUpdate(const std::string& source, const offcenter::trading::datatypes::Instrument& instrument);
	offcenter::trading::datatypes::common::DeleteRecord instrumentDelete(const std::string& source, const std::string& name);
	offcenter::trading::datatypes::common::DeleteRecord instrumentDelete(const std::string& source, unsigned instrument_id);

	unsigned int instrumentsCount(const std::string& source);

	void candlestickDataSeriesCreate(const std::string& source, const offcenter::trading::datatypes::CandlestickDataSeriesByName& candlestick_data_series);
	const std::vector<offcenter::trading::datatypes::CandlestickDataSeriesComplete> candlestickDataSeriesRead(const std::string &source);

	const offcenter::trading::datatypes::CandlestickDataSeriesByName candlestickDataSeriesIDRead(
			const std::string& source,
	        const std::string& broker_name,
	        const std::string& instrument_name,
	        const std::string& candlestick_granularity_name);

	const offcenter::trading::datatypes::CandlestickDataSeriesComplete candlestickDataSeriesRead(const std::string& source, unsigned candlestick_data_series_id);
	void candlestickDataSeriesUpdate(const std::string& source, const offcenter::trading::datatypes::CandlestickDataSeries& candlestick_data_series);
	offcenter::trading::datatypes::common::DeleteRecord candlestickDataSeriesDelete(const std::string& source, unsigned candlestick_data_series_id);
	const offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord candlestickDataSeriesFirstLast(
			const std::string& source,
			unsigned candlestick_data_series_id,
			const std::string& loggingID);

	void candlestickDataCreate(
			const std::string& source,
			const offcenter::trading::datatypes::CandlestickDataCreate& candlestick_data);

	const offcenter::trading::datatypes::CandlestickDataRange candlestickDataRead(const std::string &source, const offcenter::trading::datatypes::CandlestickDataSearch &search);
	const offcenter::trading::datatypes::CandlestickData nextCandlestickDataRead(
	        const std::string &source,
	        const offcenter::trading::datatypes::CandlestickDataAfterDate &search);
	void candlestickDataUpdate(const std::string& source, const offcenter::trading::datatypes::CandlestickData& candlestick_data);
	offcenter::trading::datatypes::common::DeleteRecord candlestickDataDelete(const std::string& source, unsigned candlestick_data_id);
};

} /* namespace oandapersistenceclient */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OANDA_PERSISTENCE_CLIENT_OANDAPERSISTENCEENDPOINTS_HPP_ */
