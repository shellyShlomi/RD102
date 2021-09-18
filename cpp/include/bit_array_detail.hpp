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
        unsigned char GetMask(size_t size, size_t n_bytes);
        void RangeChack(size_t index, size_t size);

        class NotByte
        {
        public:
            unsigned char operator()(unsigned char &byte);
        };

        class Sum
        {
        public:
            size_t operator()(size_t sum, unsigned char byte);
        };

    } //detail
} //ilrd

#endif /* ILRD_RD102_BITARRAY_DETAIL_HPP */