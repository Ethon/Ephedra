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
#ifndef HEADER_UUID_4688D5150B394941AB2F1300E5492BB1
#define HEADER_UUID_4688D5150B394941AB2F1300E5492BB1

// Angelscript:
#include <angelscript.h>

// Ephedra:
#include <ephedra/ref_counted_ptr.hpp>
#include <ephedra/detail/type_name_map.hpp>

namespace ephedra
{
	struct registration_context
	{
		ref_counted_ptr<asIScriptEngine> engine;
		detail::type_name_map<char> names;
	};

	void initialize_registration(registration_context& context,
		ref_counted_ptr<asIScriptEngine> const& engine)
	{
		assert(engine);
		context.engine = engine;
	}
}

#endif // HEADER_UUID_74688D5150B394941AB2F1300E5492BB1
