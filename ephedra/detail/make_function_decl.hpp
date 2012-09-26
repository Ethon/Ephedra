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
#ifndef HEADER_UUID_2C3C75319DEC496FB430845567485153
#define HEADER_UUID_2C3C75319DEC496FB430845567485153

// C++ Standard Library:
#include <cstdint>

// Ephedra:
#include <ephedra/detail/type_name.hpp>

namespace ephedra
{
	namespace detail
	{
		// Create decleration for a global function without arguments.
		template<typename ReturnT>
		typename type_name_map<char>::string_type
			make_function_decl(type_name_map<char>& map,
				typename type_name_map<char>::string_type const& name,
				ReturnT(*)())
		{
			return type_name<ReturnT>().value(map) + ' ' + name + "()"; 
		}
		
		template<typename ReturnT>
		typename type_name_map<wchar_t>::string_type
			make_function_decl(type_name_map<wchar_t>& map,
				typename type_name_map<wchar_t>::string_type const& name,
				ReturnT(*)())
		{
			return type_name<ReturnT>().value(map) + L' ' + name + L"()"; 
		}
			
		// Create decleration for a global function with args.
		template<typename ReturnT, typename Arg0, typename... Args>
		typename type_name_map<char>::string_type
			make_function_decl(type_name_map<char>& map,
				typename type_name_map<char>::string_type const& name,
				ReturnT(*)(Arg0, Args...))
		{
			typename type_name_map<char>::string_type decl(
				type_name<ReturnT>().value(map));
			((decl += ' ') += name) += '(';
				
			decl += type_name<Arg0>().value(map);
			bool dummy[] =
			{ 
				(
					((decl += ", ") += type_name<Args>().value(map)),
					false
				)...
			};
			(void)dummy;
				
			decl += ')';
			return decl;
		}
		
		template<typename ReturnT, typename Arg0, typename... Args>
		typename type_name_map<wchar_t>::string_type
			make_function_decl(type_name_map<wchar_t>& map,
				typename type_name_map<wchar_t>::string_type const& name,
				ReturnT(*)(Arg0, Args...))
		{
			typename type_name_map<wchar_t>::string_type decl(
				type_name<ReturnT>().value(map));
			((decl += L' ') += name) += L'(';
				
			decl += type_name<Arg0>().value(map);
			bool dummy[] =
			{ 
				(
					((decl += L", ") += type_name<Args>().value(map)),
					false
				)...
			};
			(void)dummy;
				
			decl += L')';
			return decl;
		}
	}
}

#endif // HEADER_UUID_2C3C75319DEC496FB430845567485153
