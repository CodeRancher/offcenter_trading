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
 * @file   lookup_tables.hpp
 * @author Scott Brauer
 * @date   03-31-2021
 */
#ifndef OFFCENTER_TRADING_DB_LOOKUPTABLES_HPP_
#define OFFCENTER_TRADING_DB_LOOKUPTABLES_HPP_

#include <string>

namespace offcenter {
namespace trading {
namespace db {

namespace table {

/******************************************************************************
 * Broker
 * Broker information
 */
namespace broker {

/// Create SQL for broker
inline std::string create = R"###(
CREATE TABLE broker
(
	broker_id TINYINT UNSIGNED NOT NULL AUTO_INCREMENT,
	name VARCHAR(10) NOT NULL,
	display_name VARCHAR(20) NOT NULL,
	description VARCHAR(200),
	PRIMARY KEY (broker_id),
	CONSTRAINT ck_broker_name UNIQUE (name)
);
)###";

/// Populate SQL for broker
inline std::string populate = R"###(
INSERT INTO
	broker (name, display_name, description)
VALUES
	('oanda', 'Oanda',	'OANDA Corporation is a registered Futures Commission Merchant and Retail Foreign Exchange Dealer with the Commodity Futures Trading Commission and is a member of the National Futures Association.')
)###";

} /* namespace broker */

/******************************************************************************
 * Broker Data Source
 * Broker data source information
 */
namespace broker_data_source {

/// Create SQL for broker_data_source
inline std::string create = R"###(
CREATE TABLE broker_data_source
(
	broker_data_source_id TINYINT UNSIGNED NOT NULL AUTO_INCREMENT,
	name VARCHAR(50) NOT NULL,
	display_name VARCHAR(50) NOT NULL,
	description VARCHAR(200),
	broker_id TINYINT UNSIGNED NOT NULL,
	PRIMARY KEY (broker_data_source_id),
	FOREIGN KEY (broker_id) REFERENCES broker (broker_id),
	CONSTRAINT ck_broker_data_source_name UNIQUE (name)
);
)###";

/// Populate SQL for broker_data_source
inline std::string populate = R"###(
INSERT INTO
	broker_data_source (name, display_name, description, broker_id)
VALUES
	('fxpractice', 'fxTrade Practice',	'A stable environment; recommended for testing with your fxTrade Practice account and your personal access token.',
		(SELECT broker_id FROM broker WHERE name = 'oanda')),
	('fxtrade', 'fxTrade',	'A stable environment; recommended for production-ready code to execute with your fxTrade account and your personal access token.',
		(SELECT broker_id FROM broker WHERE name = 'oanda'))
)###";

} /* namespace broker_data_source */

/******************************************************************************
 * Instrument Type
 * The type of an Instrument.
 */
namespace instrument_type {

/// Create SQL for instrument_type
inline std::string create = R"###(
CREATE TABLE instrument_type
(
	instrument_type_id TINYINT UNSIGNED NOT NULL AUTO_INCREMENT,
	name VARCHAR(10) NOT NULL,
	description VARCHAR(30),
	PRIMARY KEY (instrument_type_id),
	CONSTRAINT ck_instrument_type_name UNIQUE (name)
);
)###";

/// Populate SQL for instrument_type
inline std::string populate = R"###(
INSERT INTO
	instrument_type (name, description)
VALUES
	('CURRENCY',	'Currency'),
	('CFD',			'Contract For Difference'),
	('METAL',		'Metal');
)###";

} /* namespace instrument_type */

/******************************************************************************
 * Guaranteed Stop Loss Order Mode For Instrument
 * The overall behaviour of the Account regarding Guaranteed Stop Loss Orders for a specific Instrument.
 */
namespace guaranteed_stop_loss_order_mode_for_instrument {

/// Create SQL for guaranteed_stop_loss_order_mode_for_instrument
inline std::string create = R"###(
CREATE TABLE guaranteed_stop_loss_order_mode_for_instrument
(
	guaranteed_stop_loss_order_mode_for_instrument_id TINYINT UNSIGNED NOT NULL AUTO_INCREMENT,
	name VARCHAR(10) NOT NULL,
	description VARCHAR(130),
	PRIMARY KEY (guaranteed_stop_loss_order_mode_for_instrument_id),
	CONSTRAINT ck_guaranteed_stop_loss_order_mode_for_instrument_name UNIQUE (name)
);
)###";

/// Populate SQL for guaranteed_stop_loss_order_mode_for_instrument
inline std::string populate = R"###(
INSERT INTO
	guaranteed_stop_loss_order_mode_for_instrument (name, description)
