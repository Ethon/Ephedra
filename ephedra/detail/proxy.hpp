/*
 * This file is part of Foobar.
 * 
 * Foobar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

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
