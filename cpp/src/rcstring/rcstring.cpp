/*  Developer: Shelly Shlomi;									*
 *  Status:DONE;    											*
 *  Date Of Creation:19.08.21;									*
 *  Date Of Approval:19.08.21;									*
 *  Approved By:                                                * 
 *  Description: refernc count string;                          */

#include <cstring>  /*  memcpy  */
#include <cassert>  /*  assert  */
#include <iostream> /*  ostream */
#include <vector>   /*  vector  */
#include <cstdio>   /*  EOF     */

#include "rcstring.hpp"

const size_t SELF_COUNT(1);
const int NOT_EXSIST(0);
const int EQUALETY_INDICATOR(0);
const size_t NULL_TERMINETOR(1);

namespace ilrd
{
    void RefManipulation(ilrd::RefCountStr *m_data);

    struct RefCountStr
    {
    public:
        size_t m_ref_count;
        char m_cstr[NULL_TERMINETOR];
    };

    inline RefCountStr *InitRCString(const char *str)
    {
        const size_t LEN = strlen(str) + NULL_TERMINETOR;
        RefCountStr *rc_ptr = 0;

        rc_ptr = static_cast<RefCountStr *>(::operator new(LEN + sizeof(size_t)));
        memcpy(rc_ptr->m_cstr, str, LEN);
        rc_ptr->m_ref_count = SELF_COUNT;
        return (rc_ptr);
    }

    RCString::RCString(const char *cstr)
        : m_data(InitRCString(cstr)), is_char_ref(NOT_EXSIST)
    {
    }

    RCString::RCString(const RCString &other)
        : m_data(other.m_data), is_char_ref(other.is_char_ref)
    {
        if (NOT_EXSIST != other.is_char_ref)
        {
            is_char_ref = NOT_EXSIST;
            m_data = InitRCString(other.m_data->m_cstr);
        }
        else
        {
            ++other.m_data->m_ref_count;
        }
    }

    RCString::~RCString()
    {
        RefManipulation(m_data);
        is_char_ref = NOT_EXSIST;
    }

    RCString &RCString::operator=(const RCString &other)
    {
        if (NOT_EXSIST != other.is_char_ref)
        {
            is_char_ref = NOT_EXSIST;
            RefManipulation(m_data);
            m_data = InitRCString(other.m_data->m_cstr);
        }
        else
        {
            ++other.m_data->m_ref_count;
            RefManipulation(m_data);
            m_data = other.m_data;
            is_char_ref = other.is_char_ref;
        }

        return (*this);
    }

    size_t RCString::Length() const
    {
        return (strlen(m_data->m_cstr));
    }

    const char *RCString::CStr() const
    {
        return (m_data->m_cstr);
    }

    bool operator<(const RCString &lhs, const RCString &rhs)
    {
        assert(lhs.CStr() != NULL);
        assert(rhs.CStr() != NULL);

        return (EQUALETY_INDICATOR > strcmp(lhs.CStr(), rhs.CStr()));
    }
    bool operator>(const RCString &lhs, const RCString &rhs)
    {
        assert(lhs.CStr() != NULL);
        assert(rhs.CStr() != NULL);

        return (EQUALETY_INDICATOR < strcmp(lhs.CStr(), rhs.CStr()));
    }
    bool operator==(const RCString &lhs, const RCString &rhs)
    {
        assert(lhs.CStr() != NULL);
        assert(rhs.CStr() != NULL);

        return (EQUALETY_INDICATOR == strcmp(lhs.CStr(), rhs.CStr()));
    }
    bool operator!=(const RCString &lhs, const RCString &rhs)
    {
        return (!(lhs == rhs));
    }

    std::ostream &operator<<(std::ostream &os, const RCString &str)
    {
        assert(str.CStr() != NULL);

        return (os << str.CStr());
    }

    std::istream &operator>>(std::istream &is, RCString &str)
    {
        std::vector<char> loc_string = std::vector<char>();

        int ch = is.get();
        while (EOF != ch && '\n' != ch)
        {
            loc_string.push_back(ch);
            ch = is.get();
        }

        loc_string.push_back('\0');

        str = RCString(&loc_string[0]);

        return is;
    }
    char &RCString::operator[](size_t index)
    {
        ++is_char_ref;
        if (SELF_COUNT != m_data->m_ref_count)
        {
            --(m_data->m_ref_count);
            m_data = InitRCString(m_data->m_cstr);
        }

        return (m_data->m_cstr[index]);
    }
    char RCString::operator[](size_t index) const
    {
        return (m_data->m_cstr[index]);
    }

    void RefManipulation(RefCountStr *m_data)
    {
        --m_data->m_ref_count;
        if (NOT_EXSIST == m_data->m_ref_count)
        {
            delete (m_data);
            m_data = 0;
        }

        return;
    }

}