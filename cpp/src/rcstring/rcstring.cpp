/*  Developer: Shelly Shlomi;									*
 *  Status:DONE;    											*
 *  Date Of Creation:19.08.21;									*
 *  Date Of Approval:19.08.21;									*
 *  Approved By:                                                * 
 *  Description: refernc count string;                          */

#include <cstring>  /*  memcpy  */
#include <iostream> /*  ostream */
#include <vector>   /*  vector  */
#include <cstdio>   /*  EOF     */
#include <cstddef>  /*  offsetof*/

#include "rcstring.hpp"

const size_t SELF_COUNT(1);
const int EQUALITY_INDICATOR(0);
const size_t NULL_TERMINATOR(1);

namespace ilrd
{
    RefCountStr *DataKeeper(RefCountStr *to_assinge);
    void RefCountStrCleanUp(ilrd::RefCountStr *m_data, size_t size);
    RefCountStr *InitRefCountStr(const char *str);

    struct RefCountStr
    {
    public:
        size_t m_copy_count;
        bool m_char_ref;
        char m_cstr[NULL_TERMINATOR];
    };

    RCString::RCString(const char *cstr) : m_data(InitRefCountStr(cstr))
    {
        ; //empty on purpose
    }

    RCString::RCString(const RCString &other) : m_data(other.m_data)
    {
        if (false != other.m_data->m_char_ref)
        {
            m_data = DataKeeper(m_data);
        }
        else
        {
            ++other.m_data->m_copy_count;
        }
    }

    RCString::~RCString()
    {
        RefCountStrCleanUp(m_data, Length());
    }

    RCString &RCString::operator=(const RCString &other)
    {
        if (false != other.m_data->m_char_ref)
        {
            RefCountStrCleanUp(m_data, Length());
            m_data = DataKeeper(other.m_data);
        }
        else
        {
            ++other.m_data->m_copy_count;
            RefCountStrCleanUp(m_data, Length());
            m_data = other.m_data;
        }

        return (*this);
    }

    size_t RCString::Length() const
    {
        return (strlen(CStr()));
    }

    const char *RCString::CStr() const
    {
        return (m_data->m_cstr);
    }

    bool operator<(const RCString &lhs, const RCString &rhs)
    {
        return (EQUALITY_INDICATOR > strcmp(lhs.CStr(), rhs.CStr()));
    }
    bool operator>(const RCString &lhs, const RCString &rhs)
    {
        return (EQUALITY_INDICATOR < strcmp(lhs.CStr(), rhs.CStr()));
    }
    bool operator==(const RCString &lhs, const RCString &rhs)
    {
        return (EQUALITY_INDICATOR == strcmp(lhs.CStr(), rhs.CStr()));
    }
    bool operator!=(const RCString &lhs, const RCString &rhs)
    {
        return (!(lhs == rhs));
    }

    std::ostream &operator<<(std::ostream &os, const RCString &str)
    {
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
        if (SELF_COUNT != m_data->m_copy_count)
        {
            --(m_data->m_copy_count);
            m_data = DataKeeper(m_data);
        }
        m_data->m_char_ref = true;

        return (m_data->m_cstr[index]);
    }

    char RCString::operator[](size_t index) const
    {
        return (CStr()[index]);
    }

    void RefCountStrCleanUp(RefCountStr *m_data, size_t size)
    {
        --m_data->m_copy_count;
        if (0 == m_data->m_copy_count)
        {
            memset(m_data->m_cstr, 0, size);
            m_data->m_char_ref = false;
            m_data->m_copy_count = SELF_COUNT;
            delete (m_data);
            m_data = 0;
        }

        return;
    }

    RefCountStr *InitRefCountStr(const char *str)
    {
        const size_t LEN = strlen(str) + NULL_TERMINATOR;
        RefCountStr *rc_ptr = 0;
        rc_ptr = static_cast<RefCountStr *>(::operator new(LEN + offsetof(RefCountStr, m_cstr)));

        memcpy(rc_ptr->m_cstr, str, LEN);
        rc_ptr->m_copy_count = SELF_COUNT;
        rc_ptr->m_char_ref = false;

        return (rc_ptr);
    }

    RefCountStr *DataKeeper(RefCountStr *to_assinge)
    {
        RefCountStr *local_cpy = InitRefCountStr(to_assinge->m_cstr);
        if (local_cpy)
        {
            return (local_cpy);
        }

        return (to_assinge);
    }
}
