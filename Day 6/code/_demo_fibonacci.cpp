//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 _demo_fibonacci.cpp -o _demo_fibonacci.exe
//cl /Fo.\obj\ /EHsc /O2 _demo_fibonacci.cpp /link /out:_demo_fibonacci.exe

#include <cstdint>
#include <map>
#include <iostream>

//recursive
std::uint64_t fibonacci(std::uint8_t n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

//tail recursive
std::uint64_t fibonacci_tailrec(std::uint8_t n, std::uint64_t current, std::uint64_t next)
{
    if (n == 0) return current;
    return fibonacci_tailrec(n - 1, next, current + next);
}

static long long fibonacci_tailrec(std::uint8_t n)
{
    return fibonacci_tailrec(n, 0, 1);
}

//dynamic programming: memoization
class fibonacci_with_memoization
{
    std::map<std::uint8_t, std::uint64_t> memo;
public:
    std::uint64_t operator()(std::uint8_t n)
    {
        if (n == 0) return 0;
        if (n == 1) return 1;
        auto it = memo.find(n);
        if (it != memo.end())
            return it->second;
        std::uint64_t result = (operator()(n - 1) + operator()(n - 2));
        memo.emplace(n, result);
        return result;
    }
};

int main()
{
    for (int i = 0; i < 10; ++i)
        std::cout << i << ' ' << fibonacci(i) << '\n';

    std::cout << '\n';

    for (int i = 0; i < 10; ++i)
        std::cout << i << ' ' << fibonacci_tailrec(i) << '\n';

    std::cout << '\n';

    fibonacci_with_memoization fibonacci_memo;
    for (int i = 0; i < 10; ++i)
        std::cout << i << ' ' << fibonacci_memo(i) << '\n';

    return 0;
}