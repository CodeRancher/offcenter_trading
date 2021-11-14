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
 * @file   BaseProducer.hpp
 * @author Scott Brauer
 * @date   05-10-2021
 */
#ifndef OFFCENTER_TRADING_AMQP_BASEPRODUCER_HPP_
#define OFFCENTER_TRADING_AMQP_BASEPRODUCER_HPP_

#include "offcenter/trading/amqp/ConnectionSettings.hpp"
#include "offcenter/amqp/Helper.hpp"
#include "offcenter/amqp/SessionProducer.hpp"
#include "offcenter/amqp/SessionConsumer.hpp"
#include "offcenter/amqp/MessageCallback.hpp"

namespace offcenter {
namespace trading {
namespace amqp {

/**
 *
 */
class AMQPCommon
{
public:
	explicit AMQPCommon(const std::string& name, offcenter::amqp::ConnectionSettings::QueueParameters queueParameters = {}):
			m_connectionSettings(name)
	{}

	virtual ~AMQPCommon() = default;

protected:
	offcenter::trading::amqp::ConnectionSettings m_connectionSettings;
};

/**
 *
 */
class AMQPProducer : public AMQPCommon
{
public:
	explicit AMQPProducer(offcenter::amqp::ConnectionPtr connection, const std::string& name, offcenter::amqp::ConnectionSettings::QueueParameters queueParameters = {}):
			AMQPCommon(name, queueParameters),
			m_sessionProducer(connection, m_connectionSettings)
	{}

	virtual ~AMQPProducer() = default;

protected:
	offcenter::amqp::SessionProducer m_sessionProducer;

};

/**
 *
 */
template <class MESSAGETYPE, class CMSMESSAGETYPE>
class AMQPConsumer : public AMQPCommon, public cms::MessageListener
{
private:
	using MessageCallback = offcenter::amqp::MessageCallback<CMSMESSAGETYPE, MESSAGETYPE>;

public:
	template <typename TCallback>
	explicit AMQPConsumer(offcenter::amqp::ConnectionPtr connection, const std::string& name, TCallback&& callback, offcenter::amqp::ConnectionSettings::QueueParameters queueParameters = {}):
			AMQPCommon(name, queueParameters),
			cms::MessageListener(),
			m_callback(MessageCallback::factory(std::forward<TCallback>(callback))),
			m_sessionConsumer(connection, m_connectionSettings)
	{
		m_sessionConsumer.consumer(this);
	}

	virtual ~AMQPConsumer() = default;

private:
	/**
	 * Callback method with listener messages
	 *
	 * @param message CMS Message
	 */
	void onMessage(const cms::Message* message) override {
		try {
			m_callback.callback(message);
		} catch(std::runtime_error& e) {
			LOG(ERROR) << e.what();
		}
	}

protected:
	offcenter::amqp::SessionConsumer m_sessionConsumer;
	MessageCallback m_callback;

};

} /* namespace amqp */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_AMQP_BASEPRODUCER_HPP_ */
