/*  Developer: Shelly Shlomi;									*
 *  Status:approved;											*
 *  Date Of Creation:11.08.21;									*
 *  Date Of Approval:11.08.21;									*
 *  Approved By:                                                * 
 *          phas 1: approved by maor;                           * 
 *          phas 2: approved by nir;                            *
 *  Description: simple string;					                */

#include <cstddef>
#include <cstring>
#include <cassert>
#include <iostream>
#include <new>

#include "simple_string.hpp"

using ilrd::String;

String::String(const char *cstr) : m_cstr(new char[strlen(cstr) + 1])
{
    strcpy(m_cstr, cstr);
}

String::String(const String &other) : m_cstr(new char[other.Length() + 1])
{
    *this = other;
}

String::~String()
{
    delete[] m_cstr;
    m_cstr = NULL;
}

String &String::operator=(const String &other)
{
    assert(other.CStr() != NULL);

    if (&other != this)
    {
        delete[] m_cstr;
        m_cstr = NULL;
        m_cstr = new char[other.Length() + 1];
    }

    strcpy(m_cstr, other.CStr());

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

namespace ilrd
{
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