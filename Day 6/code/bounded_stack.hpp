//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef BOUNDED_STACK_HPP
#define BOUNDED_STACK_HPP

#include <cstddef>
#include <algorithm>
#include "memory_allocation.hpp"

namespace bounded_stack
{
    template <typename T>
    struct bounded_stack_memory_allocation :
        public memory_allocation::conventional_memory_allocation<T>
    {
    };

    //bounded_stack interface
    /*
    bool push(const T&);
    bool pop(T&);
    bool top(T&);
    bool at(std::size_t, T&);
    std::size_t size();
    std::size_t capacity();
    bool empty();
    */

    template <typename T>
    class bounded_stack
    {
        std::size_t capacity_, top_;
        T* data_;

    public:
        explicit bounded_stack(std::size_t capacity = 0) :
            capacity_(capacity), top_(0)
        {
            data_ = bounded_stack_memory_allocation<T>::alloc(capacity_);
        }

        bounded_stack(bounded_stack<T>&& that) 
            : capacity_(that.capacity_), top_(that.top_), data_(that.data_)
        {
            that.capacity_ = 0;
            that.top_ = 0;
            that.data_ = nullptr;
        }

        bounded_stack<T>& operator=(bounded_stack<T>&& that)
        {
            if (this != &that)
            {
                capacity_ = that.capacity_;
                top_ = that.top_;
                this->~bounded_stack();
                data_ = that.data_;
                that.capacity_ = 0;
                that.top_ = 0;
                that.data_ = nullptr;
            }
            return *this;
        }

        ~bounded_stack()
        {
            if (data_) bounded_stack_memory_allocation<T>::dealloc(data_);
        }

        bounded_stack(const bounded_stack<T>&) = delete;
        bounded_stack<T>& operator=(const bounded_stack<T>&) = delete;		

    public:
        bool push(const T& elem)
        {
            if (top_ < capacity_)
            {
                data_[top_++] = elem;
                return true;
            }
            return false;
        }

        bool pop(T& elem)
        {
            if (top_ > 0)
            {
                elem = data_[--top_];
                return true;
            }
            return false;
        }

        bool top(T& elem) const
        {
            if (top_ > 0)
            {
                elem = data_[top_ - 1];
                return true;
            }
            return false;
        }

        bool at(std::size_t pos, T& elem) const
        {
            if (pos < size())
            {
                elem = data_[pos];
                return true;
            }
            return false;
        }

        std::size_t size() const
        {
            return top_;
        }

        std::size_t capacity() const
        {
            return capacity_;
        }

        bool empty() const
        {
            return top_ == 0;
        }

        template <typename U>
        friend bounded_stack<U> resize(const bounded_stack<U>& s, std::size_t new_capacity);
    };

    template <typename T>
    static inline bounded_stack<T> resize(const bounded_stack<T>& s, std::size_t new_capacity)
    {
        #undef min
        bounded_stack<T> temp(new_capacity);		
        std::copy(s.data_, s.data_ + std::min(temp.capacity_, s.capacity_), temp.data_);
        temp.top_ = std::min(temp.capacity_, s.top_);
        return std::move(temp);
    }
}

#endif /* BOUNDED_STACK_HPP */