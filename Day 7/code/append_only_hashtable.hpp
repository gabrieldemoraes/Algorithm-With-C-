//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef APPEND_ONLY_HASHTABLE_HPP
#define APPEND_ONLY_HASHTABLE_HPP

#include <cstddef>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>
#include <tuple>

namespace append_only_hashtable
{
    namespace internal
    {
        static inline long double next_base_of(long double base, long double value)
        {
            return std::ceil(std::log(value) / std::log(base));
        }

        static inline long double next_base_of_two(long double value) 
        { 
            return next_base_of(2.L, value); 
        }

        static inline long double power_of_two(long double value)
        {
            return std::pow(2.L, value);
        }

        static inline std::size_t next_power_of_two(std::size_t value)
        {
            return static_cast<std::size_t>(power_of_two(next_base_of_two(static_cast<long double>(value))));
        }
    }

    //append_only_hashtable::set interface
    /*
    std::size_t add(const TKey& key);
    bool key_by_position(std::size_t pos, TKey& key) const;
    std::size_t position_by_key(const TKey& key) const;
    void clear()
    typename std::vector<TKey>::const_iterator begin() const;
    typename std::vector<TKey>::const_iterator end() const;
    std::size_t size() const;
    */

    template <typename TKey>
    class set
    {
        struct Entries
        {
            std::vector<TKey> keys;
            std::vector<std::size_t> next;
            
            void add(const TKey& key, std::size_t next)
            {
                this->keys.push_back(key);
                this->next.push_back(next);
            }
        };

        std::vector<std::size_t> buckets_;
        Entries entries_;
        std::hash<TKey> hasher_;

    public:
        static const std::size_t npos = -1;
        
        set() = delete;
        ~set() = default;

        explicit set(std::size_t suggested_bucket_size)
            : buckets_(internal::next_power_of_two(suggested_bucket_size), npos) {}

        set(const set<TKey>& that) :
            buckets_(that.buckets_)			
        {
            entries_.keys = that.entries_.keys;
            entries_.next = that.entries_.next;
        }

        set<TKey>& operator=(const set<TKey>& that)
        {
            if (&that != this)
            {
                buckets_ = that.buckets_;
                entries_.keys = that.entries_.keys;
                entries_.next = that.entries_.next;
            }
            return *this;
        }

        set(set<TKey>&& that) :
            buckets_(std::move(that.buckets_))
        {
            entries_.keys = std::move(that.entries_.keys);
            entries_.next = std::move(that.entries_.next);
        }

        set<TKey>& operator=(set<TKey>&& that)
        {
            if (&that != this)
            {
                buckets_ = std::move(that.buckets_);
                entries_.keys = std::move(that.entries_.keys);
                entries_.next = std::move(that.entries_.next);
            }
            return *this;
        }

        std::size_t add(const TKey& key)
        {
            std::size_t key_pos = find_key_position(key);
            if (key_pos == npos) //not found
            {
                key_pos = entries_.keys.size();
                const std::size_t bucket_pos = bucket_position(key);
                const std::size_t next = buckets_[bucket_pos];
                buckets_[bucket_pos] = key_pos;
                entries_.add(key, next);
            }			
            return key_pos;
        }

        bool key_by_position(std::size_t pos, TKey& key) const
        {
            if (entries_.keys.size() < pos)
                return false;
            key = entries_.keys[pos];
            return true;
        }

        std::size_t position_by_key(const TKey& key) const
        {
            return find_key_position(key);
        }

        void clear()
        {
            std::fill(buckets_.begin(), buckets_.end(), npos);
            entries_.keys.clear();
            entries_.next.clear();
        }

        typename std::vector<TKey>::const_iterator begin() const
        { 
            return entries_.keys.cbegin(); 
        }
        
        typename std::vector<TKey>::const_iterator end() const
        { 
            return entries_.keys.cend(); 
        }

        std::size_t size() const 
        {
            return entries_.keys.size();
        }

    private:
        std::size_t bucket_position(const TKey& key) const
        {
            //modulus operation using bitwise and
            //it's possible because size of buckets_ is guaranteed to be 2^n
            return hasher_(key) & (buckets_.size() - 1);
        }

        std::size_t find_key_position(const TKey& key) const
        {
            std::size_t next = buckets_[bucket_position(key)];
            while (next != npos)
            {
                if (key == entries_.keys[next])
                    return next;
                next = entries_.next[next];
            }
            return next;
        }
    };

    //append_only_hashtable::dictionary interface
    /*
    std::size_t add_or_update(const TKey& key, const TValue& value);
    bool key_by_position(std::size_t pos, TKey& key) const;
    bool value_by_position(std::size_t pos, TValue& value) const;	
    bool value_by_key(const TKey& key, TValue& value) const;	
    bool key_value_by_position(std::size_t pos, TKey& key, TValue& value) const;
    std::size_t position_by_key(const TKey& key) const;
    void clear();
    typename std::vector<TKey>::const_iterator begin() const;
    typename std::vector<TKey>::const_iterator end() const;
    std::size_t size() const;
    */

    template <typename TKey, typename TValue>
    class dictionary
    {
        struct Entries
        {
            std::vector<TKey> keys;
            std::vector<TValue> values;
            std::vector<std::size_t> next;

            void add(const TKey& key, const TValue& value, std::size_t next)
            {
                this->keys.push_back(key);
                this->values.push_back(value);
                this->next.push_back(next);
            }
        };

        std::vector<std::size_t> buckets_;
        Entries entries_;
        std::hash<TKey> hasher_;

    public:
        static const std::size_t npos = -1;

        dictionary() = delete;
        ~dictionary() = default;

        explicit dictionary(std::size_t suggested_bucket_size)
            : buckets_(internal::next_power_of_two(suggested_bucket_size), npos) {}

        dictionary(const dictionary<TKey, TValue>& that) :
            buckets_(that.buckets_)
        {
            entries_.keys = that.entries_.keys;
            entries_.values = that.entries_.values;
            entries_.next = that.entries_.next;
        }
        
        dictionary<TKey, TValue>& operator=(const dictionary<TKey, TValue>& that)
        {
            if (&that != this)
            {
                buckets_ = that.buckets_;
                entries_.keys = that.entries_.keys;
                entries_.values = that.entries_.values;
                entries_.next = that.entries_.next;
            }
            return *this;
        }

        dictionary(dictionary<TKey, TValue>&& that) :
            buckets_(std::move(that.buckets_))
        {
            entries_.keys = std::move(that.entries_.keys);
            entries_.values = std::move(that.entries_.values);
            entries_.next = std::move(that.entries_.next);
        }

        dictionary<TKey, TValue>& operator=(dictionary<TKey, TValue>&& that)
        {
            if (&that != this)
            {
                buckets_ = std::move(that.buckets_);
                entries_.keys = std::move(that.entries_.keys);
                entries_.values = std::move(that.entries_.values);
                entries_.next = std::move(that.entries_.next);
            }
            return *this;
        }

        std::size_t add_or_update(const TKey& key, const TValue& value)
        {
            std::size_t key_pos = find_key_position(key);
            if (key_pos == npos) //not found
            {
                key_pos = entries_.keys.size();
                const std::size_t bucket_pos = bucket_position(key);
                const std::size_t next = buckets_[bucket_pos];
                buckets_[bucket_pos] = key_pos;
                entries_.add(key, value, next);
            }
            else //found
            {
                entries_.values[key_pos] = value;
            }			
            return key_pos;
        }

        bool key_by_position(std::size_t pos, TKey& key) const
        {
            if (entries_.keys.size() < pos)
                return false;
            key = entries_.keys[pos];
            return true;
        }

        bool value_by_position(std::size_t pos, TValue& value) const
        {
            if (entries_.values.size() < pos)
                return false;
            value = entries_.values[pos];
            return true;
        }

        TValue& operator[](std::size_t pos)
        {
            return entries_.values[pos]; //unsafe: will crash if key doesn't exist
        }

        bool value_by_key(const TKey& key, TValue& value) const
        {
            std::size_t key_pos = find_key_position(key);
            if (key_pos == npos)
                return false;
            value = entries_.values[key_pos];
            return true;
        }

        TValue& operator[](const TKey& key)
        {
            return operator[](find_key_position(key));
        }

        bool key_value_by_position(std::size_t pos, TKey& key, TValue& value) const
        {
            if (entries_.keys.size() < pos)
                return false;
            key = entries_.keys[pos];
            value = entries_.values[pos];
            return true;
        }

        std::size_t position_by_key(const TKey& key) const
        {
            return find_key_position(key);
        }

        void clear()
        {
            std::fill(buckets_.begin(), buckets_.end(), npos);
            entries_.keys.clear();
            entries_.values.clear();
            entries_.next.clear();
        }

        typename std::vector<TKey>::const_iterator begin() const
        {
            return entries_.keys.cbegin();
        }

        typename std::vector<TKey>::const_iterator end() const
        {
            return entries_.keys.cend();
        }

        std::size_t size() const
        {
            return entries_.keys.size();
        }

    private:
        std::size_t bucket_position(const TKey& key) const
        {
            //modulus operation using bitwise and
            //it's possible because size of buckets_ is guaranteed to be 2^n
            return hasher_(key) & (buckets_.size() - 1);
        }

        std::size_t find_key_position(const TKey& key) const
        {
            std::size_t next = buckets_[bucket_position(key)];
            while (next != npos)
            {
                if (key == entries_.keys[next])
                    return next;
                next = entries_.next[next];
            }
            return next;
        }
    };
}

#endif /* APPEND_ONLY_HASHTABLE_HPP */