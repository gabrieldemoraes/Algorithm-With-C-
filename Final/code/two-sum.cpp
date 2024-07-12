//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 two-sum.cpp -o two-sum.exe
//cl /Fo.\obj\ /EHsc /O2 two-sum.cpp /link /out:two-sum.exe

#include <vector>
#include <unordered_map>

std::vector<int> two_sum(std::vector<int>& nums, int target) 
{
    std::unordered_map<int, int> t;
    t.reserve(nums.size());
    int idx = 0;
    for (int num : nums)
    {
        auto it = t.find(target - num);
        if (it != t.end())            
            return {it->second, idx};
        t.emplace(num, idx++);
    }
    return {};
}

#include <iostream>

//Test cases:
//9 4 2 7 11 15
//6 3 3 2 4
//6 2 3 3
int main()
{
    int N, target;
    std::cin >> target >> N;
    std::vector<int> nums(N, 0);
    for (int i = 0; i < N; ++i)
        std::cin >> nums[i];
    auto result = two_sum(nums, target);
    if (result.size() == 2)
    {
        std::cout << "indices " << result[0] << " and " << result[1] << " found\n";
    }
    else
    {
        std::cout << "not found\n";
    }
    return 0;
}