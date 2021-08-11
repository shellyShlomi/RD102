#ifndef ILRD_RD102_SIMPLE_STRING_HPP
#define ILRD_RD102_SIMPLE_STRING_HPP

#include <cstddef>
#include <iosfwd>
#include "simple_string.hpp"

namespace ilrd
{

	class String
	{
	public:
		String(const char *cstr = ""); // non-explicit on purpose
		String(const String &other);
		~String();
		String &operator=(const String &other);
		size_t Length() const;
		const char *CStr() const;

	private:
		char *m_cstr;
	};

	bool operator<(const String &lhs, const String &rhs);
	bool operator>(const String &lhs, const String &rhs);
	bool operator==(const String &lhs, const String &rhs);
	std::ostream &operator<<(std::ostream &os, const String &str);
} //ilrd

#endif /* ILRD_RD102_SIMPLE_STRING_HPP */
