//g++ -O3 doubly_linked_list.cpp -o doubly_linked_list.exe
#include "doubly_linked_list.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    double_linked_list ll;
    double_linked_list::list l;

    double_linked_list::double_linked_node n(10);

    ll.append(&l, &n);
    ll.append(&l, &n);
    ll.append(&l, &n);
    ll.append(&l, &n);
    ll.append(&l, &n);

    std::cout << l.first->val << std::endl;

    return 0;
}