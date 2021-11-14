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
 * @file   JsonExceptions.hpp
 * @author Scott Brauer
 * @date   05-19-2021
 */

#ifndef OFFCENTER_TRADING_COMMON_JSONEXCEPTIONS_HPP_
#define OFFCENTER_TRADING_COMMON_JSONEXCEPTIONS_HPP_

#include <nlohmann/json.hpp>

#include "offcenter/trading/common/Exceptions.hpp"

namespace offcenter {
namespace trading {
namespace common {

/// Trading Json exception
class TradingJsonException: public TradingRuntimeException
{
public:
	explicit TradingJsonException(const std::string& what_arg): TradingRuntimeException(what_arg) {}
	explicit TradingJsonException(const char* what_arg): TradingRuntimeException(what_arg) {}
	TradingJsonException(const nlohmann::json::exception& other) noexcept: TradingRuntimeException(other.what()) {}
};

} /* namespace common */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_COMMON_JSONEXCEPTIONS_HPP_ */
