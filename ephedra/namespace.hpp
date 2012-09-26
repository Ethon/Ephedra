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
#ifndef HEADER_UUID_FCE900F2D78B4CDB919A3C7B6ECE4E95
#define HEADER_UUID_FCE900F2D78B4CDB919A3C7B6ECE4E95

// C++ Standard Library:
#include <string>

// Boost:
#include <boost/throw_exception.hpp>
#include <boost/exception/info.hpp>

// Angelscript:
#include <angelscript.h>

// Ephedra:
#include <ephedra/registration_context.hpp>
#include <ephedra/script_error.hpp>

namespace ephedra
{
	namespace error
	{
		typedef boost::error_info<struct tag_invalid_namespace, std::string>
			invalid_namespace;
	}
	
	namespace detail
	{
		inline void set_default_namespace(
			ref_counted_ptr<asIScriptEngine>& engine, char const* ns)
		{
			int ec = engine->SetDefaultNamespace(ns);
			if(ec < 0)
			{
				BOOST_THROW_EXCEPTION(	error::script_error() <<
					error::script_error_code(ec) <<
					error::invalid_namespace(ns)
				);
			}
		}
	}
	class namespace_
	{
	private:
		std::string m_ns;
		registration_context& m_context;
		
	public:
		inline namespace_(registration_context& context, std::string ns)
			: m_ns(std::move(ns)), m_context(context)
		{ }
		
		template<class Registerable>
		void register_inside(Registerable const& registerable)
		{
			detail::set_default_namespace(m_context.engine, m_ns.c_str());
			registerable.register_(m_context);
			detail::set_default_namespace(m_context.engine, "");
		}
		
		template<class Registerable>
		void operator[](Registerable const& registerable)
		{
			register_inside(registerable);
		}
	};
}

#endif // HEADER_UUID_FCE900F2D78B4CDB919A3C7B6ECE4E95
