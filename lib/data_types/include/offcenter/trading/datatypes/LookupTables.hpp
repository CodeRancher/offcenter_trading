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
 * @file   LookupTables.hpp
 * @author Scott Brauer
 * @date   06-22-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_LOOKUPTABLES_HPP_
#define OFFCENTER_TRADING_DATATYPES_LOOKUPTABLES_HPP_

#include <string>
#include <vector>

#include "common/ForexDateTime.hpp"
#include "offcenter/trading/datatypes/common/LookupTableData.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

/**
 *
 */
template<class Record>
struct AllRecords
{
	//offcenter::trading::datatypes::UTCDateTime updateDateTime;
	std::vector<Record> records;
};

/**
 *
 */
struct BrokerDB
{
	int broker_id;
	std::string name;
	std::string display_name;
	std::string description;
};
using AllBroker = AllRecords<BrokerDB>;
template<>
inline unsigned offcenter::trading::datatypes::common::getID<offcenter::trading::datatypes::BrokerDB>(offcenter::trading::datatypes::BrokerDB& record) {
	return record.broker_id;
}
using BrokerLookupTable = offcenter::trading::datatypes::common::LookupTableData<offcenter::trading::datatypes::BrokerDB>;
using BrokerLookupTablePtr = std::shared_ptr<BrokerLookupTable>;

/**
 *
 */
struct BrokerDataSource
{
	int broker_data_source_id;
	std::string name;
	std::string display_name;
	std::string description;;
	int broker_id;
};
using AllBrokerDataSource = AllRecords<BrokerDataSource>;
template<>
inline unsigned offcenter::trading::datatypes::common::getID<offcenter::trading::datatypes::BrokerDataSource>(offcenter::trading::datatypes::BrokerDataSource& record) {
	return record.broker_data_source_id;
}
using BrokerDataSourceLookupTable = offcenter::trading::datatypes::common::LookupTableData<offcenter::trading::datatypes::BrokerDataSource>;
using BrokerDataSourceLookupTablePtr = std::shared_ptr<BrokerDataSourceLookupTable>;

/**
 *
 */
struct InstrumentType
{
	int instrument_type_id;
	std::string name;
	std::string description;;
};
using AllInstrumentType = AllRecords<InstrumentType>;
template<>
inline unsigned offcenter::trading::datatypes::common::getID<offcenter::trading::datatypes::InstrumentType>(offcenter::trading::datatypes::InstrumentType& record) {
	return record.instrument_type_id;
}
using InstrumentTypeLookupTable = offcenter::trading::datatypes::common::LookupTableData<offcenter::trading::datatypes::InstrumentType>;
using InstrumentTypeLookupTablePtr = std::shared_ptr<InstrumentTypeLookupTable>;

/**
 *
 */
struct GuaranteedStopLossOrderModeForInstrument
{
	int guaranteed_stop_loss_order_mode_for_instrument_id;
	std::string name;
	std::string description;;
};
using AllGuaranteedStopLossOrderModeForInstrument = AllRecords<GuaranteedStopLossOrderModeForInstrument>;
template<>
inline unsigned offcenter::trading::datatypes::common::getID<offcenter::trading::datatypes::GuaranteedStopLossOrderModeForInstrument>(offcenter::trading::datatypes::GuaranteedStopLossOrderModeForInstrument& record) {
	return record.guaranteed_stop_loss_order_mode_for_instrument_id;
}
using GuaranteedStopLossOrderModeForInstrumentLookupTable = offcenter::trading::datatypes::common::LookupTableData<offcenter::trading::datatypes::GuaranteedStopLossOrderModeForInstrument>;
using GuaranteedStopLossOrderModeForInstrumentLookupTablePtr = std::shared_ptr<GuaranteedStopLossOrderModeForInstrumentLookupTable>;

/**
 *
 */
struct DayOfWeek
{
	int day_of_week_id;
	std::string name;
	std::string description;;
};
using AllDayOfWeek = AllRecords<DayOfWeek>;
template<>
inline unsigned offcenter::trading::datatypes::common::getID<offcenter::trading::datatypes::DayOfWeek>(offcenter::trading::datatypes::DayOfWeek& record) {
	return record.day_of_week_id;
}
using DayOfWeekLookupTable = offcenter::trading::datatypes::common::LookupTableData<offcenter::trading::datatypes::DayOfWeek>;
using DayOfWeekLookupTablePtr = std::shared_ptr<DayOfWeekLookupTable>;

/**
 *
 */
struct CandlestickGranularity
{
	int candlestick_granularity_id;
	std::string name;
	std::string description;
	std::string alignment;
	unsigned duration_in_seconds;
};
using AllCandlestickGranularity = AllRecords<CandlestickGranularity>;
template<>
inline unsigned offcenter::trading::datatypes::common::getID<offcenter::trading::datatypes::CandlestickGranularity>(offcenter::trading::datatypes::CandlestickGranularity& record) {
	return record.candlestick_granularity_id;
}
using CandlestickGranularityLookupTable = offcenter::trading::datatypes::common::LookupTableData<offcenter::trading::datatypes::CandlestickGranularity>;
using CandlestickGranularityLookupTablePtr = std::shared_ptr<CandlestickGranularityLookupTable>;

/**
 *
 */
struct Currency
{
	unsigned currency_id;
	std::string name;
	std::string currency;
	int numeric_code;;
};
using AllCurrency = AllRecords<Currency>;
template<>
inline unsigned offcenter::trading::datatypes::common::getID<offcenter::trading::datatypes::Currency>(offcenter::trading::datatypes::Currency& record) {
	return record.currency_id;
}
using CurrencyLookupTable = offcenter::trading::datatypes::common::LookupTableData<offcenter::trading::datatypes::Currency>;
using CurrencyLookupTablePtr = std::shared_ptr<CurrencyLookupTable>;

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_LOOKUPTABLES_HPP_ */
