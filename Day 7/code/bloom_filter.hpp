//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <limits>
#include <functional>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <sstream>
#include <iomanip>

namespace bloom_filter
{
    namespace internal
    {
        inline static std::uint64_t rotate_left(std::uint64_t val, std::int8_t n)
        {
            return (val << n) | (val >> (64 - n));
        }

        inline static std::uint64_t getblock64(const std::uint64_t* p, int i)
        {
            return p[i];
        }

        inline static std::uint64_t getint64(const uint8_t* p, int i)
        {
            return static_cast<std::uint64_t>(p[i]);
        }

        inline static std::uint64_t fmix64(std::uint64_t k)
        {
            k ^= k >> 33;
            k *= 0xff51afd7ed558ccdLLU;
            k ^= k >> 33;
            k *= 0xc4ceb9fe1a85ec53LLU;
            k ^= k >> 33;

            return k;
        }

        inline static std::uint64_t swap_endianess(std::uint64_t val)
        {
            auto b0 = (val & 0x00000000000000ff) << 56ULL;
            auto b1 = (val & 0x000000000000ff00) << 40ULL;
            auto b2 = (val & 0x0000000000ff0000) << 24ULL;
            auto b3 = (val & 0x00000000ff000000) <<  8ULL;
            auto b4 = (val & 0x000000ff00000000) >>  8ULL;
            auto b5 = (val & 0x0000ff0000000000) >> 24ULL;
            auto b6 = (val & 0x00ff000000000000) >> 40ULL;
            auto b7 = (val & 0xff00000000000000) >> 56ULL;
            return b0 | b1 | b2 | b3 | b4 | b5 | b6 | b7;
        }

        //adapted from MurmurHash3_x64_128: https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp
        static std::pair<std::uint64_t, std::uint64_t> murmur3_128(const void* key, const int len, const uint32_t seed, bool endianess_reverse = false)
        {
            const std::uint8_t* data = static_cast<const std::uint8_t*>(key);
            const int nblocks = len / 16;
            const std::uint64_t c1 = 0x87c37b91114253d5LLU;
            const std::uint64_t c2 = 0x4cf5ad432745937fLLU;

            std::uint64_t h1 = seed, h2 = seed;

            //----------
            // body

            const std::uint64_t * blocks = reinterpret_cast<const std::uint64_t*>(data);

            for (int i = 0; i < nblocks; ++i)
            {
                std::uint64_t k1 = getblock64(blocks, i * 2 + 0);
                std::uint64_t k2 = getblock64(blocks, i * 2 + 1);
                k1 *= c1; k1 = rotate_left(k1, 31); k1 *= c2; h1 ^= k1;
                h1 = rotate_left(h1, 27); h1 += h2; h1 = h1 * 5 + 0x52dce729;
                k2 *= c2; k2 = rotate_left(k2, 33); k2 *= c1; h2 ^= k2;
                h2 = rotate_left(h2, 31); h2 += h1; h2 = h2 * 5 + 0x38495ab5;
            }

            //----------
            // tail

            const std::uint8_t* tail = reinterpret_cast<const std::uint8_t*>(data + nblocks * 16);
            std::uint64_t k1 = 0, k2 = 0;
            switch (len & 15)
            {
            case 15: k2 ^= getint64(tail, 14) << 48;
            case 14: k2 ^= getint64(tail, 13) << 40;
            case 13: k2 ^= getint64(tail, 12) << 32;
            case 12: k2 ^= getint64(tail, 11) << 24;
            case 11: k2 ^= getint64(tail, 10) << 16;
            case 10: k2 ^= getint64(tail, 9) << 8;
            case  9: k2 ^= getint64(tail, 8) << 0;
                k2 *= c2; k2 = rotate_left(k2, 33); k2 *= c1; h2 ^= k2;

            case  8: k1 ^= getint64(tail, 7) << 56;
            case  7: k1 ^= getint64(tail, 6) << 48;
            case  6: k1 ^= getint64(tail, 5) << 40;
            case  5: k1 ^= getint64(tail, 4) << 32;
            case  4: k1 ^= getint64(tail, 3) << 24;
            case  3: k1 ^= getint64(tail, 2) << 16;
            case  2: k1 ^= getint64(tail, 1) << 8;
            case  1: k1 ^= getint64(tail, 0) << 0;
                k1 *= c1; k1 = rotate_left(k1, 31); k1 *= c2; h1 ^= k1;
            };

            //----------
            // finalization

            h1 ^= len; h2 ^= len;
            h1 += h2; h2 += h1;
            h1 = fmix64(h1); h2 = fmix64(h2);
            h1 += h2; h2 += h1;

            if (endianess_reverse)
            {
                h1 = swap_endianess(h1);
                h2 = swap_endianess(h2);
            }

            return std::make_pair(h1, h2);
        }

