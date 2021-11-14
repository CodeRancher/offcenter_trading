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
 * @file   Exceptions.hpp
 * @author Scott Brauer
 * @date   05-20-2021
 */

#ifndef OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_EXCEPTIONS_HPP_
#define OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_EXCEPTIONS_HPP_

#include <cpprest/http_msg.h>

#include "offcenter/trading/common/Exceptions.hpp"

namespace offcenter {
namespace trading {
namespace oandapersistenceclient {

/// Oanda Persistence Client Exception
class OandaPersistenceClientException: public offcenter::trading::common::TradingRuntimeException
{
public:
	explicit OandaPersistenceClientException(const std::string& what_arg): TradingRuntimeException(what_arg) {}
	explicit OandaPersistenceClientException(const char* what_arg): TradingRuntimeException(what_arg) {}
};

/// Oanda Persistence Client Exception
class HttpResponseException: public offcenter::trading::common::TradingRuntimeException
{
public:
	explicit HttpResponseException(const std::string& what_arg, web::http::status_code statusCode):
		TradingRuntimeException(what_arg),
		m_statusCode(statusCode)
	{}

	explicit HttpResponseException(const char* what_arg, web::http::status_code statusCode):
		TradingRuntimeException(what_arg),
		m_statusCode(statusCode)
	{}

	web::http::status_code statusCode() { return m_statusCode; }

private:
	web::http::status_code m_statusCode;
};

} /* namespace oandapersistenceclient */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_EXCEPTIONS_HPP_ */
