//g++ -O3 copyListWithRandomPointer.cpp -o copyListWithRandomPointer.exe

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "copyListWithRandomPointer.hpp"

int main()
{
    Solution s;
    //First Scneario
    /*
    Node n0(7);
    Node n1(13);
    Node n2(11);
    Node n3(10);
    Node n4(1);

    n0.next = &n1;
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;

    n1.random = &n0;
    n2.random = &n4;
    n3.random = &n2;
    n4.random = &n0;
    */
    

    // Second Scneario
    
    Node n0(1);
    Node n1(2);

    n0.next = &n1;

    n0.random = &n1;
    n1.random = &n1;
    

    /*
    Node n0(3);
    Node n1(3);
    Node n2(3);

    n0.next = &n1;
    n1.next = &n2;

    n1.random = &n0;
    */
    /*
    Node n0(3);
    Node n1(5);
    Node n2(4);
    Node n3(-9);
    Node n4(-10);
    Node n5(5);
    Node n6(0);
    Node n7(6);
    Node n8(-6);
    Node n9(3);
    Node n10(-6);
    Node n11(9);
    Node n12(-2);
    Node n13(-3);
    Node n14(-6);
    Node n15(9);
    Node n16(-2);
    Node n17(-3);
    Node n18(-1);
    Node n19(2);
    Node n20(-3);
    */
    //Node n0(-1);
    //n0.random = &n0;
    
    Node * result = s.copyRandomList(&n0);

    return 0;
}