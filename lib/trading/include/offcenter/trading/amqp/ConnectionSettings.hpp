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
 * @file   ConnectionSettings.hpp
 * @author Scott Brauer
 * @date   05-10-2021
 */

#ifndef OFFCENTER_TRADING_AMQP_CONNECTIONSETTINGS_HPP_
#define OFFCENTER_TRADING_AMQP_CONNECTIONSETTINGS_HPP_

#include <string>
#include <utility>
#include <initializer_list>

#include "offcenter/common/amqp/ConnectionSettings.hpp"

namespace offcenter {
namespace trading {
namespace amqp {

/**
 *
 */
class ConnectionSettings: public offcenter::common::amqp::ConnectionSettings
{
public:
	explicit ConnectionSettings(const std::string& queueName = "", offcenter::common::amqp::ConnectionSettings::QueueParameters queueParameters = {}):
			offcenter::common::amqp::ConnectionSettings(cms::Session::AcknowledgeMode::AUTO_ACKNOWLEDGE, QueueType::Queue, "offcenter.trade." + queueName, queueParameters)
	{}

	virtual ~ConnectionSettings() = default;
};

} /* namespace amqp */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_AMQP_CONNECTIONSETTINGS_HPP_ */
