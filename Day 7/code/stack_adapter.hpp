//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef STACK_ADAPTER_HPP
#define STACK_ADAPTER_HPP

#include "dynamic_array.hpp"
#include <vector>
#include <deque>

namespace stack_adapter
{
    //stack's underlying container interface
    /*
    bool empty() const;
    size_t size() const;
    T& back();
    void push_back(const T&);
    void pop_back();
    */

    //container adapter
    template <typename T, typename TContainer = std::deque<T>>
    class stack_adapter
    {
    public:
        using value_type = T;
        using container_type = TContainer;
        using size_type = typename container_type::size_type;

        stack_adapter() = default;
        ~stack_adapter() = default;
        stack_adapter(const stack_adapter<T, TContainer>&) = delete;
        stack_adapter<T, TContainer>& operator=(const stack_adapter<T, TContainer>&) = delete;

        bool empty() const
        {
            return underlying_container.empty();
        }

        size_type size() const
        {
            return underlying_container.size();
        }

        T& top()
        {
            return underlying_container.back();
        }

        void push(const T& val)
        {
            underlying_container.push_back(val);
        }

        void pop()
        {
            underlying_container.pop_back();
        }

        void swap(stack_adapter<T, TContainer>& that)
        {
            if (&that != this)
            {
                underlying_container.swap(that.underlying_container);
            }
        }

    private:
        container_type underlying_container;
    };

    //underlying container adapter
    template<typename T>
    class dynamic_array_adapter
    {
    public:
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = T*;
        using const_pointer = const T*;
        using size_type = size_t;
        using iterator = T*;
        using const_iterator = const T*;

        bool empty() const
        {
            return storage.empty();
        }

        size_t size() const
        {
            return storage.size();
        }

        T& back()
        {
            return storage[storage.size() - 1];
        }

        void push_back(const T& val)
        {
            storage.add(val);
        }

        void pop_back()
        {
            storage.remove();
        }

        void swap(dynamic_array_adapter<T>& that)
        {
            if (&that != this)
            {
                std::swap(std::move(*this), std::move(that));
            }
        }

    private:
        dynamic_array::dynamic_array<T> storage;
    };
}

#endif /* STACK_ADAPTER_HPP */