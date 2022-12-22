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
 * @file   GenerateSineCandlesticksExampleProgramOptions.hpp
 * @author Scott Brauer
 * @date   12-03-2021
 */
#ifndef GENERATESINECANDLESTICKSEXAMPLEPROGRAMOPTIONS_HPP_
#define GENERATESINECANDLESTICKSEXAMPLEPROGRAMOPTIONS_HPP_

#include <functional>

#include <boost/bind/bind.hpp>

#include "GenerateSineCandlesticksExampleOptions.hpp"
#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"


class GenerateSineCandlesticksExampleProgramOptions:
		public offcenter::common::program_options::ProgramOptionsGroup<GenerateSineCandlesticksExampleOptions>
{
public:
	GenerateSineCandlesticksExampleProgramOptions():
		ProgramOptionsGroup("AMQP")
	{
		optionsDescription().add_options()
				("AMQP.tcpHost", po::value<std::string>(&optionConfig().m_tcpHost)->default_value("localhost"), "Active MQ Server")
				("AMQP.connectionSendTimeout", po::value<int>(&optionConfig().m_connectionSendTimeout)->default_value(1000), "connection.sendTimeout")
				("AMQP.failoverTransportTimeout", po::value<int>(&optionConfig().m_failoverTransportTimeout)->default_value(1000), "failoverTransport.timeout")
				;
	}

	virtual ~GenerateSineCandlesticksExampleProgramOptions() = default;
};

#endif /* GENERATESINECANDLESTICKSEXAMPLEPROGRAMOPTIONS_HPP_ */
