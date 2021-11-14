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
 * @file   SOCIMySQLConnectionOptions.hpp
 * @author Scott Brauer
 * @date   03-20-2021
 */
#ifndef OFFCENTER_TRADING_DB_SOCIMYSQLCONNECTIONOPTIONS_HPP_
#define OFFCENTER_TRADING_DB_SOCIMYSQLCONNECTIONOPTIONS_HPP_

#include <string>
#include <climits>
#include <stdexcept>

namespace offcenter {
namespace trading {
namespace db {

class SOCIMySQLConnectionOptions
{

	class Option {
	private:
		bool m_isDirty;
		const std::string m_name;
		std::string m_value;
	public:
		explicit Option(const std::string& name):
			m_isDirty(false),
			m_name(name),
			m_value("") {}
		bool isDirty() const { return m_isDirty; }
		const std::string operator()() const { return m_value; }
		void operator()(const std::string value) { m_value = value; m_isDirty = true; }
		const std::string optionString() const {
			if (m_isDirty) {
				return m_name + "=" + m_value;
			} else {
				return "";
			}
		}
	};

	template <int MIN, int MAX>
	class IntOption: public Option {
	public:
		explicit IntOption(const std::string& name):
				Option(name) {}
		int operator()() const {
			if (isDirty()) {
				return std::stoi(Option::operator()());
			} else {
				return -1;
			}
		}
		void operator()(int value) {
			if ((value < MIN) || (value > MAX)) {
				throw std::runtime_error("Setting option is out of range: " + std::to_string(MIN) + "<=" + std::to_string(value) + "<=" + std::to_string(MAX));
			}
			Option::operator()(std::to_string(value));
		}
	};

public:
	explicit SOCIMySQLConnectionOptions();
	explicit SOCIMySQLConnectionOptions(const std::string& host, const std::string& dbname, const std::string& user, const std::string& password);
	virtual ~SOCIMySQLConnectionOptions();

	const std::string getConnectionString() const;

	Option dbname;
	Option user;
	Option password;
	Option host;
	Option port;
	Option unix_socket;
	Option sslca;
	Option sslcert;
	// local_infile - should be 0 or 1, 1 means MYSQL_OPT_LOCAL_INFILE will be set.
	IntOption<0,1> local_infile;
	Option charset;
	// connect_timeout - should be positive integer value that means seconds corresponding to MYSQL_OPT_CONNECT_TIMEOUT.
	IntOption<1,INT_MAX> connect_timeout;
	// read_timeout - should be positive integer value that means seconds corresponding to MYSQL_OPT_READ_TIMEOUT.
	IntOption<1,INT_MAX> read_timeout;
	// write_timeout - should be positive integer value that means seconds corresponding to MYSQL_OPT_WRITE_TIMEOUT.
	IntOption<1,INT_MAX> write_timeout;
};

} /* namespace db */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DB_SOCIMYSQLCONNECTIONOPTIONS_HPP_ */
