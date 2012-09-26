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
#ifndef HEADER_UUID_B087B9D907354481BBFFAC0DAE923A60
#define HEADER_UUID_B087B9D907354481BBFFAC0DAE923A60

// C++ Standard Library:
#include <string>

// Boost:
#include <boost/throw_exception.hpp>

// Angelscript:
#include <angelscript.h>

// Ephedra:
#include <ephedra/registration_context.hpp>
#include <ephedra/registration_error.hpp>
#include <ephedra/detail/make_function_decl.hpp>
#include <ephedra/detail/registerable_list.hpp>

namespace ephedra
{
	namespace detail
	{
		// Call the engine to register the function and throw in case of error.
		inline void register_global_function(
			ref_counted_ptr<asIScriptEngine>& engine,
			char const* decl, asSFuncPtr ptr, asDWORD cconv)
		{
			int ec = engine->RegisterGlobalFunction(decl, ptr, cconv);
			if(ec < 0)
			{
				BOOST_THROW_EXCEPTION(	error::registration_error() <<
					error::script_error_code(ec) <<
					error::decleration(decl)
				);
			}
		}
	}
	
	// Stores a global function and registers it.
	template<typename ReturnT, typename... Args>
	class basic_global_function
	{
	public:
		typedef ReturnT(*pointer)(Args...);
		
	private:
		std::string m_name;
		pointer m_function;
		
		typedef basic_global_function<ReturnT, Args...> this_type;

	public:
		// Simply stores the arguments.
		basic_global_function(std::string name, pointer function)
			: 	m_name(std::move(name)),
				m_function(function)
		{ }
		
		// Returns the stored name.
		std::string const& name() const
		{
			return m_name;
		}
		
		// Returns the stored function pointer.
		pointer ptr() const
		{
			return m_function;
		}
		
		// Register the function in the given context.
		void register_(registration_context& context) const
		{
			detail::register_global_function(context.engine,
				detail::make_function_decl(
					context.names, m_name, m_function
				).c_str(),
				asFUNCTION(m_function), asCALL_CDECL);
		}

		// Create a registerable_list if on the left side of the expression.
		template<class Other>
		detail::registerable_list operator,(Other const& other)
		{
			detail::registerable_list list;
			return ((list, *this), other);
		}
	};
	
	// Append function to a registerable_list, if on the right side.
	template<typename ReturnT, typename... Args>
	detail::registerable_list& operator,(
		detail::registerable_list& list,
		basic_global_function<ReturnT, Args...> const& function)
	{
		list.add(std::bind(
			&basic_global_function<ReturnT, Args...>::register_,
			&function,
			std::placeholders::_1)
		);
		return list;
	}
	
	// Convenience function to deduce a basic_global_function's
	// template arguments.
	template<typename ReturnT, typename... Args>
	basic_global_function<ReturnT, Args...> global_function(std::string name,
		ReturnT(*pointer)(Args...))
	{
		return basic_global_function<ReturnT, Args...>(std::move(name), pointer);
	}
	
	// Directly register a global function.
	template<typename ReturnT, typename... Args>
	void register_global_function(registration_context& context, std::string name,
		ReturnT(*pointer)(Args...))
	{
		global_function(std::move(name), pointer).register_(context);
	}
}

#endif // HEADER_UUID_B087B9D907354481BBFFAC0DAE923A60
