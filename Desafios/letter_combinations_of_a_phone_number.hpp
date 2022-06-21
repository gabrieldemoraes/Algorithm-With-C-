#include <iostream>
#include <vector>
#include <string>
#include <map>

class Solution {
public:
    std::vector<const char*> D;
    void inserting_values_in_D(std::vector<const char*>& D)
    {
        D.push_back("abc");
        D.push_back("def");
        D.push_back("ghi");
        D.push_back("jkl");
        D.push_back("mno");
        D.push_back("pqrs");
        D.push_back("tuv");
        D.push_back("wxyz");
    }
    
    void lc_rec(int i, const std::string& digits, std::string a, std::vector<std::string>& acc)
    {
        if(i == digits.size())
        {
            acc.push_back(a);
            return;
        }   

        const char* p = D[digits[i] - '2'];
        
        while(*p != '\0')
        {
            lc_rec(i + 1, digits, a + *p, acc);
            ++p;
        }
    }

    std::vector<std::string> letterCombinations(std::string digits)
    {
        inserting_values_in_D(D);
        std::vector<std::string> acc;
        if(digits.empty())
            return acc;
        acc.reserve(256);
        lc_rec(0, digits, "", acc);

        return acc;
    }
}; 