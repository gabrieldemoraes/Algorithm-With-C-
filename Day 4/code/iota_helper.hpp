//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include <numeric>
#include <random>
#include <functional>

/*

//https://github.com/llvm-mirror/libcxx/blob/master/include/numeric#L455

template <class _ForwardIterator, class _Tp>
inline _LIBCPP_INLINE_VISIBILITY
void
iota(_ForwardIterator __first, _ForwardIterator __last, _Tp __value_)
{
    for (; __first != __last; ++__first, (void) ++__value_)
        *__first = __value_;
}

*/

namespace iota_helper
{
    namespace internal
    {
        template<typename T>
        struct iota_step final
        {
            explicit iota_step(T init, const T increment) 
                : next(init), step(increment) {}

            iota_step& operator++()
            {
                next += step;
                return *this;
            }

            operator T() const { return next; }

            iota_step() = delete; //default-constructible	
            iota_step(const iota_step&) = default; //copy-constructible
            iota_step& operator=(const iota_step&) = default; //copy-assignable
            ~iota_step() = default; //destructor

        private:
            T next;
            const T step;
        };

        template<typename T>
        struct iota_random final
        {
            explicit iota_random(const T minInclusive, const T maxInclusive, unsigned int seed = 5489U)
                : rnd(std::bind(std::uniform_int_distribution<T>(minInclusive, maxInclusive), std::default_random_engine(seed)))
            {
                next = rnd();            
            }

            iota_random& operator++()
            {
                next = rnd();
                return *this;
            }

            operator T() const { return next; }

            iota_random() = delete; //default-constructible	
            iota_random(const iota_random&) = default; //copy-constructible
            iota_random& operator=(const iota_random&) = default; //copy-assignable
            ~iota_random() = default; //destructor

        private:
            T next;
            std::function<T(void)> rnd;
        };
    }

    template<typename T>
    internal::iota_step<T> iota_step(T init, const T increment) 
    { 
        return internal::iota_step<T>(init, increment); 
    }

    template<typename T>
    internal::iota_random<T> iota_random(const T minInclusive, const T maxInclusive, unsigned int seed = 5489U) 
    { 
        return internal::iota_random<T>(minInclusive, maxInclusive, seed); 
    }
}