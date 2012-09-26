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
#ifndef HEADER_UUID_7F10783FF93547AEA10602838D91533B
#define HEADER_UUID_7F10783FF93547AEA10602838D91533B

// C++ Standard Library:
#include <vector>
#include <functional>

// Ephedra:
#include <ephedra/registration_context.hpp>

namespace ephedra
{
	namespace detail
	{
		// Stores function objects, which register something.
		struct registerable_list
		{
		public:
			typedef std::function<void (registration_context&)> registerable;
			
		private:
			std::vector<registerable> m_registerables;
			
		public:
			// Add a new function object, which registers something.
			inline void add(registerable item)
			{
				m_registerables.push_back(std::move(item));
			}
			
			// Call all function objects.
			inline void register_(registration_context& context) const
			{
				for(registerable const& item : m_registerables)
					item(context);
			}
		};
	}
}

#endif // HEADER_UUID_7F10783FF93547AEA10602838D91533B
