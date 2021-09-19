#ifndef ILRD_RD102_BITARRAY_DETAIL_HPP
#define ILRD_RD102_BITARRAY_DETAIL_HPP

#include <cstddef> //size_t
namespace ilrd
{
    namespace detail
    {
        static const size_t BYTE_MAX(0xFF);
        const size_t CHAR_BIT(8);

        size_t BitArrCountOnLUT(const unsigned char &bit_array);
        inline unsigned char GetMask(size_t size, size_t n_bytes);
        inline void RangeChack(size_t index, size_t size);

        class NotByte
        {
        public:
            inline unsigned char operator()(unsigned char byte);
        };

        class Sum
        {
        public:
            inline size_t operator()(size_t sum, unsigned char byte);
        };


    /********************************** Impl **********************************/

        unsigned char NotByte::operator()(unsigned char byte)
        {
            return (~byte);
        }

        size_t Sum::operator()(size_t sum, unsigned char byte)
        {
            return (sum + (size_t)(detail::BitArrCountOnLUT(byte)));
        }

        unsigned char GetMask(size_t size, size_t n_bytes)
        {
            unsigned char mask(0xFF);
            return (mask = ~(mask << (size - (detail::CHAR_BIT * (n_bytes - 1)))));
        }

        void RangeChack(size_t index, size_t size)
        {
            if (index >= size)
            {
                throw(std::out_of_range("out_of_range"));
            }

            return;
        }

    } //detail
} //ilrd

#endif /* ILRD_RD102_BITARRAY_DETAIL_HPP */