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
#ifndef HEADER_UUID_50FABEC1AB66409CB8F83BAA36E2E04F
#define HEADER_UUID_50FABEC1AB66409CB8F83BAA36E2E04F

// Boost:
#include <boost/throw_exception.hpp>

// Angelscript:
#include <angelscript.h>

// Ephedra:
#include <ephedra/script_error.hpp>
#include <ephedra/ref_counted_ptr.hpp>

namespace ephedra
{
	namespace detail
	{
		template<class MessageCallback>
		void message_callback_impl(const asSMessageInfo* msg, void* object)
		{
			switch(msg->type)
			{
			case asMSGTYPE_ERROR:
				static_cast<MessageCallback*>(object)->error(
					msg->section, msg->row, msg->col, msg->message);
				break;
				
			case asMSGTYPE_WARNING:
				static_cast<MessageCallback*>(object)->warn(
					msg->section, msg->row, msg->col, msg->message);
				break;
				
			case asMSGTYPE_INFORMATION:
				static_cast<MessageCallback*>(object)->info(
					msg->section, msg->row, msg->col, msg->message);
				break;
			}
		}
		
		template<class MessageCallback>
		void message_callback_noobject_impl(const asSMessageInfo* msg,
			void*)
		{
			switch(msg->type)
			{
			case asMSGTYPE_ERROR:
				MessageCallback::error(
					msg->section, msg->row, msg->col, msg->message);
				break;
				
			case asMSGTYPE_WARNING:
				MessageCallback::warn(
					msg->section, msg->row, msg->col, msg->message);
				break;
				
			case asMSGTYPE_INFORMATION:
				MessageCallback::info(
					msg->section, msg->row, msg->col, msg->message);
				break;
			}
		}
	}
	
	template<class MessageCallback>
	void set_message_callback(ref_counted_ptr<asIScriptEngine>& engine,
		MessageCallback* object)
	{
		int ec = engine->SetMessageCallback(
			asFUNCTION(&detail::message_callback_impl<MessageCallback>),
			static_cast<void*>(object), asCALL_CDECL);
		if(ec < 0)
		{
			BOOST_THROW_EXCEPTION( error::script_error() <<
				error::script_error_code(ec)
			);
		}
	}
	
	template<class MessageCallback>
	void set_message_callback(ref_counted_ptr<asIScriptEngine>& engine)
	{
		int ec = engine->SetMessageCallback(
			asFUNCTION(
				&detail::message_callback_noobject_impl<MessageCallback>),
			nullptr, asCALL_CDECL);
		if(ec < 0)
		{
			BOOST_THROW_EXCEPTION( error::script_error() <<
				error::script_error_code(ec)
			);
		}
	}
}

#endif // HEADER_UUID_50FABEC1AB66409CB8F83BAA36E2E04F
