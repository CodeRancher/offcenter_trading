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
 * @file   ProcessCandlestickHierarchyOptions.hpp
 * @author Scott Brauer
 * @date   11-01-2021
 */

#ifndef OFFCENTER_TRADING_PROCESSCANDLESTICKHIERARCHY_PROCESSCANDLESTICKHIERARCHYOPTIONS_H_
#define OFFCENTER_TRADING_PROCESSCANDLESTICKHIERARCHY_PROCESSCANDLESTICKHIERARCHYOPTIONS_H_

#include <string>
#include <vector>

namespace offcenter {
namespace trading {
namespace processcandlestickhierarchy {

class ProcessCandlestickHierarchyOptions
{
public:
	explicit ProcessCandlestickHierarchyOptions():
		m_broker(),
		m_fxtrade(false),
		m_instruments(),
		m_granularity()
	{}

	virtual ~ProcessCandlestickHierarchyOptions() {}

	const std::string broker() { return m_broker; }
	const std::string brokerServer() const { return m_fxtrade ? "fxtrade" : "fxpractice"; }
	bool fxtrade() { return m_fxtrade; }
	const std::vector<std::string>& instruments() { return m_instruments; }
	const std::string granularity() { return m_granularity; }

	friend class ProcessCandlestickHierarchyProgramOptions;

private:
	std::string m_broker;
	bool m_fxtrade;
	std::vector<std::string> m_instruments;
	std::string m_granularity;
};

} /* namespace processcandlestickhierarchy */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_PROCESSCANDLESTICKHIERARCHY_PROCESSCANDLESTICKHIERARCHYOPTIONS_H_ */
