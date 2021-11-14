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
 * @file   data_tables.hpp
 * @author Scott Brauer
 * @date   03-31-2021
 */
#ifndef OFFCENTER_TRADING_DB_DATATABLES_HPP_
#define OFFCENTER_TRADING_DB_DATATABLES_HPP_

#include <string>

namespace offcenter {
namespace trading {
namespace db {

namespace table {

/******************************************************************************
 * Instrument
 * Full specification of an Instrument
 */
namespace instrument {

/// Create SQL for instrument
inline std::string create = R"###(
CREATE TABLE instrument
(
	instrument_id INT UNSIGNED AUTO_INCREMENT,
	name CHAR(20) NOT NULL,
	display_name VARCHAR(30) NOT NULL,
	PRIMARY KEY (instrument_id),
	CONSTRAINT ck_instrument_name UNIQUE (name),
	CONSTRAINT ck_instrument_display_name UNIQUE (display_name)
);
)###";

} /* namespace instrument */

/******************************************************************************
 * Candlestick Data Series
 * A holder for a set of candlestick data
 */
namespace candlestick_data_series {

/// Create SQL for candlestick_data_series
inline std::string create = R"###(
CREATE TABLE candlestick_data_series
(
	candlestick_data_series_id INT UNSIGNED AUTO_INCREMENT,
	instrument_id INT UNSIGNED NOT NULL,
	broker_data_source_id TINYINT UNSIGNED NOT NULL,
	candlestick_granularity_id TINYINT UNSIGNED NOT NULL,
	PRIMARY KEY (candlestick_data_series_id),
	FOREIGN KEY (instrument_id) REFERENCES instrument (instrument_id) ON DELETE CASCADE,
	FOREIGN KEY (broker_data_source_id) REFERENCES broker_data_source (broker_data_source_id) ON DELETE CASCADE,
	FOREIGN KEY (candlestick_granularity_id) REFERENCES candlestick_granularity (candlestick_granularity_id) ON DELETE CASCADE,
	CONSTRAINT ck_candlestick_data_series UNIQUE (instrument_id, broker_data_source_id, candlestick_granularity_id)
);
)###";

} /* namespace candlestick_data_series */


/******************************************************************************
 * Currency Pair
 * Full specification of a Currency Pair
 */
namespace candlestick_data {

/// Create SQL for candlestick_data
inline std::string create = R"###(
CREATE TABLE candlestick_data
(
	candlestick_data_id BIGINT UNSIGNED AUTO_INCREMENT,
	candlestick_data_series_id INT UNSIGNED,
	start_time BIGINT UNSIGNED NOT NULL,
	bid_open VARCHAR(10) NOT NULL,
	bid_high VARCHAR(10) NOT NULL,
	bid_low VARCHAR(10) NOT NULL,
	bid_close VARCHAR(10) NOT NULL,
	bid_gap_open VARCHAR(10) NOT NULL,
	ask_open VARCHAR(10) NOT NULL,
	ask_high VARCHAR(10) NOT NULL,
	ask_low VARCHAR(10) NOT NULL,
	ask_close VARCHAR(10) NOT NULL,
	ask_gap_open VARCHAR(10) NOT NULL,
	volume INT UNSIGNED NOT NULL,
	PRIMARY KEY (candlestick_data_id),
	FOREIGN KEY (candlestick_data_series_id) REFERENCES candlestick_data_series (candlestick_data_series_id) ON DELETE CASCADE,
	CONSTRAINT ck_currency_pair_name UNIQUE (candlestick_data_series_id, start_time)
);
)###";

} /* namespace candlestick_data */

} /* namespace table */

} /* namespace db */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DB_DATATABLES_HPP_ */
