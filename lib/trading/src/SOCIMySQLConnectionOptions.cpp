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
 * @file   SOCIMySQLConnectionOptions.cpp
 * @author Scott Brauer
 * @date   03-20-2021
 */

#include "offcenter/trading/amqp/SOCIMySQLConnectionOptions.hpp"

#include <string>
#include <initializer_list>
#include <sstream>


namespace offcenter {
namespace trading {
namespace db {

SOCIMySQLConnectionOptions::SOCIMySQLConnectionOptions():
		dbname("db"),
		user("db"),
		password("db"),
		host("db"),
		port("db"),
		unix_socket("db"),
		sslca("db"),
		sslcert("db"),
		local_infile("db"),
		charset("db"),
		connect_timeout("db"),
		read_timeout("db"),
		write_timeout("db")
{
	// TODO Auto-generated constructor stub

}

SOCIMySQLConnectionOptions::~SOCIMySQLConnectionOptions()
{
	// TODO Auto-generated destructor stub
}

const std::string SOCIMySQLConnectionOptions::getConnectionString() const
{
	auto elements = {
			dbname.optionString(),
			user.optionString(),
			password.optionString(),
			host.optionString(),
			port.optionString(),
			unix_socket.optionString(),
			sslca.optionString(),
			sslcert.optionString(),
			local_infile.optionString(),
			charset.optionString(),
			connect_timeout.optionString(),
			read_timeout.optionString(),
			write_timeout.optionString()
	};
	std::ostringstream ss;
	bool firstElement = true;
	for (auto element : elements) {
		ss << (!firstElement ? " " : "") << element;
		firstElement = false;
	}
	return ss.str();
}

} /* namespace db */
} /* namespace trading */
} /* namespace offcenter */