VALUES
	('DISABLED',	'The Account is not permitted to create Guaranteed Stop Loss Orders for this Instrument.'),
	('ALLOWED',		'The Account is able, but not required to have Guaranteed Stop Loss Orders for open Trades for this Instrument.'),
	('REQUIRED',	'The Account is required to have Guaranteed Stop Loss Orders for all open Trades for this Instrument.');
)###";

} /* namespace guaranteed_stop_loss_order_mode_for_instrument */

/******************************************************************************
 * Day Of Week
 * The Day Of Week provides a representation of the day of the week.
 */
namespace day_of_week {

/// Create SQL for day_of_week
inline std::string create = R"###(
CREATE TABLE day_of_week
(
	day_of_week_id TINYINT UNSIGNED NOT NULL AUTO_INCREMENT,
	name VARCHAR(10) NOT NULL,
	description VARCHAR(30),
	PRIMARY KEY (day_of_week_id),
	CONSTRAINT ck_day_of_week_name UNIQUE (name)
);
)###";

/// Populate SQL for day_of_week
inline std::string populate = R"###(
INSERT INTO
	day_of_week (name, description)
VALUES
	('SUNDAY',		'Sunday'),
	('MONDAY',		'Monday'),
	('TUESDAY',		'Tuesday'),
	('WEDNESDAY',	'Wednesday'),
	('THURSDAY',	'Thursday'),
	('FRIDAY',		'Friday'),
	('SATURDAY',	'Saturday');
)###";

} /* namespace day_of_week */

/******************************************************************************
 * CandlestickGranularity
 * The granularity of a candlestick
 */
namespace candlestick_granularity {

/// Create SQL for candlestick_granularity
inline std::string create = R"###(
CREATE TABLE candlestick_granularity
(
	candlestick_granularity_id TINYINT UNSIGNED NOT NULL AUTO_INCREMENT,
	name VARCHAR(10) NOT NULL,
	description VARCHAR(30),
	alignment VARCHAR(40),
	duration_in_seconds INT UNSIGNED,
	PRIMARY KEY (candlestick_granularity_id),
	CONSTRAINT ck_candlestick_granularity_name UNIQUE (name)
);
)###";

/// Populate SQL for candlestick_granularity
inline std::string populate = R"###(
INSERT INTO
	candlestick_granularity (name, description, alignment, duration_in_seconds)
VALUES
	('S5',	'5 second candlesticks',	'minute alignment',						5),
	('S10', '10 second candlesticks',	'minute alignment',						10),
	('S15', '15 second candlesticks',	'minute alignment',						15),
	('S30', '30 second candlesticks',	'minute alignment',						30),
	('M1',	'1 minute candlesticks',	'minute alignment',						60 * 1),
	('M2',	'2 minute candlesticks',	'hour alignment',						60 * 2),
	('M4',	'4 minute candlesticks',	'hour alignment',						60 * 4),
	('M5',	'5 minute candlesticks',	'hour alignment',						60 * 5),
	('M10',	'10 minute candlesticks',	'hour alignment',						60 * 10),
	('M15',	'15 minute candlesticks',	'hour alignment',						60 * 15),
	('M30',	'30 minute candlesticks',	'hour alignment',						60 * 30),
	('H1',	'1 hour candlesticks',		'hour alignment',						60 * 60 * 1),
	('H2',	'2 hour candlesticks',		'day alignment',						60 * 60 * 2),
	('H3',	'3 hour candlesticks',		'day alignment',						60 * 60 * 3),
	('H4',	'4 hour candlesticks',		'day alignment',						60 * 60 * 4),
	('H6',	'6 hour candlesticks',		'day alignment',						60 * 60 * 6),
	('H8',	'8 hour candlesticks',		'day alignment',						60 * 60 * 8),
	('H12',	'12 hour candlesticks',		'day alignment',						60 * 60 * 12),
	('D',	'1 day candlesticks',		'day alignment',						60 * 60 * 24),
	('W',	'1 week candlesticks',		'aligned to start of week',				60 * 60 * 24 * 7),
	('M',	'1 month candlesticks',		'aligned to first day of the month',	60 * 60 * 24 * 30);
)###";

} /* namespace candlestick_granularity */

/******************************************************************************
 * Currency
 * The granularity of a candlestick
 */
namespace currency {

/// Create SQL for candlestick_granularity
inline std::string create = R"###(
CREATE TABLE currency
(
	currency_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	name CHAR(3) NOT NULL,
	currency VARCHAR(70) NOT NULL,
	numeric_code INT,
	PRIMARY KEY (currency_id),
	CONSTRAINT ck_currency_name UNIQUE (name)
);
)###";

/// Populate SQL for currency
inline std::string populate = R"###(
INSERT INTO
	currency (name, currency, numeric_code)
