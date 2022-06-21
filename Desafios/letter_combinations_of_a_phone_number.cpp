//g++ -O3 letter_combinations_of_a_phone_number.cpp -o letter_combinations_of_a_phone_number.exe
#include "letter_combinations_of_a_phone_number.hpp"

int main(int argc, char *argv[])
{
    Solution s;

    std::vector<std::string> result = s.letterCombinations("239");   

    for(int i = 0; i < result.size(); ++i)
    {
        std::cout << result[i] << std::endl;
    }

    return 0;
}