/*  Developer: Shelly Shlomi;									*
 *  Status:approved;											*
 *  Date Of Creation:11.08.21;									*
 *  Date Of Approval:11.08.21;									*
 *  Approved By:                                                * 
 *          phas 1: approved by maor;                           * 
 *          phas 2: approved by nir;                            *
 *  Description: simple string;					                */

#include <cstddef> /*WHY*/
#include <cstring>
#include <cassert>
#include <iostream>

#include "simple_string.hpp"

char *Init(const char *src, size_t size);
namespace ilrd
{

    String::String(const char *cstr) : m_cstr(Init(cstr, strlen(cstr) + 1))
    {
    }

    String::String(const String &other) : m_cstr(Init(other.CStr(), other.Length() + 1))
    {
    }

    String::~String()
    {
        delete[] m_cstr;
        m_cstr = 0;
    }

    String &String::operator=(const String &other)
    {
        char *local_temp = 0;

        assert(other.CStr() != NULL);

        if (&other != this)
        {
            if ((local_temp = Init(other.CStr(), other.Length() + 1)))
            {
                delete[] m_cstr;
                m_cstr = local_temp;
            }
        }

        return (*this);
    }

    size_t String::Length() const
    {
        return (strlen(m_cstr));
    }

    const char *String::CStr() const
    {
        return (m_cstr);
    }

    bool operator<(const String &lhs, const String &rhs)
    {
        assert(lhs.CStr() != NULL);
        assert(rhs.CStr() != NULL);

        return (0 > strcmp(lhs.CStr(), rhs.CStr()));
    }
    bool operator>(const String &lhs, const String &rhs)
    {
        assert(lhs.CStr() != NULL);
        assert(rhs.CStr() != NULL);

        return (0 < strcmp(lhs.CStr(), rhs.CStr()));
    }
    bool operator==(const String &lhs, const String &rhs)
    {
        assert(lhs.CStr() != NULL);
        assert(rhs.CStr() != NULL);

        return (0 == strcmp(lhs.CStr(), rhs.CStr()));
    }

    std::ostream &operator<<(std::ostream &os, const String &str)
    {
        assert(str.CStr() != NULL);

        return (os << str.CStr());
    }

}
char *Init(const char *src, size_t size)
{
    return (reinterpret_cast<char *>(memcpy(new char[size], src, size)));
}
