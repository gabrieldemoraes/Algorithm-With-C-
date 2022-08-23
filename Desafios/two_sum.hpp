
#include <iostream>
#include <vector>
#include <map>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::vector<int> answer;
        std::map<int, int> map;

        for(int i = 0; i < nums.size(); i++)
        {
            if(map.find(target - nums[i]) == map.end())
                map[nums[i]] = i;
            else
            {
                answer.push_back(map.find(target - nums[i])->second);
                answer.push_back(i);
                return answer;
            }
        }
        return answer;
    }
};