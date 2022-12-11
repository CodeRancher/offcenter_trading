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
 * @file   BrokerProducer.hpp
 * @author Scott Brauer
 * @date   05-10-2021
 */

#ifndef OFFCENTER_TRADING_AMQP_BROKERPRODUCER_HPP_
#define OFFCENTER_TRADING_AMQP_BROKERPRODUCER_HPP_

#include "offcenter/trading/amqp/BaseAMQP.hpp"
#include "offcenter/common/amqp/Helper.hpp"
#include "offcenter/trading/datatypes/Broker.hpp"

namespace offcenter {
namespace trading {
namespace amqp {

inline constexpr char g_broker[] {"add.broker.{broker_id}"};

/**
 *
 */
class BrokerProducer: public AMQPProducer
{
public:
	explicit BrokerProducer(offcenter::amqp::ConnectionPtr connection, offcenter::amqp::ConnectionSettings::QueueParameters queueParameters = {}):
			AMQPProducer(connection, g_broker, queueParameters)
	{}

	virtual ~BrokerProducer() = default;

	void send(const offcenter::trading::datatypes::Broker& broker) {
		m_sessionProducer.send<offcenter::trading::datatypes::Broker::CMSMessageType>(broker);
	}

};

/**
 *
 */
template <typename CALLBACK>
class BrokerConsumer:
		public AMQPConsumer<offcenter::trading::datatypes::Broker, offcenter::trading::datatypes::Broker::CMSMessageType>
{
public:
	explicit BrokerConsumer(offcenter::amqp::ConnectionPtr connection, CALLBACK callback, offcenter::amqp::ConnectionSettings::QueueParameters queueParameters = {}):
			AMQPConsumer(connection, g_broker, queueParameters)
	{}

	virtual ~BrokerConsumer() = default;

	void onMessage(const offcenter::trading::datatypes::Broker& message) override {
		m_callback(message);
	}

private:
	CALLBACK m_callback;

};

} /* namespace amqp */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_AMQP_BROKERPRODUCER_HPP_ */
