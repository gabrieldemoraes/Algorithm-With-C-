//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef VEC2D_HPP
#define VEC2D_HPP

#include <utility>
#include <limits>
#include <string>
#include <functional>

class vec2d
{
public:
    vec2d() : vec2d(0., 0.) {}
    
    vec2d(double x, double y)
        : v(std::make_pair(x, y))
    {}

    vec2d(const vec2d& that) 
        : vec2d(that.v.first, that.v.second)
    {}

    vec2d& operator=(const vec2d& that)
    {
        if (this != &that)
        {
            v.first = that.v.first;
            v.second = that.v.second;
        }
        return *this;
    }

    double operator[](int i) const
    {
        //assert i < 2
        if (i == 0) return v.first;
        if (i == 1) return v.second;
        return std::numeric_limits<double>::infinity();
    }

    bool operator==(vec2d that) const
    {
        return v.first == that.v.first && v.second == that.v.second;
    }

    bool operator!=(vec2d that) const
    {
        return !(operator==(that));
    }

    vec2d& operator+=(vec2d that)
    {
        v.first += that.v.first;
        v.second += that.v.second;
        return *this;
    }

    vec2d& operator-=(vec2d that)
    {
        v.first -= that.v.first;
        v.second -= that.v.second;
        return *this;
    }

    vec2d& operator*=(double scalar)
    {
        v.first *= scalar;
        v.second *= scalar;
        return *this;
    }

    bool operator<(const vec2d& that) const
    {
        if (that.v.first < v.first)
            return false;
        if (that.v.second < v.second)
            return false;
        return *this != that;
    }

    bool operator>(const vec2d& that)
    {
        return that < *this;
    }

    bool operator<=(const vec2d& that)
    {
        return !(that < *this);
    }

    bool operator>=(const vec2d& that)
    {
        return !(*this < that);
    }

private:
    std::pair<double, double> v;
};

inline static vec2d operator+(vec2d v0, vec2d v1)
{
    v0 += v1;
    return v1;
}

inline static vec2d operator-(vec2d v0, vec2d v1)
{
    v0 -= v1;
    return v0;
}

inline static vec2d operator*(vec2d v, double scalar)
{
    v *= scalar;
    return v;
}

inline static vec2d operator*(double scalar, vec2d v)
{
    return operator*(v, scalar);
}

namespace std 
{
    inline static std::string to_string(vec2d v)
    {
        std::string result = "(";
        result += std::to_string(v[0]);
        result += ", ";
        result += std::to_string(v[1]);
        result += ")";
        return result;
    }

    template <>
    struct hash<vec2d>
    {
        std::size_t operator()(const vec2d& v) const
        {
            const std::size_t PRIME = 61;
            std::size_t h =  v[0] * PRIME + v[1];
            return h;
        }
    };
}

#endif /* VEC2D_HPP */