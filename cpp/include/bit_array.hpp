#ifndef ILRD_RD102_BITARRAY_HPP
#define ILRD_RD102_BITARRAY_HPP

#include <cstddef>    //size_t
#include <cstring>    //string
#include <stdexcept>  //std::out_of_range
#include <functional> //bitwise::or
#include <algorithm>  //std::fill
#include <numeric>    // std::accumulate

#include <boost/array.hpp>
#include "bit_array_detail.hpp"

#if __cplusplus <= 199711L
#define noexcept throw()
#else
#define throw(...)
#endif

namespace ilrd
{

    template <size_t SIZE = detail::CHAR_BIT>
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
        inline void FlipBit(size_t index) throw(std::out_of_range);
        inline size_t Count() const noexcept;
        inline std::string ToString() const; //Strong guarantee:
                                             //if an exception is thrown,
                                             //there are no changes in the bitset.

    private:
        static const size_t M_SIZE_OF_ARRAY = (SIZE / detail::CHAR_BIT) + !!(SIZE % detail::CHAR_BIT);
        boost::array<unsigned char, M_SIZE_OF_ARRAY> m_bit_arr;
        size_t CountOnFromLUT(const BitArray &bit_array);
        BitArray<SIZE> UnconstCast() const;

        class BitProxy
        {
        public:
            BitProxy(BitArray *bitarray, size_t index) noexcept;
            inline operator bool() const noexcept;
            BitProxy &operator=(bool bit) noexcept;
            BitProxy &operator=(const BitProxy &other) noexcept;