        template<typename T>
        struct bloom_filter_pointer_size
        {
            inline static const void* get_pointer(const T& value) { return &value; }
            inline static std::size_t get_size(const T& value) { return sizeof(T); }
        };

        template<>
        struct bloom_filter_pointer_size<std::string>
        {
            inline static const void* get_pointer(const std::string& value) { return value.c_str(); }
            inline static std::size_t get_size(const std::string& value) { return value.size(); }
        };

        template<typename T>
        struct bloom_filter_hashes : private bloom_filter_pointer_size<T>
        {
            using Base = bloom_filter_pointer_size<T>;

            std::pair<std::uint64_t, std::uint64_t> hashes_of(const T& value) const
            {
                const void* ptr = Base::get_pointer(value);
                int len = static_cast<int>(Base::get_size(value));
                return murmur3_128(ptr, len, 1337);
                //return murmur3_128(ptr, len, 0, true);
                //return murmur3_128(ptr, len, 1, true);
                //return murmur3_128(ptr, len, 3, true);
            }
        };
    }

    //bloom_filter interface
    /*
    bool add(const T& value);
    bool exists(const T& value) const;
    void reset();
    std::vector<std::uint64_t> indices(const T& value) const;    
    */

    template<typename T>
    class bloom_filter final : private internal::bloom_filter_hashes<T>
    {
        using Base = internal::bloom_filter_hashes<T>;
        const std::uint64_t MAX_LONG = std::numeric_limits<std::uint64_t>::max();
        std::vector<bool> bits;
        std::int32_t number_of_hash_functions;
    public:
        bloom_filter(std::size_t length, std::int32_t number_of_hash_functions)
            : bits(length, false), number_of_hash_functions(number_of_hash_functions)
        {
            if (length == 0) throw std::runtime_error("length must be greater than 0");
        }

        bool add(const T& value)
        {
            std::uint64_t h1, h2;
            std::tie(h1, h2) = Base::hashes_of(value);
            bool changed = false;
            int i = number_of_hash_functions;
            while (i--)
            {
                auto index = static_cast<std::size_t>((h1 & MAX_LONG) % bits.size());
                changed |= !bits[index];
                bits[index] = true;
                h1 += h2;
            }
            return changed;
        }

        bool exists(const T& value) const
        {
            std::uint64_t h1, h2;
            std::tie(h1, h2) = Base::hashes_of(value);
            int i = number_of_hash_functions;
            while (i--)
            {
                auto index = static_cast<std::size_t>((h1 & MAX_LONG) % bits.size());
                if (!bits[index])
                    return false;
                h1 += h2;
            }
            return true;
        }

        void reset()
        {
            std::fill(bits.begin(), bits.end(), false);
        }

        std::vector<std::uint64_t> indices(const T& value) const
        {
            std::uint64_t h1, h2;
            std::tie(h1, h2) = Base::hashes_of(value);
            std::vector<std::uint64_t> temp(number_of_hash_functions, 0);
            for (std::size_t i = 0; i < number_of_hash_functions; ++i, h1 += h2)
                temp[i] = static_cast<std::size_t>((h1 & MAX_LONG) % bits.size());
            return temp;
        }

        std::string to_string(const T& value, std::streamsize valuew = 8, std::streamsize hashw = 4) const
        {
            std::stringstream ss;
            ss << std::setw(valuew) << value;
            for (auto index : indices(value))
                ss << "[" << std::dec << std::setw(hashw) << index << "]";
            return std::move(ss.str());
        }
    };

    inline static std::int32_t optimal_number_of_hash_functions(std::int64_t expected_insertions, std::int64_t total_number_of_bits)
    {
        std::int64_t n = expected_insertions, m = total_number_of_bits;
        return static_cast<std::int32_t>(std::max(1.0, std::round(static_cast<double>(m) / n * std::log(2.0))));
    }

    inline static std::size_t optimal_number_of_bits(std::int64_t expected_insertions, double expected_false_positive_probability)
    {
        std::int64_t n = expected_insertions; double p = expected_false_positive_probability;
        if (p == 0) p = std::numeric_limits<double>::min();
        return static_cast<std::size_t>(-n * std::log(p) / (std::log(2.0) * std::log(2.0)));
    }

    template<typename T>
    bloom_filter<T> make_bloom_filter(std::int64_t expected_insertions, double expected_false_positive_probability)
    {
        if (!expected_insertions) expected_insertions = 1;
        auto bits_length = optimal_number_of_bits(expected_insertions, expected_false_positive_probability);
        auto number_of_hash_functions = optimal_number_of_hash_functions(expected_insertions, bits_length);
        return bloom_filter<T>(bits_length, number_of_hash_functions);
    }
}

#endif /* BLOOM_FILTER_HPP */