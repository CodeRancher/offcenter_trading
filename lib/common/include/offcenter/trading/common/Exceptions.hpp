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
 * @file   Exceptions.hpp
 * @author Scott Brauer
 * @date   05-19-2021
 */

#ifndef OFFCENTER_TRADING_COMMON_EXCEPTIONS_HPP_
#define OFFCENTER_TRADING_COMMON_EXCEPTIONS_HPP_

#include <string>
#include <stdexcept>

namespace offcenter {
namespace trading {
namespace common {

/// Trading runtime exception
class TradingRuntimeException: public std::runtime_error
{
public:
	explicit TradingRuntimeException(const std::string& what_arg): runtime_error(what_arg) {}
	explicit TradingRuntimeException(const char* what_arg): runtime_error(what_arg) {}
	TradingRuntimeException(const std::runtime_error& other) noexcept: runtime_error(other) {}
};

/// Empty Recordset runtime exception
class EmptyRecordset: public TradingRuntimeException
{
public:
	explicit EmptyRecordset(const std::string& tableName, const std::string& what_arg):
			TradingRuntimeException("Table " + tableName + " is empty. " + what_arg) {}

	explicit EmptyRecordset(const std::string& what_arg): TradingRuntimeException(what_arg) {}
	explicit EmptyRecordset(const char* what_arg): TradingRuntimeException(what_arg) {}
	EmptyRecordset(const std::runtime_error& other) noexcept: TradingRuntimeException(other) {}
};

/// Duplicate Record runtime exception
class DuplicateRecord: public TradingRuntimeException
{
public:
	explicit DuplicateRecord(const std::string& what_arg): TradingRuntimeException(what_arg) {}
	explicit DuplicateRecord(const char* what_arg): TradingRuntimeException(what_arg) {}
	DuplicateRecord(const std::runtime_error& other) noexcept: TradingRuntimeException(other) {}
};

/**
 * Invalid initialization of data element
 */
class InvalidInitialization: public TradingRuntimeException
{
public:
	explicit InvalidInitialization(const std::string& what_arg): TradingRuntimeException(what_arg) {}
	explicit InvalidInitialization(const char* what_arg): TradingRuntimeException(what_arg) {}
	InvalidInitialization(const std::runtime_error& other) noexcept: TradingRuntimeException(other) {}
};

} /* namespace common */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_COMMON_EXCEPTIONS_HPP_ */
