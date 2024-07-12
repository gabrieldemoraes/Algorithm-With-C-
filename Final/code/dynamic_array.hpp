//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <stdexcept>
#include <memory>

namespace dynamic_array
{
    template <typename T>
    constexpr const T& min(const T& a, const T& b)
    {
        return (b < a) ? b : a;
    }

    template <typename T>
    constexpr const T& clamp(const T& value, const T& min_value, const T& max_value)
    {
        if (value < min_value) return min_value;
        if (value > max_value) return max_value;
        return value;
    }

    const static std::size_t DYNAMIC_ARRAY_MIN_CAPACITY = 2;
    const static std::size_t DYNAMIC_ARRAY_MAX_CAPACITY = 100 * 1024 * 1024;

    //dynamic array interface
    /*
    void add(const T&);
    void remove();
    T& operator[](std::size_t) const;
    T& at(std::size_t) const;
    bool empty() const;
    std::size_t size() const;
    std::size_t capacity() const;
    void clear();
    T* data();
    T* begin();
    T* end();
    const T* cbegin() const;
    const T* cend() const;
    */

    template <typename T>
    class dynamic_array final
    {
    public:
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = T*;
        using const_pointer = const T*;
        using size_type = std::size_t;
        using iterator = T*;
        using const_iterator = const T*;

        //default constructor
        dynamic_array()
            : dynamic_array(DYNAMIC_ARRAY_MIN_CAPACITY)
        {
        }

        ~dynamic_array()
        {
            if (items)
                delete[] items;
        }

        explicit dynamic_array(std::size_t capacity)
            : current_size(0)
        {
            resize(capacity, false);
        }

        dynamic_array(std::size_t n, const T& val)
            : dynamic_array(n)
        {
            for (std::size_t i = 0; i < n; ++i)
                add(val);
        }

        //copy constructor
        dynamic_array(const dynamic_array<T>& that)
        {
            copy(that);
        }

        //move constructor
        dynamic_array(dynamic_array<T>&& that) noexcept
        {
            move(std::move(that));
        }

        //copy assignment
        dynamic_array<T>& operator=(const dynamic_array<T>& that)
        {
            if (&that != this)
            {
                copy(that);
            }
            return *this;
        }

        //move assignment
        dynamic_array<T>& operator=(dynamic_array<T>&& that) noexcept
        {
            if (&that != this)
            {
                move(std::move(that));
            }
            return *this;
        }

    public:
        void add(const T& item)
        {
            if (size() == capacity())
            {
                const std::size_t N = 2 * capacity();
                if (resize(N) < N) 
                    throw std::bad_alloc();
            }
            items[current_size++] = item;
        }

        void remove()
        {
            if (empty())
                throw std::runtime_error("is empty");

            if (!try_shrink())
                --current_size;
        }

        T& operator[](std::size_t index) const
        {
            return items[index]; //no boundary check
        }

        T& at(std::size_t index) const
        {
            if (0 <= index && index < current_size)
                return items[index];
            throw std::runtime_error("invalid index");
        }

        bool empty() const
        {
            return 0 == current_size;
        }

        std::size_t size() const
        {
            return current_size;
        }

        std::size_t capacity() const
        {
            return max_size;
        }

        void clear()
        {
            current_size = 0;
        }

        T* data()
        {
            return &items[0];
        }

        const T* data() const
        {
            return &items[0];
        }

        T* begin()
        {
            return data();
        }

        T* end()
        {
            return data() + size();
        }

        const T* cbegin() const
        {
            return data();
        }

        const T* cend() const
        {
            return data() + size();
        }

    private:
        std::size_t resize(std::size_t capacity, bool preserve = true)
        {
            capacity = clamp(capacity, DYNAMIC_ARRAY_MIN_CAPACITY, DYNAMIC_ARRAY_MAX_CAPACITY);
            T* new_items = new T[capacity];
            if (preserve)
            {
                for (std::size_t i = 0, l = min(current_size, capacity); i < l; ++i)
                    new_items[i] = items[i];
            }
            if (items)
                delete[] items;
            items = new_items;
            max_size = capacity;
            if (max_size < current_size)
                current_size = max_size;
            return capacity;
        }

        bool try_shrink(bool preserve = true)
        {
            bool can_shrink = (2 * DYNAMIC_ARRAY_MIN_CAPACITY) <= size() - 1 && size() - 1 == capacity() / 4;
            if (can_shrink)
                resize(capacity() / 4, preserve);
            return can_shrink;
        }

        void copy(const dynamic_array<T>& that)
        {
            if (that.capacity() > 0 && that.items) //is valid state?
            {
                resize(that.capacity(), false);
                for (std::size_t i = 0; i < that.size(); ++i)
                    items[i] = that.items[i];
                current_size = that.current_size;
            }
            else
            {
                throw std::runtime_error("invalid state");
            }
        }

        void move(dynamic_array<T>&& that) noexcept
        {
            max_size = that.max_size;
            current_size = that.current_size;
            if (items)
                delete[] items;
            items = that.items;
            that.max_size = 0;
            that.current_size = 0;
            that.items = nullptr;
        }

    private:
        std::size_t max_size, current_size;
        T* items = nullptr;
    };

    template <typename T>
    inline T* begin(dynamic_array<T>& xs) { return xs.begin(); }

    template <typename T>
    inline T* end(dynamic_array<T>& xs) { return xs.end(); }

    template <typename T>
    inline const T* cbegin(dynamic_array<T>& xs) { return xs.cbegin(); }

    template <typename T>
    inline const T* cend(dynamic_array<T>& xs) { return xs.cend(); }
}

#endif /* DYNAMIC_ARRAY_HPP */