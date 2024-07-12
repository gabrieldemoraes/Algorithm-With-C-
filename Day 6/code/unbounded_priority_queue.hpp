//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef UNBOUNDED_PRIORITY_QUEUE_HPP
#define UNBOUNDED_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <queue>
#include <vector>
#include <functional>

namespace unbounded_priority_queue
{
    #undef min
    #undef max

    namespace internal
    {
        template <typename T>
        using MinPQBase = std::priority_queue<T, std::vector<T>, std::greater<T>>;

        template <typename T>
        using MaxPQBase = std::priority_queue<T, std::vector<T>, std::less<T>>;
    }

    //min_pq interface
    /*
    bool insert(const T&);
    T& min();
    bool min(T&);
    bool remove_min();
    bool remove_min(T&);
    std::size_t size();
    bool empty();
    */

    template <typename T>
    class min_pq final : private internal::MinPQBase<T>
    {
        using Base = internal::MinPQBase<T>;

    public:
        min_pq() = default;
        ~min_pq() = default;

        min_pq(const min_pq<T>&) = default;
        min_pq<T>& operator=(const min_pq<T>&) = default;

        min_pq(min_pq<T>&& that)
        {
            Base::swap(that);
        }

        min_pq<T>& operator=(min_pq<T>&& that)
        {
            if (&that != this)
            {
                //Base::operator=(Base()); //clear pq using base operator=
                //or
                *reinterpret_cast<Base*>(this) = Base(); //clear pq casting to base
                Base::swap(that);
            }
            return *this;
        }	

    public:
        bool insert(const T& elem)
        {
            Base::push(elem);
            return true;
        }

        const T& min() const
        {
            return Base::top();
        }

        bool min(T& elem) const
        {
            if (!empty())
            {
                elem = Base::top();
                return true;
            }
            return false;
        }

        bool remove_min()
        {
            if (!empty())
            {
                Base::pop();
                return true;
            }
            return false;
        }

        bool remove_min(T& elem)
        {
            if (!empty())
            {
                elem = Base::top();
                Base::pop();
                return true;
            }
            return false;
        }

        std::size_t size() const
        {
            return Base::size();
        }

        bool empty() const
        {
            return Base::empty();
        }
    };

    //max_pq interface
    /*
    bool insert(const T&);
    T& max();
    bool max(T&);
    bool remove_max();
    bool remove_max(T&);
    std::size_t size();
    bool empty();
    */

    template <typename T>
    class max_pq final : private internal::MaxPQBase<T>
    {
        using Base = internal::MaxPQBase<T>;

    public:
        max_pq() = default;
        ~max_pq() = default;

        max_pq(const max_pq<T>&) = default;
        max_pq<T>& operator=(const max_pq<T>&) = default;

        max_pq(max_pq<T>&& that)
        {
            Base::swap(that);
        }

        max_pq<T>& operator=(max_pq<T>&& that)
        {
            if (&that != this)
            {
                //Base::operator=(Base()); //clear pq using base operator=
                //or
                *reinterpret_cast<Base*>(this) = Base(); //clear pq casting to base
                Base::swap(that);
            }
            return *this;
        }

    public:
        bool insert(const T& elem)
        {
            Base::push(elem);
            return true;
        }

        const T& max() const
        {
            return Base::top();
        }
        
        bool max(T& elem) const
        {
            if (!empty())
            {
                elem = Base::top();
                return true;
            }
            return false;
        }

        bool remove_max()
        {
            if (!empty())
            {
                Base::pop();
                return true;
            }
            return false;
        }

        bool remove_max(T& elem)
        {
            if (!empty())
            {
                elem = Base::top();
                Base::pop();
                return true;
            }
            return false;
        }

        std::size_t size() const
        {
            return Base::size();
        }

        bool empty() const
        {
            return Base::empty();
        }
    };
}

#endif /* UNBOUNDED_PRIORITY_QUEUE_HPP */