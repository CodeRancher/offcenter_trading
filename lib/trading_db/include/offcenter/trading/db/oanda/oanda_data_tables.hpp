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
 * @file   oanda_data_tables.hpp
 * @author Scott Brauer
 * @date   04-06-2021
 */
#ifndef OFFCENTER_TRADING_DB_OANDA_OANDADATATABLES_HPP_
#define OFFCENTER_TRADING_DB_OANDA_OANDADATATABLES_HPP_

#include <string>

namespace offcenter {
namespace trading {
namespace db {
namespace oanda {

namespace table {

/******************************************************************************
 * Instrument
 * Full specification of an Instrument.
 */
namespace oanda_instrument {

/// Create SQL for instrument
inline std::string create = R"###(
CREATE TABLE oanda_instrument
(
	instrument_id INT UNSIGNED AUTO_INCREMENT,
	name VARCHAR(20) NOT NULL,
	instrument_type_id TINYINT UNSIGNED NOT NULL,
	display_name VARCHAR(30) NOT NULL,
	pip_location INT,
	display_precision INT,
	trade_units_precision INT,
	minimum_trade_size DECIMAL,
	maximum_trailing_stop_distance DECIMAL,
	minimum_guaranteed_stop_loss_distance DECIMAL,
	minimum_trailing_stop_distance DECIMAL,
	maximum_position_size DECIMAL,
	maximum_order_units DECIMAL,
	margin_rate DECIMAL,
	commission_commission DECIMAL,
	commission_units_traded DECIMAL,
	commission_minimum_commission DECIMAL,
	guaranteed_stop_loss_order_mode TINYINT UNSIGNED,
	guaranteed_stop_loss_order_execution_premium DECIMAL,
	guaranteed_stop_loss_order_level_restriction_volume DECIMAL,
	guaranteed_stop_loss_order_level_restriction_priceRange DECIMAL,
	financing_longRate DECIMAL,
	financing_shortRate DECIMAL,
	PRIMARY KEY (instrument_id),
	FOREIGN KEY (instrument_type_id) REFERENCES instrument_type (instrument_type_id),
	CONSTRAINT ck_oanda_instrument_name UNIQUE (name),
	CONSTRAINT ck_oanda_instrument_display_name UNIQUE (display_name)
);
)###";


} /* namespace oanda_instrument */

/******************************************************************************
 * Financing Day Of Week
 * A FinancingDayOfWeek message defines a day of the week when financing charges are debited or credited.
 */
namespace oanda_financing_day_of_week {

/// Create SQL for financing_day_of_week
inline std::string create = R"###(
CREATE TABLE oanda_financing_day_of_week
(
	financing_day_of_week_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	instrument_id INT UNSIGNED,
	day_of_week_id TINYINT UNSIGNED NOT NULL,
	days_charged INT NOT NULL,
	PRIMARY KEY (financing_day_of_week_id),
	FOREIGN KEY (instrument_id) REFERENCES oanda_instrument (instrument_id) ON DELETE CASCADE,
	FOREIGN KEY (day_of_week_id) REFERENCES day_of_week (day_of_week_id)
);
)###";

} /* namespace oanda_financing_day_of_week */

/******************************************************************************
 * Instrument Tags
 * Tags specific to an instrument
 */
namespace oanda_instrument_tags {

/// Create SQL for instrument_tags
inline std::string create = R"###(
CREATE TABLE oanda_instrument_tags
(
	instrument_tags_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	instrument_id INT UNSIGNED,
    type VARCHAR(100),
    name VARCHAR(100),
	PRIMARY KEY (instrument_tags_id),
	FOREIGN KEY (instrument_id) REFERENCES oanda_instrument (instrument_id)
);
)###";

} /* namespace oanda_instrument_tags */

} /* namespace table */

} /* namespace oanda */
} /* namespace db */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DB_OANDA_OANDADATATABLES_HPP_ */
