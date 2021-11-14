/**
 * Copyright 2021 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the 'License');
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
 * @file   views.hpp
 * @author Scott Brauer
 * @date   03-31-2021
 */
#ifndef OFFCENTER_TRADING_DB_VIEWS_HPP_
#define OFFCENTER_TRADING_DB_VIEWS_HPP_

#include <string>

namespace offcenter {
namespace trading {
namespace db {

namespace view {

/******************************************************************************
 * Broker Source
 * Combined Broker and Broker Data Source
 */
namespace broker_source {

/// Create SQL for broker_source
inline std::string create = R"###(
CREATE VIEW v_broker_source AS
SELECT 
	b.broker_id,
	bds.broker_data_source_id,
	b.name AS broker_name,
	b.display_name AS broker_display_name,
	b.description AS broker_description,
	bds.name AS source_name,
	bds.display_name AS source_display_name,
	bds.description AS source_description
FROM broker_data_source bds
	INNER JOIN broker b
		ON b.broker_id = bds.broker_id;
)###";

} /* namespace broker_source */

/******************************************************************************
 * Candlestick Data Series
 * Combined Candlestick Data Series
 */
namespace candlestick_data_series {

/// Create SQL for broker_source
inline std::string create = R"###(
CREATE VIEW v_candlestick_data_series AS
SELECT 
	cds.candlestick_data_series_id,
	cds.instrument_id AS instrument_id,
	i.name AS instrument_name,
	b.broker_id AS broker_id,
	b.name AS broker_name,
	b.display_name AS broker_display_name,
	cds.broker_data_source_id AS broker_data_source_id,
	bds.name AS broker_data_source_name,
	bds.display_name AS broker_data_source_display_name,
	cds.candlestick_granularity_id AS candlestick_granularity_id,
	cg.name AS candlestick_granularity_name	
FROM candlestick_data_series cds
	INNER JOIN instrument i
		ON i.instrument_id = cds.instrument_id
	INNER JOIN broker_data_source bds
		ON bds.broker_data_source_id = cds.broker_data_source_id
	INNER JOIN broker b
		ON b.broker_id = bds.broker_id
	INNER JOIN candlestick_granularity cg
		ON cg.candlestick_granularity_id = cds.candlestick_granularity_id;
)###";

} /* namespace candlestick_data_series */

} /* namespace view */

} /* namespace db */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DB_VIEWS_HPP_ */
