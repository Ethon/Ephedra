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
#ifndef HEADER_UUID_982935ADC21B45A2BB8FD41637E57736
#define HEADER_UUID_982935ADC21B45A2BB8FD41637E57736

// C++ Standard Library:
#include <type_traits>
#include <utility>

namespace ephedra
{
	template<class ScriptRefCounted>
	class ref_counted_ptr
	{
	public:
		typedef ScriptRefCounted element_type;
		typedef typename std::add_lvalue_reference<element_type>::type
			lvalue_reference;
		typedef typename std::add_pointer<element_type>::type pointer;
		
	private:
		pointer m_ptr;
		
	public:
		ref_counted_ptr()
			: m_ptr(nullptr)
		{ }
		
		ref_counted_ptr(pointer ptr, bool add_ref = false)
			: m_ptr(ptr)
		{
			if(add_ref && m_ptr)
				m_ptr->AddRef();
		}
		
		ref_counted_ptr(ref_counted_ptr<element_type> const& other)
			: m_ptr(other.m_ptr)
		{
			m_ptr->AddRef();
		}
		
		ref_counted_ptr(ref_counted_ptr<element_type>&& other)
			: m_ptr(other.m_ptr)
		{
			other.m_ptr = nullptr;
		}
		
		~ref_counted_ptr()
		{
			if(m_ptr)
				m_ptr->Release();
		}
		
		ref_counted_ptr& operator=(ref_counted_ptr<element_type> other)
		{
			swap(other);
		}

		void reset(pointer ptr = pointer(), bool add_ref = false)
		{
			ref_counted_ptr<element_type> helper(ptr, add_ref);
			swap(helper);
		}
		
		void swap(ref_counted_ptr<element_type> other)
		{
			std::swap(m_ptr, other.m_ptr);
		}
		
		pointer get() const
		{
			return m_ptr;
		}
		
		operator pointer() const
		{
			return m_ptr;
		}
		
		explicit operator bool() const
		{
			return m_ptr != nullptr;
		}
		
		lvalue_reference operator*() const
		{
			return *m_ptr;
		}
		
		pointer operator->() const
		{
			return m_ptr;
		}
		
		bool operator==(ref_counted_ptr<element_type> const& other) const
		{
			return m_ptr == other.m_ptr;
		}

		bool operator!=(ref_counted_ptr<element_type> const& other) const
		{
			return !(*this == other);
		}
	};
}

namespace std
{
	template<class ScriptRefCounted>
	void swap(ephedra::ref_counted_ptr<ScriptRefCounted>& _1,
		ephedra::ref_counted_ptr<ScriptRefCounted>& _2)
	{
		return _1.swap(_2);
	}
}

#endif // HEADER_UUID_982935ADC21B45A2BB8FD41637E57736

