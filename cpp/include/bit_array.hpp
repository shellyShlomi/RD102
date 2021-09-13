#ifndef ILRD_RD102_BITARRAY_HPP
#define ILRD_RD102_BITARRAY_HPP

#include <cstddef>  //size_t
#include <iostream> //string
#include <cstring>
#include <stdexcept>  //std::out_of_range
#include <functional> //bitwise::or
#include <algorithm>
#include <boost/array.hpp>

#if __cplusplus <= 199711L
#define noexcept throw()
#else
#define throw(...)
#endif

namespace ilrd
{
    static const size_t CHAR_BIT(8);

    template <size_t SIZE = CHAR_BIT>
    class BitArray
    {

    private:
        class BitProxy;

    public:
        explicit BitArray();
        ~BitArray();
        BitArray(const BitArray &other);
        inline BitArray &operator=(const BitArray &other);
        inline bool operator[](size_t index) const noexcept;
        inline BitProxy operator[](size_t index) noexcept;
        inline BitArray &operator|=(const BitArray &rhs_) noexcept;
        inline BitArray &operator&=(const BitArray &rhs_) noexcept;
        inline BitArray &operator^=(const BitArray &rhs_) noexcept;
        inline BitArray &operator<<=(size_t shifts) noexcept;
        inline BitArray &operator>>=(size_t shifts) noexcept;
        inline bool operator==(const BitArray &rhs_) noexcept;
        inline bool operator!=(const BitArray &rhs_) noexcept;

        inline void SetAll(bool val = true) noexcept;
        inline void SetBit(size_t index, bool val = true) throw(std::out_of_range);
        inline bool GetBit(size_t index) const throw(std::out_of_range);
        inline void FlipAll() noexcept;
        inline void FlipBit(size_t index) const throw(std::out_of_range);
        inline size_t Count() const noexcept;
        inline std::string ToString() const; //Strong guarantee:
                                             //if an exception is thrown,
                                             //there are no changes in the bitset.

    private:
        static const size_t M_SIZE_OF_ARRAY = (SIZE / CHAR_BIT) + !!(SIZE % CHAR_BIT);
        boost::array<unsigned char, M_SIZE_OF_ARRAY> m_bit_arr;

        class BitProxy
        {
        public:
            BitProxy(BitArray *bitarray, size_t index);
            inline operator bool() const;
            BitProxy &operator=(bool bit);
            BitProxy &operator=(BitProxy &other);

        private:
            unsigned char *m_proxy_bitarr;
            size_t m_index;
        };
        // inline operator BitProxy() const;
    };

    template <size_t SIZE>
    BitArray<SIZE>::BitArray() : m_bit_arr()
    {
        std::fill(m_bit_arr.begin(), m_bit_arr.end(), 0);
    }

    template <size_t SIZE>
    BitArray<SIZE>::BitArray(const BitArray &other) : m_bit_arr(other.m_bit_arr)
    {
        ;
    }

    template <size_t SIZE>
    BitArray<SIZE>::~BitArray()
    {
    }

    template <size_t SIZE>
    BitArray<SIZE> &BitArray<SIZE>::operator=(const BitArray<SIZE> &other)
    {
        std::copy(m_bit_arr.begin(), m_bit_arr.end(),
                  (const_cast<BitArray<SIZE> &>(other)).m_bit_arr.begin());

        return (*this);
    }

    template <size_t SIZE>
    typename BitArray<SIZE>::BitProxy BitArray<SIZE>::operator[](size_t index) noexcept
    {
        return (BitProxy(this, index));
    }

    template <size_t SIZE>
    bool BitArray<SIZE>::operator[](size_t index) const noexcept
    {
        BitArray<SIZE> temp(*this); /* making a copy with no referenc to the
                                      const obj for the reuse of non const []*/

        return (temp[index]);
    }

    template <size_t SIZE>
    BitArray<SIZE> &BitArray<SIZE>::operator|=(const BitArray<SIZE> &rhs_) noexcept
    {
        // std::valarray<unsigned char> var;
        // std::valarray<unsigned char> var2;
        // var |= var2;
        std::for_each(m_bit_arr[0], m_bit_arr[M_SIZE_OF_ARRAY - 1], BitArray<SIZE>());
        return (*this);
    }

    template <size_t SIZE>
    BitArray<SIZE>::BitProxy::BitProxy(BitArray *bitarray, size_t index)
        : m_proxy_bitarr(bitarray->m_bit_arr.c_array() + (index / CHAR_BIT)), m_index(index % CHAR_BIT)
    {
        ;
    }
    // template <size_t SIZE>
    // typename BitArray<SIZE>::BitProxy BitArray<SIZE>::operator BitArray<SIZE>::BitProxy() const
    // {
    // }
    template <size_t SIZE>
    BitArray<SIZE>::BitProxy::operator bool() const
    {
        return (*m_proxy_bitarr & (1 << m_index));
    }

    template <size_t SIZE>
    typename BitArray<SIZE>::BitProxy &BitArray<SIZE>::BitProxy::operator=(bool bit)
    {
        *(m_proxy_bitarr) = *(m_proxy_bitarr) | (bit << m_index);
        return *this;
    }

    template <size_t SIZE>
    typename BitArray<SIZE>::BitProxy &BitArray<SIZE>::BitProxy::operator=(BitProxy &other)
    {
        bool bit = *(other.m_proxy_bitarr) << other.m_index;
        return (*this = bit);
    }

} //ilrd

#ifdef noexcept
#undef noexcept
#else
#undef throw
#endif

#endif /* ILRD_RD102_BITARRAY_HPP */