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
 * @file   Topics.hpp
 * @author Scott Brauer
 * @date   10-24-2021
 */

#ifndef OFFCENTER_TRADING_AMQP_TOPICS_HPP_
#define OFFCENTER_TRADING_AMQP_TOPICS_HPP_

#include <string>

namespace offcenter {
namespace trading {
namespace amqp {
namespace topic {

const std::string offcenterTrading();

const std::string broker(const std::string& broker);
const std::string brokerServer(const std::string& broker, const std::string& server);
const std::string instrument(const std::string& broker, const std::string& server, const std::string& instrument);
const std::string instrumentGranularity(const std::string& broker, const std::string& server, const std::string& instrument, const std::string& granularity);

const std::string signalCandleRange(const std::string& broker, const std::string& server, const std::string& instrument, const std::string& granularity);
const std::string processInstrumentGranularity(const std::string& broker, const std::string& server, const std::string& instrument, const std::string& granularity);

} /* namespace topic */
} /* namespace amqp */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_AMQP_TOPICS_HPP_ */
