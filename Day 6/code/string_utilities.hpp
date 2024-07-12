//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef STRING_UTILITIES_HPP
#define STRING_UTILITIES_HPP

#include <algorithm>
#include <string>
#include <cctype>
#include <cstddef>
#include <functional>
#include <vector>
#include <iterator>
#include <limits>

namespace string_utilities
{
    template<typename UnaryPredicate>
    static inline std::string& strip_left_if(std::string& source, UnaryPredicate is_space)
    {
        auto first = source.begin();
        auto is_not_space = std::not1(std::function<bool(char)>(is_space));
        auto last = std::find_if(first, source.end(), is_not_space);
        source.erase(first, last);
        return source;
    }

    static inline std::string& strip_left(std::string& source)
    {
        return strip_left_if(source, [](int ch) { return std::isspace(ch); });
    }

    static inline std::string strip_left_copy(std::string source)
    {
        return std::move(strip_left(source));
    }

    template<typename UnaryPredicate>
    static inline std::string strip_left_copy_if(std::string source, UnaryPredicate is_space)
    {
        return std::move(strip_left_if(source, is_space));
    }

    template<typename UnaryPredicate>
    static inline std::string& strip_right_if(std::string& source, UnaryPredicate is_space)
    {
        auto is_not_space = std::not1(std::function<bool(char)>(is_space));
        auto first = std::find_if(source.rbegin(), source.rend(), is_not_space).base();
        auto last = source.end();
        source.erase(first, last);
        return source;
    }

    static inline std::string& strip_right(std::string& source)
    {
        return strip_right_if(source, [](int ch) { return std::isspace(ch); });
    }

    static inline std::string strip_right_copy(std::string source)
    {
        return std::move(strip_right(source));
    }

    template<typename UnaryPredicate>
    static inline std::string strip_right_copy_if(std::string source, UnaryPredicate is_space)
    {
        return std::move(strip_right_if(source, is_space));
    }

    template<typename UnaryPredicate>
    static inline std::string& strip_if(std::string& source, UnaryPredicate is_space)
    {
        return strip_right_if(strip_left_if(source, is_space), is_space);
    }

    static inline std::string& strip(std::string& source)
    {
        return strip_if(source, [](int ch) { return std::isspace(ch); });
    }

    static inline std::string strip_copy(std::string source)
    {
        return std::move(strip(source));
    }

    template<typename UnaryPredicate>
    static inline std::string strip_copy_if(std::string source, UnaryPredicate is_space)
    {
        return std::move(strip_if(source, is_space));
    }

    static inline bool contains(const std::string& source, const std::string& pattern)
    {
        return source.find(pattern) != std::string::npos;
    }

    static inline bool starts_with(const std::string& source, const std::string& pattern)
    {
        std::size_t n = source.size(), m = pattern.size();
        if (m <= n)
            return std::equal(pattern.begin(), pattern.end(), source.begin());
        return false;
    }

    static inline bool ends_with(const std::string& source, const std::string& pattern)
    {
        std::size_t n = source.size(), m = pattern.size();
        if (m <= n)
            return std::equal(pattern.begin(), pattern.end(), source.begin() + (n - m));
        return false;
    }

    namespace vector_support
    {
        template<typename UnaryPredicate>
        static inline std::vector<char>& strip_left_if(std::vector<char>& source, UnaryPredicate is_space)
        {
            auto first = source.begin();
            auto is_not_space = std::not1(std::function<bool(char)>(is_space));
            auto last = std::find_if(first, source.end(), is_not_space);
            auto n = std::distance(first, last);
            if (n)
            {
                std::move(last, source.end(), first);
                source.resize(source.size() - n);
            }
            return source;
        }

        static inline std::vector<char>& strip_left(std::vector<char>& source)
        {
            return strip_left_if(source, [](int ch) { return std::isspace(ch); });
        }

        static inline std::vector<char> strip_left_copy(std::vector<char> source)
        {
            return std::move(strip_left(source));
        }

