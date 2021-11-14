/**
 * Copyright 2020 Scott Brauer
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

/*
 * @file   JsonConversion.cpp
 * @author Scott Brauer
 * @date   12-16-2020
 */

#include <iostream>
#include <type_traits>
#include <typeinfo>

#include "offcenter/trading/common/JsonConversion.hpp"

#include "../../data_types/include/offcenter/trading/datatypes/common/ForexDateTime.hpp"
#include "offcenter/trading/common/JsonExceptions.hpp"

namespace offcenter {
namespace trading {
namespace common {


template <>
void convertJson<std::string>(const nlohmann::json& j, const std::string& key, std::string& value)
{
	try {
		auto iter = j.find(key);
		if (iter != j.end()) {
			// If value is int, throw error because primitive int doesn't handle null
			if ((*iter).is_null()) {
				std::ostringstream ss;
				ss << "Json conversion of NULL not handled (" << key << ")";

				LOG(ERROR) << ss.str();

				throw offcenter::trading::common::InvalidJsonConversionException(ss.str());
			}

			value = *iter;
		} else {
			value = "";
		}
	} catch(nlohmann::json::exception& e) {
		std::ostringstream ss;
		ss << e.what() << std::endl << "Value for (" << key << ") defaults to \"\"";
		LOG(ERROR) << ss.str();
		value = "";
	}
}

template <>
void convertJson<int>(const nlohmann::json& j, const std::string& key, int& value)
{
	try {
		auto iter = j.find(key);
		if (iter != j.end()) {
			// If value is int, throw error because primitive int doesn't handle null
			if ((*iter).is_null()) {
				std::ostringstream ss;
				ss << "Json conversion of NULL not handled (" << key << ")";

				LOG(ERROR) << ss.str();

				throw offcenter::trading::common::InvalidJsonConversionException(ss.str());
			}

			value = *iter;
		} else {
			value = 0;
		}
	} catch(nlohmann::json::exception& e) {
		std::ostringstream ss;
		ss << e.what() << std::endl << "Value for (" << key << ") defaults to 0";
		LOG(ERROR) << ss.str();
		value = 0;
	}
}

template <>
void convertJson<unsigned int>(const nlohmann::json& j, const std::string& key, unsigned int& value)
{
	try {
		auto iter = j.find(key);
		if (iter != j.end()) {
			// If value is int, throw error because primitive int doesn't handle null
			if ((*iter).is_null()) {
				std::ostringstream ss;
				ss << "Json conversion of NULL not handled (" << key << ")";

				LOG(ERROR) << ss.str();

				throw offcenter::trading::common::InvalidJsonConversionException(ss.str());
			}

			value = *iter;
		} else {
			value = 0;
		}
	} catch(nlohmann::json::exception& e) {
		std::ostringstream ss;
		ss << e.what() << std::endl << "Value for (" << key << ") defaults to 0";
		LOG(ERROR) << ss.str();
		value = 0;
	}
}

template <>
void convertJson<bool>(const nlohmann::json& j, const std::string& key, bool& value)
{
	try {
		auto iter = j.find(key);
		if (iter != j.end()) {
			// If value is bool, throw error because primitive bool doesn't handle null
			if ((*iter).is_null()) {
				std::ostringstream ss;
				ss << "Json conversion of NULL not handled (" << key << ")";

				LOG(ERROR) << ss.str();

				throw offcenter::trading::common::InvalidJsonConversionException(ss.str());
			}

			value = *iter;
		} else {
			value = false;
		}
	} catch(nlohmann::json::exception& e) {
		std::ostringstream ss;
		ss << e.what() << std::endl << "Value for (" << key << ") defaults to false";
		LOG(ERROR) << ss.str();
		value = false;
	}
}

template <>
void convertJson<double>(const nlohmann::json& j, const std::string& key, double& value)
{
	try {
		auto iter = j.find(key);
		if (iter != j.end()) {
			// If value is int, throw error because primitive int doesn't handle null
			if ((*iter).is_null()) {
				std::ostringstream ss;
				ss << "Json conversion of NULL not handled (" << key << ")";

				LOG(ERROR) << ss.str();

				throw offcenter::trading::common::InvalidJsonConversionException(ss.str());
			}

			value = *iter;
		} else {
			value = 0;
		}
	} catch(nlohmann::json::exception& e) {
		std::ostringstream ss;
		ss << e.what() << std::endl << "Value for (" << key << ") defaults to 0";
		LOG(ERROR) << ss.str();
		value = 0;
	}
}

template <>
void convertJson<offcenter::common::UTCDateTime>(const nlohmann::json& j, const std::string& key, offcenter::common::UTCDateTime& value)
{
	try {
		std::string tmpTime;
		convertJson(j, key, tmpTime);
		value = offcenter::common::make_UTCDateTimeFromISO8601(tmpTime);
	} catch(std::exception& e) {
		std::ostringstream ss;
		ss << "Json conversion of UTDDateTime not handled (" << key << "): " << e.what();
		LOG(ERROR) << ss.str();
		throw offcenter::trading::common::InvalidJsonConversionException(ss.str());
	}
}

} /* namespace common */
} /* namespace trading */
} /* namespace offcenter */
