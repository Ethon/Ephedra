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
#ifndef HEADER_UUID_5C09A759071C4A4BBDD5A495538B585E
#define HEADER_UUID_5C09A759071C4A4BBDD5A495538B585E

// C++ Standard Library:
#include <string>
#include <unordered_map>
#include <utility>

// Boost:
#include <boost/throw_exception.hpp>
#include <boost/exception/info.hpp>

namespace ephedra
{
	namespace error
	{
		struct unknown_type_error : public virtual script_error
		{ };
		
		typedef boost::error_info<struct tag_unknown_type_info,
			std::type_info const&> unknown_type_info;
	}
	
	namespace detail
	{
		template<typename CharT = char>
		class type_name_map
		{
		public:
			typedef CharT char_type;
			typedef std::basic_string<CharT> string_type;
			
		private:
			std::unordered_map<std::type_index, string_type> m_map;
			
		public:
			void set(std::type_info const& index, string_type name) const
			{
				m_map.emplace(index, std::move(name));
			}
			
			bool try_get(std::type_info const& type, string_type& out) const
			{
				auto iter = m_map.find(type);
				if(iter == m_map.end()
					return false;
				
				out = iter->second;
				return true;
			}
			
			string_type get(std::type_info const& type) const
			{
				string_type result;
				if(!try_get(type, result))
				{
					BOOST_THROW_EXCEPTION(	error::unknown_type_error() <<
						error::unknown_type_info(type)
					);
				}
				
				return result;
			}
			
			string_type operator[](std::type_index type) const
			{
				return get(type);
			}
		};
	}
}

#endif // HEADER_UUID_5C09A759071C4A4BBDD5A495538B585E
