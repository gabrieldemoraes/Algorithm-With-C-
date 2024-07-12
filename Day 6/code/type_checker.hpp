//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef TYPE_CHECKER_HPP
#define TYPE_CHECKER_HPP

#include <type_traits>

namespace type_checker
{
    namespace internal
    {
        template<typename, typename, typename, typename, typename T> struct _5th { typedef T type; };
        
        template <typename T, typename U>
        static typename _5th<decltype((std::declval<T>() == std::declval<U>())), 
                             decltype((std::declval<T>() != std::declval<U>())),
                             decltype((std::declval<U>() == std::declval<T>())),
                             decltype((std::declval<U>() != std::declval<T>())), std::true_type>::type is_equality_comparable_test(int);
        
        template <typename, typename>
        static std::false_type is_equality_comparable_test(...);
        
        template <typename T, typename U = T> struct is_equality_comparable : 
            public std::integral_constant<bool, !(std::is_void<T>::value || std::is_void<U>::value) &&
                                                decltype((is_equality_comparable_test<T, U>(0)))::value> {};
            
        //definition: https://en.cppreference.com/w/cpp/concepts/semiregular
        template <typename T> struct is_semiregular : 
            public std::integral_constant<bool, std::is_default_constructible<T>::value &&
                                                std::is_copy_constructible<T>::value &&
                                                std::is_copy_assignable<T>::value &&                                                
                                                std::is_destructible<T>::value> {};
        
        //definition: https://en.cppreference.com/w/cpp/concepts/regular
        template <typename T> struct is_regular :
            public std::integral_constant<bool, is_semiregular<T>::value &&
                                                is_equality_comparable<T>::value> {};
    }

    template <typename T>
    static constexpr bool is_semiregular() { return internal::is_semiregular<T>::value; }

    template <typename T>
    static constexpr bool is_regular() { return internal::is_regular<T>::value; }
}

#endif /* TYPE_CHECKER_HPP */