        private:
            unsigned char *m_proxy_bitarr;
            size_t m_index;
        };

    };

    /************************** Ctor & CCtor & Dtor **************************/
    /************************* operator= & operator[] ************************/

    template <size_t SIZE>
    BitArray<SIZE>::BitArray()
    {
        SetAll(false);
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
                  (other.UnconstCast()).m_bit_arr.begin());

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
        return (UnconstCast()[index]);
        //  NOTE: operator[] (non const) returns BitProxy by value so there is 
        //  no problem to reuse it
        //  cuse it will not return a referenc to a bit that the user can use
        //  (i.e, the user dosen't know BitProxy so, it canot save a 
        //  reference to a bit by declering a bit proxy variable)
        //  and thus automaticly go implicit cast to bool value
    }

    /******************************* Bitwise *******************************/

    template <size_t SIZE>
    BitArray<SIZE> &BitArray<SIZE>::operator|=(const BitArray<SIZE> &rhs_) noexcept
    {
        std::transform(m_bit_arr.begin(),
                       m_bit_arr.end(),
                       rhs_.m_bit_arr.begin(),
                       m_bit_arr.begin(),
                       std::bit_or<unsigned char>());
        return (*this);
    }
    template <size_t SIZE>
    BitArray<SIZE> &BitArray<SIZE>::operator&=(const BitArray<SIZE> &rhs_) noexcept
    {
        std::transform(m_bit_arr.begin(),
                       m_bit_arr.end(),
                       rhs_.m_bit_arr.begin(),
                       m_bit_arr.begin(),
                       std::bit_and<unsigned char>());
        return (*this);
    }

    template <size_t SIZE>
    BitArray<SIZE> &BitArray<SIZE>::operator^=(const BitArray<SIZE> &rhs_) noexcept
    {
        std::transform(m_bit_arr.begin(),
                       m_bit_arr.end(),
                       rhs_.m_bit_arr.begin(),
                       m_bit_arr.begin(),
                       std::bit_xor<unsigned char>());
        return (*this);
    }

    // template <size_t SIZE>
    // BitArray<SIZE> &BitArray<SIZE>::operator<<=(size_t shifts)
    // {
    //     BitArray<this->SIZE> cpy(*this);

    //     const size_t byte_shift = shifts / detail::CHAR_BIT;
    //     const size_t offset = shifts % detail::CHAR_BIT;

    //     std::copy(m_bit_arr.c_array() , m_bit_arr.c_array() + ,
    //               (const_cast<BitArray<SIZE> &>(other)).m_bit_arr.begin());

    //     std::transform(m_bit_arr.c_array(),
    //                    m_bit_arr.c_array(),
    //                    m_bit_arr.begin(),
    //                    m_bit_arr.begin(),
    //                    std::bit_xor<unsigned char>());

    //     BitArray<this->SIZE> mask;
    //     mask.SetAll(false);

    // }

    // 11010011 << 4
    //     |
    //     V
    // 00110000

    // 11010011 >> 4
    //     |
    //     V
    // 00001101

    //     inline BitArray &operator>>=(size_t shifts) noexcept;

    /************************** Set & Flip & Get *************************/

    template <size_t SIZE>
    void BitArray<SIZE>::SetAll(bool val) noexcept
    {
        std::fill(m_bit_arr.begin(), m_bit_arr.end(), detail::BYTE_MAX * val);
        return;
    }

    template <size_t SIZE>
    void BitArray<SIZE>::SetBit(size_t index, bool val) throw(std::out_of_range)
    {
        detail::RangeChack(index, SIZE);

        (*this)[index] = val;
        return;
    }

    template <size_t SIZE>
    bool BitArray<SIZE>::GetBit(size_t index) const throw(std::out_of_range)
    {
        detail::RangeChack(index, SIZE);

        return (*this)[index];
    }

    template <size_t SIZE>
    void BitArray<SIZE>::FlipAll() noexcept
    {
        std::transform(m_bit_arr.begin(),
                       m_bit_arr.end(),
                       m_bit_arr.begin(),
                       detail::NotByte());
        return;
    }

    template <size_t SIZE>
    void BitArray<SIZE>::FlipBit(size_t index) throw(std::out_of_range)
    {
        detail::RangeChack(index, SIZE);

        (*this)[index] = !(*this)[index];
        return;
    }

    /************************** Count & ToString *************************/

    template <size_t SIZE>
    size_t BitArray<SIZE>::Count() const noexcept
    {
        detail::Sum sum_local;
        size_t sum =
            std::accumulate(m_bit_arr.begin(),
                            m_bit_arr.end() - 1,
                            0, detail::Sum());

        return (sum_local(sum, *(m_bit_arr.end() - 1) &
                                   detail::GetMask(SIZE, M_SIZE_OF_ARRAY)));
    }

    template <size_t SIZE>
    std::string BitArray<SIZE>::ToString() const
    {
        char string[SIZE + 1] = {'\0'};

        for (size_t i = SIZE; 0 < i; --i)
        {
            string[i - 1] = (*this)[SIZE - i] + '0';
        }

        return (string);
    }

    /************************** Logical operators *************************/

    template <size_t SIZE>
    bool BitArray<SIZE>::operator==(const BitArray<SIZE> &rhs_) noexcept
    {
        unsigned char mask(detail::GetMask(SIZE, M_SIZE_OF_ARRAY));

        return (std::equal(
                    m_bit_arr.begin(),
                    m_bit_arr.begin() + (M_SIZE_OF_ARRAY - 1),
                    rhs_.m_bit_arr.begin()) &&
                ((*(m_bit_arr.end() - 1) & mask) ==
                 (*(rhs_.m_bit_arr.end() - 1) & mask)));
    }

    template <size_t SIZE>
    bool BitArray<SIZE>::operator!=(const BitArray<SIZE> &rhs_) noexcept
    {
        return !(*this == rhs_);
    }

    /********************************** Proxy **********************************/
    template <size_t SIZE>
    BitArray<SIZE>::BitProxy::BitProxy(BitArray *bitarray, size_t index) noexcept
        : m_proxy_bitarr(bitarray->m_bit_arr.c_array() + (index / detail::CHAR_BIT)),
          m_index(index % detail::CHAR_BIT)
    {
        ;
    }

    template <size_t SIZE>
    BitArray<SIZE>::BitProxy::operator bool() const noexcept
    {
        return (((*m_proxy_bitarr) >> m_index) & 1);
    }

    template <size_t SIZE>
    typename BitArray<SIZE>::BitProxy &BitArray<SIZE>::BitProxy::operator=(bool bit) noexcept
    {
        *(m_proxy_bitarr) = (*m_proxy_bitarr & ~(1 << m_index)) | (bit << m_index);
        return *this;
    }

    template <size_t SIZE>
    typename BitArray<SIZE>::BitProxy &BitArray<SIZE>::BitProxy::operator=(const BitProxy &other) noexcept
    {
        bool bit = (*(other.m_proxy_bitarr)) & (1 << other.m_index);
        return (*this = bit);
    }

    template <size_t SIZE>
    BitArray<SIZE> BitArray<SIZE>::UnconstCast() const
    {
        return ((const_cast<BitArray<SIZE> &>(*this)));
    }

} //ilrd

#ifdef noexcept
#undef noexcept
#else
#undef throw
#endif

#endif /* ILRD_RD102_BITARRAY_HPP */