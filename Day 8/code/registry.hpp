//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <cstddef>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <utility>
#include <algorithm>
#include <memory>

namespace registry
{
    //registry interface
    /*
    std::size_t deposit(T item);
    bool check(std::size_t id);
    std::pair<bool, T> withdraw(std::size_t id);
    std::size_t size() const;
    */
    
    template<typename T>
    struct registry_base
    {
        virtual std::size_t deposit(T item) = 0;
        virtual bool check(std::size_t id) const = 0;
        virtual std::pair<bool, T> withdraw(std::size_t id) = 0;
        virtual std::size_t size() const = 0;
    };

    template<typename T>
    class hash_table_registry final : public registry_base<T>
    {
        std::unordered_map<std::size_t, T> map_;
        std::size_t size_ = 0, next_id_ = 0;

    public:
        std::size_t deposit(T item) override
        {
            map_.emplace(next_id_, std::move(item));
            ++size_;
            return next_id_++;
        }

        bool check(std::size_t id) const override
        {
            auto it = map_.find(id);
            return it != map_.end();
        }

        std::pair<bool, T> withdraw(std::size_t id) override
        {
            auto it = map_.find(id);
            if (it == map_.end())
                return std::make_pair<bool, T>(false, std::move(T{}));

            T temp = std::move(it->second);
            map_.erase(it);
            --size_;
            return std::make_pair<bool, T>(true, std::move(temp));
        }

        std::size_t size() const override { return map_.size(); };
    };

    template<typename T>
    class russian_coat_check_algorithm_registry final : public registry_base<T>
    {
        struct bool_type
        {
            mutable bool value = false;
            void flip() const { value = !value; }
            operator bool() const { return value; }
        };
        using kvp_type = std::pair<std::size_t, std::pair<T, bool_type>>;
        std::vector<kvp_type> map_;
        std::size_t size_ = 0, next_id_ = 0;
    
        typename std::vector<kvp_type>::const_iterator find(std::size_t id) const
        {
            return std::lower_bound(map_.begin(), map_.end(), id,
                [](const kvp_type& lhs, std::size_t id) {
                    return lhs.first < id;
                });
        }

        void try_compact()
        {
            if (size_ < (map_.size() / 2))
            {
                map_.erase(
                    std::remove_if(
                        map_.begin(), map_.end(),
                        [](const kvp_type& x) { return !x.second.second; }
                    ),
                    map_.end()
                );
            }
        }

    public:
        std::size_t deposit(T item) override
        {
            map_.emplace_back(next_id_,
                std::move(std::make_pair<>(std::move(item), bool_type{ true }))
            );
            ++size_;
            return next_id_++;
        }
        
        bool check(std::size_t id) const override
        {
            auto it = find(id);
            return !(it == map_.end() || it->first != id || !it->second.second);
        }

        std::pair<bool, T> withdraw(std::size_t id) override
        {
            auto it = find(id);
            if (it == map_.end() || it->first != id || !it->second.second)
                return std::make_pair<bool, T>(false, std::move(T{}));

            T temp = std::move(it->second.first);
            it->second.second.flip();
            --size_;
            try_compact();
            return std::make_pair<bool, T>(true, std::move(temp));
        }

        std::size_t size() const override { return size_; };
    };
}

#endif /* REGISTRY_HPP */