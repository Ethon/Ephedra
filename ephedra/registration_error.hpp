/* All copyright belongs to Florian Erler <ethon[@]ethon.cc> 2012, 2013
 * 
 * This file is part of Ephedra.
 * 
 * Ephedra is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Ephedra is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Ephedra.  If not, see <http://www.gnu.org/licenses/>.
 */
 
// MSVC-Guard
#ifdef _MSC_VER
#	paragma once
#endif // _MSC_VER

// Guard
#ifndef HEADER_UUID_ADFBBCB2ACF048A2BB8A0DD4924A98B0
#define HEADER_UUID_ADFBBCB2ACF048A2BB8A0DD4924A98B0

// C++ Standard Library:
#include <string>

// Boost:
#include <boost/exception/info.hpp>

// Ephedra:
#include <ephedra/script_error.hpp>

namespace ephedra
{
	namespace error
	{
		struct registration_error : virtual script_error
		{ };
		
		typedef boost::error_info<struct tag_script_error_code, std::string>
			decleration;
	}
}

#endif // HEADER_UUID_ADFBBCB2ACF048A2BB8A0DD4924A98B0
