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
 * @file   Broker.cpp
 * @author Scott Brauer
 * @date   05-10-2021
 */
#include "offcenter/trading/datatypes/Broker.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

Broker::Broker():
		m_id(""),
		m_name(""),
		m_description("")
{}

Broker::Broker(const std::string& id, const std::string& name, const std::string& description):
		m_id(id),
		m_name(name),
		m_description(description)
{}

Broker::~Broker()
{}

void Broker::set(const std::string& id, const std::string& name, const std::string& description)
{
	m_id = id;
	m_name = name;
	m_description = description;
}

void to_cmsMessage(Broker::CMSMessageType* j, const Broker &p)
{
	j->setString(p.id_key, p.m_id);
	j->setString(p.name_key, p.m_name);
	j->setString(p.description_key, p.m_description);
}

void from_cmsMessage(const Broker::CMSMessageType* j, Broker &p)
{
	p.set(
		j->getString(p.id_key),
		j->getString(p.name_key),
		j->getString(p.description_key));
}

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */
