//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef BOUNDED_QUEUE_HPP
#define BOUNDED_QUEUE_HPP

#include <cstddef>
#include "memory_allocation.hpp"

namespace bounded_queue
{
    template <typename T>
    struct bounded_queue_memory_allocation :
        public memory_allocation::conventional_memory_allocation<T>
    {
    };

    //bounded_queue interface
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
    class bounded_queue
    {
        std::size_t capacity_, write_, read_, count_;
        T* data_;

    public:
        explicit bounded_queue(std::size_t capacity = 0)
            : capacity_(capacity), write_(0), read_(0), count_(0)
        {
            data_ = bounded_queue_memory_allocation<T>::alloc(capacity_);
        }

        bounded_queue(bounded_queue<T>&& that)
            : capacity_(that.capacity_), write_(that.write_), read_(that.read_),
              count_(that.count_), data_(that.data_)
        {
            that.capacity_ = 0;
            that.write_ = 0;
            that.read_ = 0;
            that.count_ = 0;
            that.data_ = nullptr;
        }

        ~bounded_queue()
        {
            if (data_) bounded_queue_memory_allocation<T>::dealloc(data_);
        }

        bounded_queue(const bounded_queue<T>&) = delete;
        bounded_queue<T>& operator=(const bounded_queue<T>&) = delete;
        bounded_queue<T>& operator=(bounded_queue<T>&&) = delete;

    private:
        void next_read()
        {
            if (++read_ >= capacity_)
            {
                read_ = 0;
            }
        }

        void next_write()
        {
            if (++write_ >= capacity_)
            {
                write_ = 0;
            }
        }

    public:
        bool push(const T& elem)
        {
            if (count_ < capacity_)
            {
                data_[write_] = elem;
                next_write();
                ++count_;
                return true;
            }
            return false;
        }

        bool pop(T& elem)
        {
            if (count_ > 0)
            {
                elem = data_[read_];
                next_read();
                --count_;
                return true;
            }
            return false;
        }

        bool top(T& elem) const
        {
            if (count_ > 0)
            {
                elem = data_[read_];
                return true;
            }
            return false;
        }

        bool at(std::size_t pos, T& elem) const
        {
            if (pos < size())
            {
                elem = data_[(pos + read_) % capacity_];
                return true;
            }
            return false;
        }

        std::size_t size() const
        {
            return count_;
        }

        std::size_t capacity() const
        {
            return capacity_;
        }

        bool empty() const
        {
            return count_ == 0;
        }
    };
}

#endif /* BOUNDED_QUEUE_HPP */