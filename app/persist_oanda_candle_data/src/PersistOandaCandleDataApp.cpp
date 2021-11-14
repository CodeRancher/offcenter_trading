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
 * @file   PersistOandaCandleDataApp.cpp
 * @author Scott Brauer
 * @date   04-06-2021
 */

#include <iostream>
#include <string>

#include "easylogging++.h"

#include "oanda/v20/endpoint/Account.hpp"
#include "oanda/v20/endpoint/Pricing.hpp"
#include "oanda/v20/instrument/InstrumentDefinitions.hpp"

#include "offcenter/common/InterruptHandler.hpp"
#include "offcenter/trading/persistoandacandledata/PersistOandaCandleDataApp.hpp"
#include "offcenter/trading/db/lookup_tables.hpp"
#include "offcenter/trading/db/data_tables.hpp"
#include "offcenter/trading/db/oanda/oanda_data_tables.hpp"
using namespace offcenter::trading::db::oanda;

#include "offcenter/trading/common/Utility.hpp"

#include "offcenter/common/Utility.hpp"

namespace offcenter {
namespace trading {
namespace persistoandacandledata {

PersistOandaCandleDataApp::PersistOandaCandleDataApp():
		IBasicApp(),
		m_mysqlConfig(),
		m_programConfig(),
		m_oandaEndpoints(),
		m_persistenceEndpoints()
{
}

PersistOandaCandleDataApp::~PersistOandaCandleDataApp() {
	// TODO Auto-generated destructor stub
}

void PersistOandaCandleDataApp::onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager)
{
	m_mysqlConfig = optionsManager.add<offcenter::soci::MySQLProgramOptions>();
	m_programConfig = optionsManager.add<offcenter::trading::persistoandacandledata::PersistOandaCandleDataProgramOptions>();
	m_persistenceManagerConfig = optionsManager.add<offcenter::trading::oandapersistenceclient::PersistenceManagerProgramOptions>();
}

void PersistOandaCandleDataApp::onSetUp()
{
	// Display MySQL Config Options
	LOG(INFO) << "\nProgram Config Options"
				<< "\n\tDatabase Name: " << m_mysqlConfig->dbname()
				<< "\n\tUser: " << m_mysqlConfig->user()
				<< "\n\tPassword: " << ((m_mysqlConfig->password().size() > 0) ? "*" : "")
				<< "\n\tHost: " << m_mysqlConfig->host()
				<< "\n\tPort: " << m_mysqlConfig->port()
				<< "\n\tUnix Socket: " << m_mysqlConfig->unix_socket()
				<< "\n\tsslca: " << m_mysqlConfig->sslca()
				<< "\n\tsslcert: " << m_mysqlConfig->sslcert()
				<< "\n\tLocal Infile: " << m_mysqlConfig->local_infile()
				<< "\n\tCharset: " << m_mysqlConfig->charset()
				<< "\n\tConnect Timeout: " << m_mysqlConfig->connect_timeout()
				<< "\n\tRead Timeout: " << m_mysqlConfig->read_timeout()
				<< "\n\tWrite Timeout: " << m_mysqlConfig->write_timeout();

	// Display Program Config Options
	std::string accessToken = m_programConfig->accessToken();
	if (accessToken.length() > 12) {
		accessToken = accessToken.replace(4, accessToken.length() - 8, "****");
	} else {
		accessToken = accessToken.replace(0, accessToken.length(), "*");
	}
	LOG(INFO) << "\nProgram Config Options"
				<< "\n\tAccess Token: " << accessToken
				<< "\n\tUser Account: " << m_programConfig->userAccount()
				<< "\n\tInstruments: " << offcenter::common::join(m_programConfig->instruments(), ", ")
				<< "\n\tUpdate Instruments: " << (m_programConfig->updateInstruments() ? "true" : "false")
				<< "\n\tfxtrade: " << (m_programConfig->fxtrade() ? "true" : "false")
				<< "\n\ts5: " << (m_programConfig->s5() ? "true" : "false");

	// Initialize AMQP

	// Initialize REST
	endpoint::OandaAuthorization authorization(m_programConfig->accessToken());
	if (m_programConfig->fxtrade()) {
		m_oandaEndpoints = endpoint::OandaEndpoints::factory(endpoint::OandaLiveServer(), authorization);
	} else {
		m_oandaEndpoints = endpoint::OandaEndpoints::factory(endpoint::OandaPracticeServer(), authorization);
	}

	// Initialize DB
	//m_tradingDB.initialize(*m_mysqlConfig);
	// Initialize Persistence Endpoints

	if(m_programConfig->fxtrade()) {
		m_oandaSource = "fxtrade";
	} else {
		m_oandaSource = "fxpractice";
	}

	LOG(INFO) << "\nPersistence Manager Options"
				<< "\n\tScheme: " << m_persistenceManagerConfig->getScheme()
				<< "\n\tUser Info: " << m_persistenceManagerConfig-> getUserInfo()
				<< "\n\tHost: " << m_persistenceManagerConfig->getHost()
				<< "\n\tPort: " << m_persistenceManagerConfig->getPort()
				<< "\n\tPath: " << m_persistenceManagerConfig->getPath()
				<< "\n\tQuery: " << m_persistenceManagerConfig->getQuery()
				<< "\n\tFragment: " << m_persistenceManagerConfig->getFragment()
				<< "\n\tTimeout: " << m_persistenceManagerConfig->getTimeout().count() << "ms"
				<< "\n\tChunksize: " << m_persistenceManagerConfig->getChunksize()
				<< "\n\tURI: " << m_persistenceManagerConfig->getURI().to_string();

	// Initialize Program Manager Options
	m_persistenceEndpoints.setProgramManagerOptions(m_persistenceManagerConfig);
}

void PersistOandaCandleDataApp::onExecute()
{
	try {
		updateInstruments();
	} catch(const std::exception& e) {
		std::cout << "Unable to update instruments: " << e.what() << std::endl;
	}

	try {
		initializeInstruments();
	} catch(const std::exception& e) {
		std::cout << "Unable to initialize instruments: " << e.what() << std::endl;
	}

	try {
		downloadInstrumentData();
		m_processInstrumentsDataThreads.run();
	} catch(const std::exception& e) {
		std::cout << "Unable to setup and download instruments: " << e.what() << std::endl;
	}

	offcenter::common::interrupthandler::waitForUserInterrupt();
	m_processInstrumentsDataThreads.stop();
	m_processInstrumentsDataThreads.join();
}

void PersistOandaCandleDataApp::onTearDown()
{
	std::cout << "onTearDown" << std::endl;
}

/**
 * Display command line help
 */
void PersistOandaCandleDataApp::onHelp(const std::string& help)
{
	std::cout << help << std::endl;
}

void PersistOandaCandleDataApp::onVersion()
{
	std::cout << "onVersion" << std::endl;
}

/**
 * Create a database table
 * Inform the user of the name of the table. Then let the session create the table.
 * @param tableSchema SQL to create table
 */
void PersistOandaCandleDataApp::createTable(const std::string& tableSchema)
{

}

/**
 * Create and populate a database table
 * Inform the user of the name of the table. Then let the session create and populate the table.
 * @param tableSchema SQL to create table
 * @param tableData SQL to populate table
 */
void PersistOandaCandleDataApp::createAndPopulateTable(const std::string& tableSchema, const std::string& tableData)
{

}

void PersistOandaCandleDataApp::updateInstruments()
{
	unsigned instrumentsCount = m_persistenceEndpoints.instrumentsCount("fxpractice");

	LOG(INFO) << "Update Instruments: "
			<< "Instrument Count (" << instrumentsCount << ") "
			<< "Update Instruments (" << (m_programConfig->updateInstruments() ? "true" : "false") << ")";

	if ((instrumentsCount == 0) || (m_programConfig->updateInstruments())) {
		LOG(INFO) << "Updating Instruments";
		endpoint::account::accountinstruments::Request request;
		endpoint::account::accountinstruments::Parameters parameters;
		parameters.accountID = m_programConfig->userAccount();
		m_oandaEndpoints->account.accountInstruments(request, parameters)->sync([&oandaSource=m_oandaSource, &persistenceEndpoints=m_persistenceEndpoints](endpoint::account::accountinstruments::Response instruments) -> void {
			for (oanda::v20::primitives::Instrument& oandaInstrument : instruments.instruments) {
				// Save the Oanda Instrument
				LOG(INFO) << "Instrument Name: " << oandaInstrument.name;
				offcenter::trading::datatypes::oanda::InstrumentWithIDs dbInstrument;

				dbInstrument.instrument_id = 0;
				dbInstrument.name = oandaInstrument.name;

				std::string instrumentType;
				oanda::v20::primitives::to_string(oandaInstrument.type, instrumentType);
				dbInstrument.instrument_type_id = persistenceEndpoints.instrumentType()->recordByName(instrumentType).instrument_type_id;

				dbInstrument.display_name = oandaInstrument.displayName;
				dbInstrument.pip_location = oandaInstrument.pipLocation;
				dbInstrument.display_precision = oandaInstrument.displayPrecision;
				dbInstrument.trade_units_precision = oandaInstrument.tradeUnitsPrecision;
				dbInstrument.minimum_trade_size = oandaInstrument.minimumTradeSize.asDouble(0.0);
				dbInstrument.maximum_trailing_stop_distance = oandaInstrument.maximumTrailingStopDistance.asDouble(0.0);
				dbInstrument.minimum_guaranteed_stop_loss_distance = oandaInstrument.minimumGuaranteedStopLossDistance.asDouble(0.0);
				dbInstrument.minimum_trailing_stop_distance = oandaInstrument.minimumTrailingStopDistance.asDouble(0.0);
				dbInstrument.maximum_position_size = oandaInstrument.maximumPositionSize.asDouble(0.0);
				dbInstrument.maximum_order_units = oandaInstrument.maximumOrderUnits.asDouble(0.0);
				dbInstrument.margin_rate = oandaInstrument.marginRate.asDouble(0.0);
				dbInstrument.commission_commission = oandaInstrument.commission.commission.asDouble(0.0);
				dbInstrument.commission_units_traded = oandaInstrument.commission.unitsTraded.asDouble(0.0);
				dbInstrument.commission_minimum_commission = oandaInstrument.commission.minimumCommission.asDouble(0.0);

				std::string guaranteedStopLossOrderModeForInstrument;
				oanda::v20::primitives::to_string(oandaInstrument.guaranteedStopLossOrderMode, guaranteedStopLossOrderModeForInstrument);
				dbInstrument.guaranteed_stop_loss_order_mode =
						persistenceEndpoints.guaranteedStopLossOrderModeForInstrument()->recordByName(guaranteedStopLossOrderModeForInstrument).guaranteed_stop_loss_order_mode_for_instrument_id;

				dbInstrument.guaranteed_stop_loss_order_execution_premium = oandaInstrument.guaranteedStopLossOrderExecutionPremium.asDouble(0.0);
				dbInstrument.guaranteed_stop_loss_order_level_restriction_volume = oandaInstrument.guaranteedStopLossOrderLevelRestriction.volume.asDouble(0.0);
				dbInstrument.guaranteed_stop_loss_order_level_restriction_priceRange = oandaInstrument.guaranteedStopLossOrderLevelRestriction.priceRange.asDouble(0.0);
				dbInstrument.financing_longRate = oandaInstrument.financing.longRate.asDouble(0.0);
				dbInstrument.financing_shortRate= oandaInstrument.financing.shortRate.asDouble(0.0);

				offcenter::trading::datatypes::oanda::FinancingDayOfWeek financingDayOfWeek;
				for (oanda::v20::primitives::FinancingDayOfWeek oandaFinancingDaysOfWeek : oandaInstrument.financing.financingDaysOfWeek) {
					std::string financingDaysOfWeek;
					oanda::v20::primitives::to_string(oandaFinancingDaysOfWeek.dayOfWeek, financingDaysOfWeek);
					financingDayOfWeek.day_of_week_id = persistenceEndpoints.dayOfWeek()->recordByName(financingDaysOfWeek).day_of_week_id;
					financingDayOfWeek.days_charged = oandaFinancingDaysOfWeek.daysCharged;
					dbInstrument.financingDaysOfWeek.push_back(financingDayOfWeek);
				}

				LOG(INFO) << "Update Oanda Instrument: " << dbInstrument.name << ", " << dbInstrument.display_name;

				persistenceEndpoints.oandaInstrumentCreate(oandaSource, dbInstrument);

				// Save the basic Instrument
				offcenter::trading::datatypes::Instrument basicInstrument;
				basicInstrument.instrument_id = 0;
				basicInstrument.name = oandaInstrument.name;
				basicInstrument.display_name = oandaInstrument.displayName;
				persistenceEndpoints.instrumentCreate(oandaSource, basicInstrument);
			}
		});
	}
}

void PersistOandaCandleDataApp::initializeInstruments()
{
	LOG(INFO) << "Initialize Instruments";
	for (std::string instrument : m_programConfig->instruments()) {
		LOG(INFO) << "Initialize Instrument: " << offcenter::trading::common::normalizeCurrencyPair(instrument);

		offcenter::trading::datatypes::CandlestickDataSeriesByName candlestickDataSeries;
		candlestickDataSeries.candlestick_data_series_id = 0;
		candlestickDataSeries.instrument_name = instrument;
		candlestickDataSeries.broker_name = m_programConfig->broker();
		candlestickDataSeries.broker_data_source_name = m_programConfig->brokerServer();
		candlestickDataSeries.candlestick_granularity_name = m_programConfig->granularity();

		m_persistenceEndpoints.candlestickDataSeriesCreate(m_oandaSource, candlestickDataSeries);
	}
}

// Loop through each currency pair and timeframe
	// Get first and last record in DB
	// Read a block of records
	// Loop through each record
		// Write record to DB
	// Get first and last record in DB
	// Send AMQP message with currency pair, timeframe, start record time, end record time
	// If number of records read = block size
		// Begin process for next time period
	// If number of records read < block size
		// Start processing stream
void PersistOandaCandleDataApp::downloadInstrumentData()
{
	LOG(INFO) << "Download Instrument Data";
	for (std::string instrument : m_programConfig->instruments()) {
		const offcenter::trading::datatypes::CandlestickDataSeriesComplete candlestickDataSeriesRead(const std::string& source, unsigned candlestick_data_series_id);
		LOG(INFO) << "Download Instrument Data: " << offcenter::trading::common::normalizeCurrencyPair(instrument);

		m_processInstrumentsDataThreads.add(std::make_unique<offcenter::trading::oandapersistenceclient::ProcessInstrumentDataThread>(
				m_programConfig->broker(),
				m_programConfig->brokerServer(),
				instrument,
				m_programConfig->granularity(),
				m_programConfig->userAccount(),
				m_programConfig->oandaRecords(),
				m_persistenceEndpoints,
				m_oandaEndpoints)
		);
	}
}

} /* namespace persistoandacandledata */
} /* namespace trading */
} /* namespace offcenter */
