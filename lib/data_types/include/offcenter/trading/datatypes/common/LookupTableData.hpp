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
 * @file   LookupTableData.hpp
 * @author Scott Brauer
 * @date   06-22-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_COMMON_LOOKUPTABLEDATA_HPP_
#define OFFCENTER_TRADING_DATATYPES_COMMON_LOOKUPTABLEDATA_HPP_

#include <vector>
#include <map>
#include <memory>

namespace offcenter {
namespace trading {
namespace datatypes {
namespace common {

/**
 * Generic getID to be specialized
 */
template<class Record>
unsigned getID(Record& record) { return 0; }

/**
 *
 */
template<class Record>
class LookupTableData
{
public:
	using IDType = unsigned;
	using NameType = std::string;

	using Records = std::vector<Record>;
	using RecordsByID = std::map<IDType, Record>;
	using RecordsByName = std::map<NameType, Record>;

public:
	explicit LookupTableData(const Records& records):
		m_recordsByID(),
		m_recordsByName()
	{
		for (Record record : records) {
			addRecord(record);
		}
	}

	explicit LookupTableData():
		m_recordsByID(),
		m_recordsByName()
	{}

	virtual ~LookupTableData() {}

	const RecordsByID& recordsByID() { return m_recordsByID; }
	const RecordsByName& recordsByName() { return m_recordsByName; }

	const Record& recordByID(IDType id) { return m_recordsByID.at(id); }
	const Record& recordByName(NameType name) { return m_recordsByName.at(name); }

	void addRecord(Record& record) {
		m_recordsByID[getID<Record>(record)] = record;
		m_recordsByName[record.name] = record;
	}

private:
	RecordsByID m_recordsByID;
	RecordsByName m_recordsByName;
};

} /* namespace common */
} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_COMMON_LOOKUPTABLEDATA_HPP_ */
