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
 * @file   InstrumentJson.hpp
 * @author Scott Brauer
 * @date   05-31-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_INSTRUMENTSOCI_HPP_
#define OFFCENTER_TRADING_DATATYPES_INSTRUMENTSOCI_HPP_

#include "soci/soci.h"

#include "offcenter/trading/datatypes/Instrument.hpp"

namespace soci {

template<>
struct type_conversion<offcenter::trading::datatypes::Instrument>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::Instrument & p)
	{
		p.instrument_id = v.get<unsigned>("instrument_id");
		p.name = v.get<std::string>("name");
		p.display_name = v.get<std::string>("display_name");
	}

	static void to_base(offcenter::trading::datatypes::Instrument const & p, values & v, indicator & ind)
	{
		v.set("instrument_id", p.instrument_id);
		v.set("name", p.name);
		v.set("display_name", p.display_name);
		ind = i_ok;
	}
};

} /* namespace soci */


#endif /* OFFCENTER_TRADING_DATATYPES_INSTRUMENTSOCI_HPP_ */
