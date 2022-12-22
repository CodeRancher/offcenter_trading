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
 * @file   BuildHigherTimeframeCandle.hpp
 * @author Scott Brauer
 * @date   11-02-2021
 */

#ifndef OFFCENTER_TRADING_AMQP_BUILDHIGHERTIMEFRAMECANDLE_HPP_
#define OFFCENTER_TRADING_AMQP_BUILDHIGHERTIMEFRAMECANDLE_HPP_

#include "offcenter/common/amqp/threading/ProcessAmqpMessageThread.hpp"
#include "offcenter/trading/datatypes/CandlestickDataAmqp.hpp"

namespace offcenter {
namespace trading {
namespace amqp {

/**
 *
 */
class BuildHigherTimeframeCandle:
		public offcenter::common::amqp::threading::ProcessAmqpMessageThread<
			offcenter::trading::datatypes::CandlestickDataAmqp,
			offcenter::trading::datatypes::CandlestickDataAmqp::MessageType>
{
public:
	BuildHigherTimeframeCandle() = delete;
	explicit BuildHigherTimeframeCandle(
			offcenter::common::amqp::SessionPtr session,
			const std::string& broker,
			const std::string& server,
			const std::string& instrument,
			const std::string& granularity);
	virtual ~BuildHigherTimeframeCandle();

protected:
	void onNewData() override;
	void task() override;
	void stopped() override;

private:
    const std::string m_broker;
    const std::string m_server;
    const std::string m_instrument;
    const std::string m_granularity;

};

} /* namespace amqp */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_AMQP_BUILDHIGHERTIMEFRAMECANDLE_HPP_ */
