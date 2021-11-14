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
 * @file   OandaPersistenceManagerOptions.hpp
 * @author Scott Brauer
 * @date   09-10-2021
 */

#ifndef OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_PERSISTENCEMANAGEROPTIONS_HPP_
#define OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_PERSISTENCEMANAGEROPTIONS_HPP_

#include <string>
#include <chrono>

#include <cpprest/uri_builder.h>

namespace offcenter {
namespace trading {
namespace oandapersistenceclient {

/**
 *
 */
class PersistenceManagerOptions
{
private:
	inline static int UnInitializedInt = -1;
	inline static std::string UnInitializedString = "";

public:
	explicit PersistenceManagerOptions():
		m_scheme(UnInitializedString),
		m_userInfo(UnInitializedString),
		m_host(UnInitializedString),
		m_port(UnInitializedInt),
		m_path(UnInitializedString),
		m_query(UnInitializedString),
		m_fragment(UnInitializedString),
		m_timeout(UnInitializedInt),
		m_chunksize(UnInitializedInt)
	{}

	virtual ~PersistenceManagerOptions() {}

	const std::string& getScheme() { return m_scheme; }
	const std::string& getUserInfo() { return m_userInfo; }
	const std::string& getHost() { return m_host; }
	int getPort() { return m_port; }
	const std::string& getPath() { return m_path; }
	const std::string& getQuery() { return m_query; }
	const std::string& getFragment() { return m_fragment; }
	bool isTimeoutDirty() { return m_timeout != UnInitializedInt; }
	std::chrono::milliseconds getTimeout() { return std::chrono::milliseconds(m_timeout); }
	bool isChunksizeDirty() { return m_chunksize != UnInitializedInt; }
	int getChunksize() { return m_chunksize; }

	web::uri getURI() {
		web::uri_builder uriBuilder;

		uriBuilder.set_scheme(m_scheme);
		if (m_userInfo != UnInitializedString) { uriBuilder.set_user_info(m_userInfo); }
		uriBuilder.set_host(m_host);
		uriBuilder.set_port(m_port);
		if (m_path != UnInitializedString) { uriBuilder.set_path(m_path); }
		if (m_query != UnInitializedString) { uriBuilder.set_query(m_query); }
		if (m_fragment != UnInitializedString) { uriBuilder.set_fragment (m_fragment); }
		return uriBuilder.to_uri();
	}

	friend class PersistenceManagerProgramOptions;

private:
	std::string m_scheme;
	std::string m_userInfo;
	std::string m_host;
	int m_port;
	std::string m_path;
	std::string m_query;
	std::string m_fragment;
	int m_timeout;
	int m_chunksize;

};

} /* namespace oandapersistenceclient */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_PERSISTENCEMANAGEROPTIONS_HPP_` */
