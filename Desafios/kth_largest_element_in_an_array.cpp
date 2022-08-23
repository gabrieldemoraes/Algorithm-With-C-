//g++ -O3 kth_largest_element_in_an_array.cpp -o kth_largest_element_in_an_array.exe
// make_heap, pop_heap ou push_heap, pop_heap
#include "kth_largest_element_in_an_array.hpp"
#include <vector>

int main()
{
    Solution s;
    
    int myints[] = {3,2,1,5,6,4};
    std::vector<int> myvector (myints, myints+6);

    int result = s.findKthLargest(myvector, 2);

    std::cout << result << std::endl;

    return 0;
}