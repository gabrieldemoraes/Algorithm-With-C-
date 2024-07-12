//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include <cstddef>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ostream>
#include <algorithm>
#include <cassert>

#include "unbounded_priority_queue.hpp"

namespace bin_packing_best_fit
{
    class Bin final
    {
        std::size_t capacity_;
        std::vector<std::size_t> items_;

    public:
        Bin(std::size_t capacity) : capacity_(capacity) {}

        Bin(const Bin& that) : capacity_(that.capacity_), items_(that.items_) 
        {
        }
        
        Bin& operator=(const Bin& that)
        {
            if (this != &that)
            {
                capacity_ = that.capacity_;
                items_ = that.items_;
            }
            return *this;
        }

        Bin(Bin&& that) : capacity_(that.capacity_), items_(std::move(that.items_))
        {
            that.capacity_ = 0;
        }

        Bin& operator=(Bin&& that)
        {
            if (this != &that)
            {
                capacity_ = that.capacity_;
                that.capacity_ = 0;
                items_ = std::move(that.items_);
            }
            return *this;
        }

        ~Bin() = default;

        bool operator<(const Bin& that) const
        {
            return size() < that.size();
        }

        std::size_t size() const
        {
            return capacity_;
        }

        bool full() const
        {
            return size() == 0;
        }

        bool try_decrease(std::size_t amount)
        {
            if (0 < amount && amount <= size())
            {
                capacity_ -= amount;
                items_.push_back(amount);
                return true;
            }
            return false;
        }

        std::string to_string() const
        {
            std::stringstream ss;
            ss << "(remaining: " << capacity_ << " items:";
            if (!items_.empty())
                for (std::size_t i : items_) ss << " " << i;
            else
                ss << " empty";
            ss << ")";
            return ss.str();
        }

        friend std::ostream& operator<<(std::ostream& os, const Bin& b);
    };

    std::ostream& operator<<(std::ostream& os, const Bin& b)
    {
        os << b.to_string();
        return os;
    }

    static void bin_packing_best_fit(std::vector<std::size_t> weights, std::size_t bin_capacity)
    {
        //assert(std::all_of(weights.begin(), weights.end(), [bin_capacity](std::size_t w) { return w <= bin_capacity; }));

        unbounded_priority_queue::max_pq<Bin> pq;
        if (!weights.empty())
        {
            pq.insert(Bin(bin_capacity));
            for (auto w : weights)
            {
                if (w <= bin_capacity)
                {
                    if (pq.max().size() < w)
                        pq.insert(Bin(bin_capacity));
                    Bin b = pq.max();
                    pq.remove_max();
                    b.try_decrease(w);
                    pq.insert(b);
                }
                //else
                    //ignore
            }
        }

        std::cout << pq.size() << " Bin(s) of " << bin_capacity << ":\n";
        for (std::size_t i = 1; !pq.empty(); ++i)
        {
            std::cout << std::setw(4) << i << ": " << pq.max() << "\n";
            pq.remove_max();
        }
    }
        
    static int run_solution()
    {
        //PROBLEM: Given the bin capacity and a sequence of item's of weights. 
        //Find the minimal number of bins necessary to assign each item in sequence.
        
        //INPUT: B, N, weights
        //Our input represents B (bin capacity), N (number of items) and weights (sequence of item's weight)
        
        std::size_t B, N;
        std::cin >> B >> N;
        std::vector<std::size_t> weights(N, 0);
        for (std::size_t i = 0; i < N; ++i)		
            std::cin >> weights[i];
        
        //REQUIREMENTS:
        if (!std::all_of(weights.begin(), weights.end(), [B](std::size_t w) { return w <= B; }))
        {
            std::cout << "Invalid due an item greater than bin capacity\n";
            return -1;
        }

        //SOLUTION:
        bin_packing_best_fit(std::move(weights), B);
        return 0;
    }
}

//Test cases:
//3 Bin(s) of 80: 80 5 10 20 30 40 50
//2 Bin(s) of 10: 10 4 8 4 2 3
//4 Bin(s) of 10: 10 7 2 5 4 7 1 3 8
//4 Bin(s) of  8: 8 7 2 5 4 7 1 3 8
//3 Bin(s) of 14: 14 7 2 5 4 7 1 3 8
//3 Bin(s) of 10: 10 5 8 3 4 9 1
//1 Bin(s) of 25: 25 5 8 3 4 9 1
int bin_packing_best_fit_main(int argc, char *argv[], bool run)
{
    using bin_packing_best_fit::run_solution;
    
    if (run)
    {
        return run_solution();
    }

    return 0;
}