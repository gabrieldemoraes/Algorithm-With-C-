#ifndef FIND_DUPLICATES_HPP
#define FIND_DUPLICATES_HPP

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <algorithm>

class Solution {
public:
    std::vector<int> findDuplicates_V0(std::vector<int>& nums) 
    {
        std::map<int, int> m;
        std::map<int, int>::iterator it;
        std::vector <int> result;
        for (std::size_t i = 0; i < nums.size(); ++i)
        {
            if (i == 0)
                m.insert(std::pair<int, int>(nums[i], i));
            else
            {
                it = m.find(nums[i]);
                if (it != m.end())
                    result.push_back(nums[i]);
                else
                    m.insert(std::pair<int, int>(nums[i], i));
            }
        }
        return result;
    }

    std::vector<int> findDuplicates_V1(std::vector<int>& nums)
    {
       std::vector<int>::iterator it = std::max_element(nums.begin(), nums.end());
       std::vector<int> v(*it + 1, -1);
       std::vector<int> result;

       for (it = nums.begin(); it != nums.end(); ++it)
       {
           if (v[*it] == -1)
                v[*it] = *it;
           else
               result.push_back(*it);
       }
       return result;
    }
};

#endif /* FIND_DUPLICATES_HPP */