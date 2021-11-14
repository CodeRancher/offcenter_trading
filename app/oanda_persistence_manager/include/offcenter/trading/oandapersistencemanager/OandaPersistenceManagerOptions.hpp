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
 * @file   OandaPersistenceManagerOptions.hpp
 * @author Scott Brauer
 * @date   05-18-2021
 */
#ifndef OFFCENTER_TRADING_OANDAPERSISTENCEMANAGER_OANDAPERSISTENCEMANAGEROPTIONS_HPP_
#define OFFCENTER_TRADING_OANDAPERSISTENCEMANAGER_OANDAPERSISTENCEMANAGEROPTIONS_HPP_

#include <string>

namespace offcenter {
namespace trading {
namespace oandapersistencemanager {

class OandaPersistenceManagerOptions
{
public:
	explicit OandaPersistenceManagerOptions():
		m_urlBase(""),
		m_broker("")
	{}

	virtual ~OandaPersistenceManagerOptions() {}

	std::string urlBase() { return m_urlBase; }
	std::string broker() { return m_broker; }

	friend class OandaPersistenceManagerProgramOptions;

private:
	std::string m_urlBase;
	std::string m_broker;
};

} /* namespace oandapersistencemanager */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_OANDAPERSISTENCEMANAGER_OANDAPERSISTENCEMANAGEROPTIONS_HPP_ */
