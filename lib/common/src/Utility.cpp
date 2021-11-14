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
 * @file   Utility.cpp
 * @author Scott Brauer
 * @date   04-07-2021
 */
#include "offcenter/trading/common/Utility.hpp"

namespace offcenter {
namespace trading {
namespace common {

std::string normalizeCurrencyPair(const std::string& currencyPair)
{
	std::string normalizedCurrencyPair = currencyPair;

	// TODO Check for invalid lenghts
	if (normalizedCurrencyPair.length() == 6) {
		normalizedCurrencyPair.insert(3, "_");
	} else {
		normalizedCurrencyPair.replace(3, 1, "_");
	}

	return normalizedCurrencyPair;
}

} /* namespace common */
} /* namespace trading */
} /* namespace offcenter */
