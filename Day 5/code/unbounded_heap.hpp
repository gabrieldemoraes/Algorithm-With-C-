//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef UNBOUNDED_HEAP_HPP
#define UNBOUNDED_HEAP_HPP

#include <cstddef>
#include <algorithm>
#include <vector>
#include <type_traits>
#include <functional>

namespace unbounded_heap
{
    //unbounded_heap interface
    /*
    bool push(const T&);
    bool pop(T&);
    bool top(T&);
    bool at(std::size_t, T&);
    std::size_t size();
    bool empty();
    */
    
    template <typename T, typename Compare>
    class unbounded_heap
    {
        std::vector<T> data_;
        Compare compare_;

    public:
        unbounded_heap() = default;
        
        template <typename... Ts>
        unbounded_heap(Ts&&... xs)
        {
            data_.reserve(sizeof...(xs));
            construct_heap_recursive(std::forward<Ts>(xs)...);
        }
        
        unbounded_heap(unbounded_heap<T, Compare>&& that)
            : data_(std::move(that.data_)) {}

        unbounded_heap(std::vector<T>&& xs)
            : data_(std::move(xs))
        {
            heapify();
        }

        ~unbounded_heap() = default;

        unbounded_heap(const unbounded_heap<T, Compare>&) = delete;
        unbounded_heap<T, Compare>& operator=(const unbounded_heap<T, Compare>&) = delete;
        unbounded_heap<T, Compare>& operator=(unbounded_heap<T, Compare>&&) = delete;

    private:
        template <typename T_, typename... Ts>
        void construct_heap_recursive(T_&& x, Ts &&... xs)
        {
            static_assert(std::is_same<T, T_>::value, "requires same type");
            data_.emplace_back(std::forward<T_>(x));
            construct_heap_recursive(std::forward<Ts>(xs)...);
        }
        
        void construct_heap_recursive()
        {
            heapify();
        }

        void heapify()
        {
            std::make_heap(data_.begin(), data_.end(), compare_);
        }

    public:
        bool push(const T& elem)
        {
            data_.push_back(elem);
            std::push_heap(data_.begin(), data_.end(), compare_);
            return true;
        }

        bool pop(T& elem)
        {
            if (!empty())
            {
                elem = data_.front();
                std::pop_heap(data_.begin(), data_.end(), compare_);
                data_.pop_back();
                return true;
            }
            return false;
        }

        bool top(T& elem) const
        {
            if (!empty())
            {
                elem = data_.front();
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
            return data_.size();
        }
        
        bool empty() const
        {
            return data_.empty();
        }
    };

    template <typename T>
    using unbounded_max_heap = unbounded_heap<T, std::less<T>>;
    
    template <typename T>
    using unbounded_min_heap = unbounded_heap<T, std::greater<T>>;
}

#endif /* UNBOUNDED_HEAP_HPP */