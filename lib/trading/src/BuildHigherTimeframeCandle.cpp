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
 * @file   BuildHigherTimeframeCandle.cpp
 * @author Scott Brauer
 * @date   11-02-2021
 */

#include "offcenter/trading/amqp/BuildHigherTimeframeCandle.hpp"

#include "offcenter/trading/amqp/Topics.hpp"

namespace offcenter {
namespace trading {
namespace amqp {

BuildHigherTimeframeCandle::BuildHigherTimeframeCandle(
        offcenter::common::amqp::SessionPtr session,
        const std::string &broker,
        const std::string &server,
        const std::string &instrument,
        const std::string &granularity
	):
		ProcessAmqpMessageThread(session, offcenter::trading::amqp::topic::processInstrumentGranularity(broker, server, instrument, granularity)),
		m_broker(broker),
		m_server(server),
		m_instrument(instrument),
		m_granularity(granularity)
{
}

BuildHigherTimeframeCandle::~BuildHigherTimeframeCandle()
{
	// TODO Auto-generated destructor stub
}

void BuildHigherTimeframeCandle::onNewData()
{
	unblock();
}

void BuildHigherTimeframeCandle::task()
{
	LOG(INFO) << "task: "
				<< m_broker << "."
				<< m_server << "."
				<< m_instrument << "."
				<< m_granularity << " "
				<< offcenter::common::UTCDateTimeToISO8601(data().start_time);

	std::cout << "task: "
				<< m_broker << "."
				<< m_server << "."
				<< m_instrument << "."
				<< m_granularity << " "
				<< offcenter::common::UTCDateTimeToISO8601(data().start_time) << std::endl;

	block();
}

void BuildHigherTimeframeCandle::stopped()
{
}

} /* namespace amqp */
} /* namespace trading */
} /* namespace offcenter */
