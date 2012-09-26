/* All copyright belongs to Florian Erler <ethon[@]ethon.cc>
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
#ifndef HEADER_UUID_7B6158160079453BA34B55220889D824
#define HEADER_UUID_7B6158160079453BA34B55220889D824

namespace ephedra
{
	namespace detail
	{
		template<typename FPtrT, FPtrT Fun, typename... Args>
		auto global_function_proxy(Args&&... args) -> decltype(Fun(args...))
		{
			return Fun(std::forward<Args>(args)...);
		}

		template<typename ValueT, ValueT* Ptr>
		ValueT global_property_proxy_get()
		{
			return *Ptr;
		}

		template<typename ValueT, ValueT* Ptr>
		void global_property_proxy_set(ValueT const& val)
		{
			*Ptr = val;
		}
	}
}

#endif // HEADER_UUID_7B6158160079453BA34B55220889D824
