//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include "doubly_linked_list_alt.hpp"

#include <cstddef>
#include <string>
#include <iostream>

namespace doubly_linked_list_alt
{
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

        operator const T&() const noexcept 
        { 
            return val;
        }

        friend bool operator==(const wrapper<T>& lhs, const wrapper<T>& rhs)
        {
            return lhs.val == rhs.val;
        }

        friend bool operator!=(const wrapper<T>& lhs, const wrapper<T>& rhs)
        {
            return !(lhs == rhs);
        }
        
    private:
        T val;
    };

    static void test_interactive()
    {
        std::cout << "     int: prepend an item,              +int: append an item\n";
        std::cout << "aint,int: insert after an item,     bint,int: insert before an item\n";
        std::cout << "       -: remove first item,               =: remove last item\n";
        std::cout << "    fint: remove an item (forward),     gint: remove an item (backward)\n";
        std::cout << "       >: display forward,                 <: display backward\n";
        std::cout << "       !: display info,                    c:clear all\n";
        std::cout << "     EOF: benchmark\n";

        using T = int;
        //using T = wrapper<int>;
        doubly_linked_list_alt<T> ll;
        
        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case 'c':
                clear(ll);
                break;
            case '+':
            case 'f':
            case 'g':
                try
                {
                    T x = std::stoi(cmd.substr(1));
                    if (cmd[0] == 'f')
                        remove_forward(ll, x);
                    else if (cmd[0] == 'g')
                        remove_backward(ll, x);
                    else //+
                        append(ll, x);
                }
                catch (const std::invalid_argument&)
                {
                    std::cout << "input ignored\n";
                }
                break;
            case 'a':
            case 'b':
                try
                {
                    std::size_t pos = cmd.find(',', 1);
                    if (pos == std::string::npos)
                        throw std::invalid_argument("missing ,");
                    T x = std::stoi(cmd.substr(1, pos));
                    T y = std::stoi(cmd.substr(pos + 1));
                    if (cmd[0] == 'a')
                        insert_after(ll, x, y);
                    else //'b'
                        insert_before(ll, x, y);
                }
                catch (const std::invalid_argument&)
                {
                    std::cout << "input ignored\n";
                }				
                break;
            case '-':				
                remove_front(ll);
                break;
            case '=':
                remove_back(ll);
                break;
            case '>':
                std::cout << "_ -> ";
                traverse_forward(ll, [](T& x) { std::cout << x << " -> "; });
                std::cout << "_\n";
                break;
            case '<':
                std::cout << "_ -> ";
                traverse_backward(ll, [](T& x) { std::cout << x << " -> "; });
                std::cout << "_\n";
                break;
            case '!':
                std::cout << "size: " << count(ll) << "\n";
                break;
            default:
                try
                {
                    T x = std::stoi(cmd);
                    prepend(ll, x);
                }
                catch (const std::invalid_argument&)
                {
                    std::cout << "input ignored\n";
                }
                break;
            }
        }
    }
}

int doubly_linked_list_alt_main(int argc, char *argv[], bool run_tests)
{
    using doubly_linked_list_alt::test_interactive;	
    
    if (run_tests)
    {
        test_interactive();
    }
    
    return 0;
}