//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include <cstddef>
#include <vector>
#include <ostream>
#include <sstream>

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
