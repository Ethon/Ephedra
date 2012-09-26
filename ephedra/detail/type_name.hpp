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
#ifndef HEADER_UUID_49CB0A7FB9674F75831357208878DA10
#define HEADER_UUID_49CB0A7FB9674F75831357208878DA10

// C++ Standard Library:
#include <cstdint>

// Ephedra:
#include <ephedra/detail/type_name_map.hpp>

namespace ephedra
{
	namespace detail
	{
		// Default implementation, does a map-lookup for the type's name.
		template<typename T>
		struct type_name
		{
			template<typename CharT>
			static typename type_name_map<CharT>::string_type
				value(type_name_map<CharT>& map)
			{
				return map[typeid(T)];
			}
		};
		
		// Specialization for const types.
		template<typename T>
		struct type_name<T const>
		{
			static typename type_name_map<char>::string_type
				value(type_name_map<char>& map)
			{
				return "const " + type_name<T>::value(map);
			}
			
			static typename type_name_map<wchar_t>::string_type
				value(type_name_map<wchar_t>& map)
			{
				return "const " + type_name<T>::value(map);
			}
		};
		
		/************ Unsigned integer types ************/
		
		template<>
		struct type_name<std::uint8_t>
		{
			static typename type_name_map<char>::string_type
				value(type_name_map<char>&)
			{
				return "uint8";
			}
			
			static typename type_name_map<wchar_t>::string_type
				value(type_name_map<wchar_t>&)
			{
				return L"uint8";
			}
		};
		
		template<>
		struct type_name<std::uint16_t>
		{
			static typename type_name_map<char>::string_type
				value(type_name_map<char>&)
			{
				return "uint16";
			}
			
			static typename type_name_map<wchar_t>::string_type
				value(type_name_map<wchar_t>&)
			{
				return L"uint16";
			}
		};
		
		template<>
		struct type_name<std::uint32_t>
		{
			static typename type_name_map<char>::string_type
				value(type_name_map<char>&)
			{
				return "uint";
			}
			
			static typename type_name_map<wchar_t>::string_type
				value(type_name_map<wchar_t>&)
			{
				return L"uint";
			}
		};
		
		template<>
		struct type_name<std::uint64_t>
		{
			static typename type_name_map<char>::string_type
				value(type_name_map<char>&)
			{
				return "uint64";
			}
			
			static typename type_name_map<wchar_t>::string_type
				value(type_name_map<wchar_t>&)
			{
				return L"uint64";
			}
		};
		
		/************ Signed integer types ************/
		
		template<>
		struct type_name<std::int8_t>
		{
			static typename type_name_map<char>::string_type
				value(type_name_map<char>&)
			{
				return "int8";
			}
			
			static typename type_name_map<wchar_t>::string_type
				value(type_name_map<wchar_t>&)
			{
				return L"int8";
			}
		};
		
		template<>
		struct type_name<std::int16_t>
		{
			static typename type_name_map<char>::string_type
				value(type_name_map<char>&)
			{
				return "int16";
			}
			
			static typename type_name_map<wchar_t>::string_type
				value(type_name_map<wchar_t>&)
			{
				return L"int16";
			}
		};
		
		template<>
		struct type_name<std::int32_t>
		{
			static typename type_name_map<char>::string_type
				value(type_name_map<char>&)
			{
				return "int";
			}
			
			static typename type_name_map<wchar_t>::string_type
				value(type_name_map<wchar_t>&)
			{
				return L"int";
			}
		};
		
		template<>
		struct type_name<std::int64_t>
		{
			static typename type_name_map<char>::string_type
				value(type_name_map<char>&)
			{
				return "int64";
			}
			
			static typename type_name_map<wchar_t>::string_type
				value(type_name_map<wchar_t>&)
			{
				return L"int64";
			}
		};
		
		/************ Floating-point types. ************/
		template<>
		struct type_name<float>
		{
			static typename type_name_map<char>::string_type
				value(type_name_map<char>&)
			{
				return "float";
			}
			
			static typename type_name_map<wchar_t>::string_type
				value(type_name_map<wchar_t>&)
			{
				return L"float";
			}
		};
		
		template<>
		struct type_name<double>
		{
			static typename type_name_map<char>::string_type
				value(type_name_map<char>&)
			{
				return "double";
			}
			
			static typename type_name_map<wchar_t>::string_type
				value(type_name_map<wchar_t>&)
			{
				return L"double";
			}
		};
		
		/************ Other primitive types. ************/
		template<>
		struct type_name<void>
		{
			static typename type_name_map<char>::string_type
				value(type_name_map<char>&)
			{
				return "void";
			}
			
			static typename type_name_map<wchar_t>::string_type
				value(type_name_map<wchar_t>&)
			{
				return L"void";
			}
		};
		
		template<>
		struct type_name<bool>
		{
			static typename type_name_map<char>::string_type
				value(type_name_map<char>&)
			{
				return "bool";
			}
			
			static typename type_name_map<wchar_t>::string_type
				value(type_name_map<wchar_t>&)
			{
				return L"bool";
			}
		};
	}
}

#endif // HEADER_UUID_49CB0A7FB9674F75831357208878DA10