VALUES
	('AED', 'UAE Dirham', 784),
	('AFN', 'Afghani', 971),
	('ALL', 'Lek', 008),
	('AMD', 'Armenian Dram', 051),
	('ANG', 'Netherlands Antillean Guilder', 532),
	('AOA', 'Kwanza', 973),
	('ARS', 'Argentine Peso', 032),
	('AUD', 'Australian Dollar', 036),
	('AWG', 'Aruban Florin', 533),
	('AZN', 'Azerbaijan Manat', 944),
	('BAM', 'Convertible Mark', 977),
	('BBD', 'Barbados Dollar', 052),
	('BDT', 'Taka', 050),
	('BGN', 'Bulgarian Lev', 975),
	('BHD', 'Bahraini Dinar', 048),
	('BIF', 'Burundi Franc', 108),
	('BMD', 'Bermudian Dollar', 060),
	('BND', 'Brunei Dollar', 096),
	('BOB', 'Boliviano', 068),
	('BOV', 'Mvdol', 984),
	('BRL', 'Brazilian Real', 986),
	('BSD', 'Bahamian Dollar', 044),
	('BTN', 'Ngultrum', 064),
	('BWP', 'Pula', 072),
	('BYN', 'Belarusian Ruble', 933),
	('BZD', 'Belize Dollar', 084),
	('CAD', 'Canadian Dollar', 124),
	('CDF', 'Congolese Franc', 976),
	('CHE', 'WIR Euro', 947),
	('CHF', 'Swiss Franc', 756),
	('CHW', 'WIR Franc', 948),
	('CLF', 'Unidad de Fomento', 990),
	('CLP', 'Chilean Peso', 152),
	('CNY', 'Yuan Renminbi', 156),
	('COP', 'Colombian Peso', 170),
	('COU', 'Unidad de Valor Real', 970),
	('CRC', 'Costa Rican Colon', 188),
	('CUC', 'Peso Convertible', 931),
	('CUP', 'Cuban Peso', 192),
	('CVE', 'Cabo Verde Escudo', 132),
	('CZK', 'Czech Koruna', 203),
	('DJF', 'Djibouti Franc', 262),
	('DKK', 'Danish Krone', 208),
	('DOP', 'Dominican Peso', 214),
	('DZD', 'Algerian Dinar', 012),
	('EGP', 'Egyptian Pound', 818),
	('ERN', 'Nakfa', 232),
	('ETB', 'Ethiopian Birr', 230),
	('EUR', 'Euro', 978),
	('FJD', 'Fiji Dollar', 242),
	('FKP', 'Falkland Islands Pound', 238),
	('GBP', 'Pound Sterling', 826),
	('GEL', 'Lari', 981),
	('GHS', 'Ghana Cedi', 936),
	('GIP', 'Gibraltar Pound', 292),
	('GMD', 'Dalasi', 270),
	('GNF', 'Guinean Franc', 324),
	('GTQ', 'Quetzal', 320),
	('GYD', 'Guyana Dollar', 328),
	('HKD', 'Hong Kong Dollar', 344),
	('HNL', 'Lempira', 340),
	('HRK', 'Kuna', 191),
	('HTG', 'Gourde', 332),
	('HUF', 'Forint', 348),
	('IDR', 'Rupiah', 360),
	('ILS', 'New Israeli Sheqel', 376),
	('INR', 'Indian Rupee', 356),
	('IQD', 'Iraqi Dinar', 368),
	('IRR', 'Iranian Rial', 364),
	('ISK', 'Iceland Krona', 352),
	('JMD', 'Jamaican Dollar', 388),
	('JOD', 'Jordanian Dinar', 400),
	('JPY', 'Yen', 392),
	('KES', 'Kenyan Shilling', 404),
	('KGS', 'Som', 417),
	('KHR', 'Riel', 116),
	('KMF', 'Comorian Franc ', 174),
	('KPW', 'North Korean Won', 408),
	('KRW', 'Won', 410),
	('KWD', 'Kuwaiti Dinar', 414),
	('KYD', 'Cayman Islands Dollar', 136),
	('KZT', 'Tenge', 398),
	('LAK', 'Lao Kip', 418),
	('LBP', 'Lebanese Pound', 422),
	('LKR', 'Sri Lanka Rupee', 144),
	('LRD', 'Liberian Dollar', 430),
	('LSL', 'Loti', 426),
	('LYD', 'Libyan Dinar', 434),
	('MAD', 'Moroccan Dirham', 504),
	('MDL', 'Moldovan Leu', 498),
	('MGA', 'Malagasy Ariary', 969),
	('MKD', 'Denar', 807),
	('MMK', 'Kyat', 104),
	('MNT', 'Tugrik', 496),
	('MOP', 'Pataca', 446),
	('MRU', 'Ouguiya', 929),
	('MUR', 'Mauritius Rupee', 480),
	('MVR', 'Rufiyaa', 462),
	('MWK', 'Malawi Kwacha', 454),
	('MXN', 'Mexican Peso', 484),
	('MXV', 'Mexican Unidad de Inversion (UDI)', 979),
	('MYR', 'Malaysian Ringgit', 458),
	('MZN', 'Mozambique Metical', 943),
	('NAD', 'Namibia Dollar', 516),
	('NGN', 'Naira', 566),
	('NIO', 'Cordoba Oro', 558),
	('NOK', 'Norwegian Krone', 578),
	('NPR', 'Nepalese Rupee', 524),
	('NZD', 'New Zealand Dollar', 554),
	('OMR', 'Rial Omani', 512),
	('PAB', 'Balboa', 590),
	('PEN', 'Sol', 604),
	('PGK', 'Kina', 598),
	('PHP', 'Philippine Peso', 608),
	('PKR', 'Pakistan Rupee', 586),
	('PLN', 'Zloty', 985),
	('PYG', 'Guarani', 600),
	('QAR', 'Qatari Rial', 634),
	('RON', 'Romanian Leu', 946),
	('RSD', 'Serbian Dinar', 941),
	('RUB', 'Russian Ruble', 643),
	('RWF', 'Rwanda Franc', 646),
	('SAR', 'Saudi Riyal', 682),
	('SBD', 'Solomon Islands Dollar', 090),
	('SCR', 'Seychelles Rupee', 690),
	('SDG', 'Sudanese Pound', 938),
	('SEK', 'Swedish Krona', 752),
	('SGD', 'Singapore Dollar', 702),
	('SHP', 'Saint Helena Pound', 654),
	('SLL', 'Leone', 694),
	('SOS', 'Somali Shilling', 706),
	('SRD', 'Surinam Dollar', 968),
	('SSP', 'South Sudanese Pound', 728),
	('STN', 'Dobra', 930),
	('SVC', 'El Salvador Colon', 222),
	('SYP', 'Syrian Pound', 760),
	('SZL', 'Lilangeni', 748),
	('THB', 'Baht', 764),
	('TJS', 'Somoni', 972),
	('TMT', 'Turkmenistan New Manat', 934),
	('TND', 'Tunisian Dinar', 788),
	('TOP', 'Pa’anga', 776),
	('TRY', 'Turkish Lira', 949),
	('TTD', 'Trinidad and Tobago Dollar', 780),
	('TWD', 'New Taiwan Dollar', 901),
	('TZS', 'Tanzanian Shilling', 834),
	('UAH', 'Hryvnia', 980),
	('UGX', 'Uganda Shilling', 800),
	('USD', 'US Dollar', 840),
	('USN', 'US Dollar (Next day)', 997),
	('UYI', 'Uruguay Peso en Unidades Indexadas (UI)', 940),
	('UYU', 'Peso Uruguayo', 858),
	('UYW', 'Unidad Previsional', 927),
	('UZS', 'Uzbekistan Sum', 860),
	('VES', 'Bolívar Soberano', 928),
	('VND', 'Dong', 704),
	('VUV', 'Vatu', 548),
	('WST', 'Tala', 882),
	('XAF', 'CFA Franc BEAC', 950),
	('XAG', 'Silver', 961),
	('XAU', 'Gold', 959),
	('XBA', 'Bond Markets Unit European Composite Unit (EURCO)', 955),
	('XBB', 'Bond Markets Unit European Monetary Unit (E.M.U.-6)', 956),
	('XBC', 'Bond Markets Unit European Unit of Account 9 (E.U.A.-9)', 957),
	('XBD', 'Bond Markets Unit European Unit of Account 17 (E.U.A.-17)', 958),
	('XCD', 'East Caribbean Dollar', 951),
	('XDR', 'SDR (Special Drawing Right)', 960),
	('XOF', 'CFA Franc BCEAO', 952),
	('XPD', 'Palladium', 964),
	('XPF', 'CFP Franc', 953),
	('XPT', 'Platinum', 962),
	('XSU', 'Sucre', 994),
	('XTS', 'Codes specifically reserved for testing purposes', 963),
	('XUA', 'ADB Unit of Account', 965),
	('XXX', 'The codes assigned for transactions where no currency is involved', 999),
	('YER', 'Yemeni Rial', 886),
	('ZAR', 'Rand', 710),
	('ZMW', 'Zambian Kwacha', 967),
	('ZWL', 'Zimbabwe Dollar', 932);
)###";

} /* namespace currency */

} /* namespace table */

} /* namespace db */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DB_LOOKUPTABLES_HPP_ */
