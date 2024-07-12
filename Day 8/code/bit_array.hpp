//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef BIT_ARRAY_HPP
#define BIT_ARRAY_HPP

#include <cstddef>
#include <cstdint>

namespace bit_array
{
    class bit_array
    {
        public:
            bit_array(std::size_t size, bool default_value = false)
                : length(size), bits(new std::int32_t[bit_size(size)]) {}

            ~bit_array()
            {
                delete[] bits;
            }
            
            const std::size_t size() const 
            { 
                return length; 
            }

            bool get(std::size_t index) const
            {
                return (bits[index >> 5] & (1 << index)) != 0;
            }

            void set(std::size_t index, bool value)
            {
                if(value) on(index); else off(index);
            }

            void on(std::size_t index)
            {
                int& b = bits[index >> 5];
                b |= (1 << index);
            }

            void off(std::size_t index)
            {
                int& b = bits[index >> 5];
                b &= ~(1 << index);
            }

        private:
            static std::size_t bit_size(std::size_t size)
            {
                return (size - 1 + 32) >> 5;
            }

        private:
            std::size_t length;
            std::int32_t* bits = nullptr;
    };
}

#endif /* BIT_ARRAY_HPP */