        template<typename UnaryPredicate>
        static inline std::vector<char> strip_left_copy_if(std::vector<char> source, UnaryPredicate is_space)
        {
            return std::move(strip_left_if(source, is_space));
        }

        template<typename UnaryPredicate>
        static inline std::vector<char>& strip_right_if(std::vector<char>& source, UnaryPredicate is_space)
        {
            auto is_not_space = std::not1(std::function<bool(char)>(is_space));
            auto first = std::find_if(source.rbegin(), source.rend(), is_not_space).base();
            auto last = source.end();
            auto n = std::distance(first, last);
            if (n) source.resize(source.size() - n);
            return source;
        }

        static inline std::vector<char>& strip_right(std::vector<char>& source)
        {
            return strip_right_if(source, [](int ch) { return std::isspace(ch); });
        }

        static inline std::vector<char> strip_right_copy(std::vector<char> source)
        {
            return std::move(strip_right(source));
        }

        template<typename UnaryPredicate>
        static inline std::vector<char> strip_right_copy_if(std::vector<char> source, UnaryPredicate is_space)
        {
            return std::move(strip_right_if(source, is_space));
        }

        template<typename UnaryPredicate>
        static inline std::vector<char>& strip_if(std::vector<char>& source, UnaryPredicate is_space)
        {
            return strip_right_if(strip_left_if(source, is_space), is_space);
        }

        static inline std::vector<char>& strip(std::vector<char>& source)
        {
            return strip_if(source, [](int ch) { return std::isspace(ch); });
        }

        static inline std::vector<char> strip_copy(std::vector<char> source)
        {
            return std::move(strip(source));
        }

        template<typename UnaryPredicate>
        static inline std::vector<char> strip_copy_if(std::vector<char> source, UnaryPredicate is_space)
        {
            return std::move(strip_if(source, is_space));
        }

        static inline bool contains(const std::vector<char>& source, const std::vector<char>& pattern)
        {
            return std::search(source.begin(), source.end(), pattern.begin(), pattern.end()) == source.end();
        }

        static inline bool starts_with(const std::vector<char>& source, const std::vector<char>& pattern)
        {
            std::size_t n = source.size(), m = pattern.size();
            if (m <= n)
                return std::equal(pattern.begin(), pattern.end(), source.begin());
            return false;
        }

        static inline bool ends_with(const std::vector<char>& source, const std::vector<char>& pattern)
        {
            std::size_t n = source.size(), m = pattern.size();
            if (m <= n)
                return std::equal(pattern.begin(), pattern.end(), source.begin() + (n - m));
            return false;
        }
    }

    namespace iterator_support
    {
        template<typename InputIterator, typename OutputIterator, typename UnaryPredicate>
        static inline OutputIterator strip_left_if(InputIterator first, InputIterator last, OutputIterator result, UnaryPredicate predicate)
        {
            using T = typename std::iterator_traits<InputIterator>::value_type;
            auto not_predicate = std::not1(std::function<bool(T)>(predicate));
            return std::copy(std::find_if(first, last, not_predicate), last, result);
        }

        template<typename BidirectionalIterator, typename OutputIterator, typename UnaryPredicate>
        static inline OutputIterator strip_right_if(BidirectionalIterator first, BidirectionalIterator last, OutputIterator result, UnaryPredicate predicate)
        {
            while (first != last)
            {
                last = std::prev(last);
                if (!predicate(*last))
                    break;
            }
            if (std::distance(first, last) && !predicate(*last))
                last = std::next(last);				
            return std::copy(first, last, result);
        }

        template<typename BidirectionalIterator, typename UnaryPredicate>
        static inline BidirectionalIterator strip_if(BidirectionalIterator first, BidirectionalIterator last, UnaryPredicate predicate)
        {
             return string_utilities::iterator_support::strip_right_if
                   (
                        first, 
                        string_utilities::iterator_support::strip_left_if(first, last, first, predicate),
                        first, 
                        predicate
                   );
        }
    }
}

#endif /* STRING_UTILITIES_HPP */