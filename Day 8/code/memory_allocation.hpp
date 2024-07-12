//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef MEMORY_ALLOCATION_HPP
#define MEMORY_ALLOCATION_HPP

namespace memory_allocation
{
    template <typename T>
    struct conventional_memory_allocation
    {
        static inline T* alloc(std::size_t n)
        {
            T* ptr = new T[n];
            return ptr;
        }

        static inline void dealloc(void* ptr)
        {
            delete[](reinterpret_cast<T*>(ptr));
        }
    };

    template <typename T>
    struct nonconventional_memory_allocation
    {
        static inline T* alloc(std::size_t n)
        {
            T* ptr = static_cast<T*>(::operator new(sizeof(T) * n));
            return ptr;
        }

        static inline void dealloc(void* ptr)
        {
            ::operator delete(reinterpret_cast<T*>(ptr));
        }
    };
}

#endif /* MEMORY_ALLOCATION_HPP */