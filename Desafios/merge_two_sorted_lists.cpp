//g++ -O3 merge_two_sorted_lists.cpp -o merge_two_sorted_lists.exe

#include <iostream>

#include "merge_two_sorted_lists.hpp"


int main(int argc, char *argv[])
{
    Solution s;

    ListNode ln1(-9);
    ListNode ln2(3);
    //ListNode ln3(4);
    ln1.next = &ln2;
    //ln2.next = &ln3;
    
    ListNode n1(5);
    ListNode n2(7);
    //ListNode n3(4);
    n1.next = &n2;
    //n2.next = &n3;


    s.mergeTwoLists(&ln1, &n1);

}