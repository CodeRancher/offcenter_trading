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
 * @file   Common.hpp
 * @author Scott Brauer
 * @date   05-29-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_COMMON_HPP_
#define OFFCENTER_TRADING_DATATYPES_COMMON_HPP_

#include <string>

namespace offcenter {
namespace trading {
namespace datatypes {
namespace common {

/**
 *
 */
struct CountRecords
{
public:
	CountRecords():
		recordCount(0),
		success(true),
		errorMessage("")
	{}

	CountRecords(unsigned int l_recordCount, bool l_success = true, std::string l_errorMessage = ""):
		recordCount(l_recordCount),
		success(l_success),
		errorMessage(l_errorMessage)
	{}

	std::string message() { return std::to_string(recordCount) + ":" + errorMessage; }

	unsigned int recordCount;
	bool success;
	std::string errorMessage;
};

/**
 *
 */
struct DeleteRecord
{
	DeleteRecord():
		name(""),
		success(true),
		errorMessage("")
	{}

	DeleteRecord(std::string l_name, bool l_success = true, std::string l_errorMessage = ""):
		name(l_name),
		success(l_success),
		errorMessage(l_errorMessage)
	{}

	std::string message() { return name + ":" + errorMessage; }

	std::string name;
	bool success;
	std::string errorMessage;
};

/**
 *
 */
struct CreateRecord
{
	CreateRecord():
		name(""),
		success(true),
		errorMessage("")
	{}

	CreateRecord(std::string l_name, bool l_success = true, std::string l_errorMessage = ""):
		name(l_name),
		success(l_success),
		errorMessage(l_errorMessage)
	{}

	std::string message() { return name + ":" + errorMessage; }

	std::string name;
	bool success;
	std::string errorMessage;
};

/**
 *
 */
struct ReadRecordError
{
	ReadRecordError():
		name(""),
		errorMessage("")
	{}

	ReadRecordError(std::string l_name, std::string l_errorMessage = ""):
		name(l_name),
		errorMessage(l_errorMessage)
	{}

	std::string message() { return name + ":" + errorMessage; }

	std::string name;
	std::string errorMessage;
};


} /* namespace common */
} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_COMMON_HPP_ */
