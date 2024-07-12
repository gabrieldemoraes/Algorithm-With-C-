//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2021 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 type_checker.cpp -o type_checker.exe
//cl /Fo.\obj\ /EHsc /O2 type_checker.cpp /link /out:type_checker.exe

#include "type_checker.hpp"

#include <utility>
#include <string>
#include <vector>
#include <memory>

struct C0
{
    int n;
};

struct C1
{
    explicit C1(int n) : n(n) {}
    int n;
};

struct C2
{
    C2() : n(42) {}
    int n;
};

struct C3
{
    C3() : n(42) {}
    C3& operator=(C3&) = delete;
    int n;
};

struct C4
{
    int n;
    bool operator==(const C4& that) const { return that.n == n; }
};
//static bool operator!=(const C4& lhs, const C4& rhs) { return !(lhs == rhs); }

struct C5
{
    C5() {};
    ~C5() {};
    C5(const C5& that) : n(that.n) {}
    C5& operator=(const C5& that) { n = that.n; return *this; }
    bool operator==(const C5& that) const { return that.n == n; }
    bool operator!=(const C5& that) const { return !(*this == that); }
    int n;
};

template <typename T>
struct factory
{
    static_assert(type_checker::is_regular<T>(), "T should be a regular type");
    static std::vector<T> create_empty_vector() { return std::vector<T>(); }
};

#include <iostream>
#include <iomanip>

template <typename T>
void display_semiregular_check(const char* _typename)
{
    std::cout << std::setw(12) << _typename << " is semiregular? " 
              << std::boolalpha << type_checker::is_semiregular<T>() << '\n';
}

template <typename T>
void display_regular_check(const char* _typename)
{
    std::cout << std::setw(12) << _typename << " is     regular? " 
              << std::boolalpha << type_checker::is_regular<T>() << '\n';
}

int main()
{
    display_semiregular_check<int>("int");
    display_regular_check<int>("int");
    display_semiregular_check<double>("double");
    display_regular_check<double>("double");
    display_semiregular_check<std::string>("std::string");
    display_regular_check<std::string>("std::string");
    display_semiregular_check<int&&>("int&&");
    display_regular_check<int&&>("int&&");
    display_semiregular_check<int&>("int&");
    display_regular_check<int&>("int&");
    display_semiregular_check<C0>("C0");
    display_regular_check<C0>("C0");
    display_semiregular_check<C1>("C1");
    display_regular_check<C1>("C1");
    display_semiregular_check<C2>("C2");
    display_regular_check<C2>("C2");
    display_semiregular_check<C3>("C3");
    display_regular_check<C3>("C3");
    display_semiregular_check<C4>("C4");
    display_regular_check<C4>("C4");
    display_semiregular_check<C5>("C5");
    display_regular_check<C5>("C5");
    factory<int>::create_empty_vector();
    //factory<int&>::create_empty_vector();    
}