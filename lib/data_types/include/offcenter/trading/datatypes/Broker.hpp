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
 * @file   Broker.hpp
 * @author Scott Brauer
 * @date   05-10-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_BROKER_HPP_
#define OFFCENTER_TRADING_DATATYPES_BROKER_HPP_

#include <string>

#include "offcenter/amqp/Helper.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {


/**
 *
 */
class Broker
{
public:
	explicit Broker();
	explicit Broker(const std::string& id, const std::string& name, const std::string& description);
	virtual ~Broker();

	void set(const std::string& id, const std::string& name, const std::string& description);

	using CMSMessageType = cms::MapMessage;

private:
	std::string m_id;
	std::string m_name;
	std::string m_description;

	static inline std::string const id_key = "id";
	static inline std::string const name_key = "name";
	static inline std::string const description_key = "description";

	friend void to_cmsMessage(Broker::CMSMessageType* j, const Broker& p);
	friend void from_cmsMessage(const Broker::CMSMessageType* j, Broker& p);
};

void to_cmsMessage(Broker::CMSMessageType* j, const Broker& p);
void from_cmsMessage(const Broker::CMSMessageType* j, Broker& p);

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_BROKER_HPP_ */
