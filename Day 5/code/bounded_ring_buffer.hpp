//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef BOUNDED_RING_BUFFER_HPP
#define BOUNDED_RING_BUFFER_HPP

#include <cstddef>
#include "memory_allocation.hpp"

namespace bounded_ring_buffer
{
    template <typename T>
    struct bounded_ring_buffer_memory_allocation :
        public memory_allocation::conventional_memory_allocation<T>
    {
    };

    //bounded_ring_buffer interface
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
    class bounded_ring_buffer
    {
        std::size_t capacity_, write_, read_;
        bool lap_ahead_;
        T* data_;

    public:
        explicit bounded_ring_buffer(std::size_t capacity = 0)
            : capacity_(capacity), write_(0), read_(0), lap_ahead_(false)
        {
            data_ = bounded_ring_buffer_memory_allocation<T>::alloc(capacity_);
        }

        bounded_ring_buffer(bounded_ring_buffer<T>&& that)
            : capacity_(that.capacity_), write_(that.write_), read_(that.read_),
              lap_ahead_(that.lap_ahead_), data_(that.data_)
        {
            that.capacity_ = 0;
            that.write_ = 0;
            that.read_ = 0;
            that.lap_ahead_ = false;
            that.data_ = nullptr;
        }

        ~bounded_ring_buffer()
        {
            if (data_) bounded_ring_buffer_memory_allocation<T>::dealloc(data_);
        }

        bounded_ring_buffer(const bounded_ring_buffer<T>&) = delete;
        bounded_ring_buffer<T>& operator=(const bounded_ring_buffer<T>&) = delete;
        bounded_ring_buffer<T>& operator=(bounded_ring_buffer<T>&&) = delete;
    
    private:
        void next_read()
        {
            if (++read_ >= capacity_)
            {
                read_ = 0;
                lap_ahead_ = false;
            }
        }

        void next_write()
        {
            if (++write_ >= capacity_)
            {
                write_ = 0;
                lap_ahead_ = true;
            }
        }

    public:
        bool push(const T& elem)
        {
            if (lap_ahead_ && read_ == write_) 
                next_read();
            data_[write_] = elem;			
            next_write();
            return true;
        }

        bool pop(T& elem)
        {
            if (empty())
                return false;
            elem = data_[read_];
            next_read();
            return true;
        }

        bool top(T& elem) const
        {
            if (empty())
                return false;
            elem = data_[read_];
            return true;
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
            std::size_t s = write_ - read_;
            if (lap_ahead_) s += capacity_;
            return s;
        }

        std::size_t capacity() const
        {
            return capacity_;
        }

        bool empty() const
        {
            return !lap_ahead_ && read_ == write_;
        }
    };
}

#endif /* BOUNDED_RING_BUFFER_HPP */

