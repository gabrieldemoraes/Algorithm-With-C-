//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 smart_ptr.cpp -o smart_ptr.exe
//cl /Fo.\obj\ /EHsc /O2 smart_ptr.cpp /link /out:smart_ptr.exe

#include "smart_ptr.hpp"
#include "doubly_linked_list_alt.hpp"

#include <iostream>
#include <utility>

template <typename T>
class wrapper
{
public:
    wrapper() : val(T{})
    {
        std::cout << "++> ctor: " << val << " obj addr: " << this << '\n';
    }
    
    wrapper(T val) : val(val) 
    {
        std::cout << "==> ctor: " << val << " obj addr: " << this << '\n';
    }

    wrapper<T>& operator=(const wrapper<T>& that)
    {
        val = that.val;
        std::cout << "--> ctor: " << val << " obj addr: " << this << '\n';
        return *this;
    }

    ~wrapper() 
    {
        std::cout << "==> dtor: " << val << " obj addr: " << this << '\n';
    }

    const T& value() const noexcept 
    {
        return val;
    }

private:
    T val;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const wrapper<T>& w)
{
    os << w.value();
    return os;
}

template <typename T, typename Init = T>
static inline smart_ptr::owner<T*> make_onheap(Init val)
{
    return smart_ptr::owner<T*>(new T(val));
}

template <typename T>
static void destroy(smart_ptr::owner<T*>& ptr)
{
    if (ptr)
    {
        delete ptr;
        ptr = nullptr;
    }
}

int main()
{
    using smart_ptr::scoped_ptr;
    using smart_ptr::owner;

    scoped_ptr<int> i_ptr(new int{42});
    std::cout << *i_ptr << '\n';
    i_ptr.reset(new int{84});
    std::cout << *i_ptr << '\n';
    std::cout << std::boolalpha << static_cast<bool>(i_ptr) << '\n';
    i_ptr.reset();
    std::cout << std::boolalpha << static_cast<bool>(i_ptr) << '\n';

    std::cout << "--------------------\n";

    scoped_ptr<wrapper<int>> wi_ptr(new wrapper<int>{42});
    std::cout << *wi_ptr << '\n';
    wi_ptr.reset(new wrapper<int>{84});
    std::cout << *wi_ptr << '\n';
    std::cout << std::boolalpha << static_cast<bool>(wi_ptr) << '\n';
    wi_ptr.reset();
    std::cout << std::boolalpha << static_cast<bool>(wi_ptr) << '\n';

    std::cout << "--------------------\n";

    owner<int*> oi_ptr = make_onheap<int>(42);
    std::cout << *oi_ptr << '\n';
    destroy(oi_ptr);
    oi_ptr = make_onheap<int>(84);;
    std::cout << *oi_ptr << '\n';
    std::cout << std::boolalpha << static_cast<bool>(oi_ptr) << '\n';
    destroy(oi_ptr);
    std::cout << std::boolalpha << static_cast<bool>(oi_ptr) << '\n';

    std::cout << "--------------------\n";

    owner<wrapper<int>*> owi_ptr = make_onheap<wrapper<int>>(42);
    std::cout << *owi_ptr << '\n';
    destroy(owi_ptr);
    owi_ptr = make_onheap<wrapper<int>>(84);
    std::cout << *owi_ptr << '\n';
    std::cout << std::boolalpha << static_cast<bool>(owi_ptr) << '\n';
    destroy(owi_ptr);
    std::cout << std::boolalpha << static_cast<bool>(owi_ptr) << '\n';

    std::cout << "--------------------\n";

    doubly_linked_list_alt::doubly_linked_list_alt<int> ll;
    doubly_linked_list_alt::prepend<int>(ll, 2);
    doubly_linked_list_alt::prepend<int>(ll, 1);
    doubly_linked_list_alt::append<int>(ll, 5);
    doubly_linked_list_alt::append<int>(ll, 6);

    auto display = [](const auto& x) { std::cout << x << " "; };

    std::cout << "frwd: ";
    doubly_linked_list_alt::traverse_forward(ll, display);
    std::cout << "\n";
    std::cout << "bkwd: ";
    doubly_linked_list_alt::traverse_backward(ll, display);
    std::cout << "\n";

    doubly_linked_list_alt::insert_before<int>(ll, 1, 77);
    doubly_linked_list_alt::insert_before<int>(ll, 5, 88);
    doubly_linked_list_alt::insert_after<int>(ll, 1, 99);
    doubly_linked_list_alt::insert_after<int>(ll, 5, 44);
    doubly_linked_list_alt::insert_after<int>(ll, 8, 33);
    doubly_linked_list_alt::insert_before<int>(ll, 8, 22);
    
    std::cout << "frwd: ";
    doubly_linked_list_alt::traverse_forward(ll, display);
    std::cout << "\n";
    std::cout << "bkwd: ";
    doubly_linked_list_alt::traverse_backward(ll, display);
    std::cout << "\n";

    doubly_linked_list_alt::remove_back<int>(ll);
    doubly_linked_list_alt::remove_front<int>(ll);

    std::cout << "frwd: ";
    doubly_linked_list_alt::traverse_forward(ll, display);
    std::cout << "\n";
    std::cout << "bkwd: ";
    doubly_linked_list_alt::traverse_backward(ll, display);
    std::cout << "\n";

    std::cout << "--------------------\n";
    {
        std::cout << "create\n";
        doubly_linked_list_alt::doubly_linked_list_alt<wrapper<int>> llw;
        doubly_linked_list_alt::prepend(llw, wrapper<int>{30});
        doubly_linked_list_alt::prepend(llw, wrapper<int>{20});
        doubly_linked_list_alt::append(llw, wrapper<int>{50});
        doubly_linked_list_alt::append(llw, wrapper<int>{60});

        std::cout << "\ntraverse\n";
        std::cout << "frwd: ";
        doubly_linked_list_alt::traverse_forward(ll, display);
        std::cout << "\n";
        std::cout << "bkwd: ";
        doubly_linked_list_alt::traverse_backward(ll, display);
        std::cout << "\n";

        std::cout << "\ndestroy\n";
    }
}