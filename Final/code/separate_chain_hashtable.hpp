//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef SEPARATE_CHAIN_HASHTABLE_HPP
#define SEPARATE_CHAIN_HASHTABLE_HPP

#include <cstddef>
#include <vector>
#include <forward_list>
#include <functional>
#include <algorithm>

namespace separate_chain_hashtable
{
    namespace internal
    {
        template <typename T, typename Predicate>
        static inline bool erase_first(std::forward_list<T>& xs, Predicate predicate)
        {
            using list_type = std::forward_list<T>;
            typename list_type::iterator prev;
            typename list_type::iterator iter = xs.before_begin();
            typename list_type::iterator end = xs.end();
            bool found = false;
            while (true)
            {
                prev = iter++;
                if (iter == end)
                {
                    break;
                }
                else if (predicate(iter))
                {
                    xs.erase_after(prev);
                    found = true;
                    break;
                }
            }
            return found;
        }
    }

    //separate_chain_hashtable::dictionary (unbounded) interface
    /*
    void add_or_update(const TKey&, const TValue&);
    bool get(const TKey&, TValue&);
    bool remove(const TKey&);
    std::vector<TKey> keys() const;
    bool empty() const;
    */

    template <typename TKey, typename TValue>
    class dictionary
    {
        struct KV
        {
            TKey key;
            TValue value;
        };
        
        using chain_value_type = KV;
        using bucket_value_type = std::forward_list<chain_value_type>;
        using bucket_reference = bucket_value_type&;
    
    public:
        explicit dictionary(std::size_t bucket_size = 0) 
            : buckets_(bucket_size ? bucket_size : 1024, bucket_value_type{})
        {
        }

        ~dictionary() = default;

        dictionary(const dictionary<TKey, TValue>& that) 
            : buckets_(that.buckets_)
        {
        }

        dictionary(dictionary<TKey, TValue>&& that)
            : buckets_(std::move(that.buckets_))
        {
        }
        
        dictionary<TKey, TValue>& operator=(const dictionary<TKey, TValue>& that)
        {
            if (this != &that)
                buckets_ = that.buckets_;
            return *this;
        }

        dictionary<TKey, TValue>& operator=(dictionary<TKey, TValue>&& that)		
        {
            if (this != &that)
                buckets_ = std::move(that.buckets_);
            return *this;
        }

        void add_or_update(const TKey& key, const TValue& value)
        {
            bucket_reference b = get_bucket(key);
            typename bucket_value_type::iterator iter = find_key(b, key);
            if (iter != b.end()) //found			
                iter->value = value;			
            else //not found			
                b.push_front(chain_value_type{ key, value });			
        }

        bool get(const TKey& key, TValue& value)
        {
            bucket_reference b = get_bucket(key);
            typename bucket_value_type::iterator iter = find_key(b, key);
            if (iter == b.end()) 
                return false; //not found
            value = iter->value;
            return true; //found
        }

        bool remove(const TKey& key)
        {
            return remove_key(get_bucket(key), key);
        }

        std::vector<TKey> keys() const
        {
            std::vector<TKey> result;
            for (auto& b : buckets_)
                for (auto& kv : b)
                    result.push_back(kv.key);
            return std::move(result);
        }

        bool empty() const
        {
            for (auto& b : buckets_)
                if (!b.empty())
                    return false;
            return true;
        }

    private:
        bucket_reference get_bucket(const TKey& key)
        {
            std::size_t h = hasher_(key) % buckets_.size();
            return buckets_[h];
        }

        typename bucket_value_type::iterator find_key(bucket_reference b, const TKey& key)
        {
            return std::find_if(b.begin(), b.end(), [&](const chain_value_type& kv) {
                return kv.key == key;
            });
        }

        bool remove_key(bucket_reference b, const TKey& key)
        {
            return internal::erase_first(b, [&](typename bucket_value_type::const_iterator citer) { 
                return citer->key == key; 
            });
        }

    private:
        std::vector<bucket_value_type> buckets_;
        std::hash<TKey> hasher_;
    };

    //separate_chain_hashtable::set (unbounded) interface
    /*
    void add(const TKey&);
    bool exists(const TKey& key);
    bool remove(const TKey&);
    std::vector<TKey> keys() const;
    */

    template <typename TKey>
    class set
    {
        using chain_value_type = TKey;
        using bucket_value_type = std::forward_list<chain_value_type>;
        using bucket_reference = bucket_value_type&;

    public:
        explicit set(std::size_t bucket_size = 0)
            : buckets_(bucket_size ? bucket_size : 1024, bucket_value_type{})
        {
        }

        ~set() = default;

        set(const set<TKey>& that)
            : buckets_(that.buckets_)
        {
        }

        set(set<TKey>&& that)
            : buckets_(std::move(that.buckets_))
        {
        }

        set<TKey>& operator=(const set<TKey>& that)
        {
            if (this != &that)
                buckets_ = that.buckets_;
            return *this;
        }

        set<TKey>& operator=(set<TKey>&& that)
        {
            if (this != &that)
                buckets_ = std::move(that.buckets_);
            return *this;
        }

        void add(const TKey& key)
        {
            bucket_reference b = get_bucket(key);
            if (find_key(b, key) == b.end())
                b.push_front(chain_value_type{ key });
        }

        bool exists(const TKey& key)
        {
            bucket_reference b = get_bucket(key);
            return find_key(b, key) != b.end();
        }

        bool remove(const TKey& key)
        {
            return remove_key(get_bucket(key), key);
        }

        std::vector<TKey> keys() const
        {
            std::vector<TKey> result;
            for (auto& b : buckets_)
                for (auto& k : b)
                    result.push_back(k);
            return std::move(result);
        }

    private:
        bucket_reference get_bucket(const TKey& key)
        {
            std::size_t h = hasher_(key) % buckets_.size();
            return buckets_[h];
        }

        typename bucket_value_type::iterator find_key(bucket_reference b, const TKey& key)
        {
            return std::find_if(b.begin(), b.end(), [&](const chain_value_type& k) {
                return k == key;
            });
        }

        bool remove_key(bucket_reference b, const TKey& key)
        {
            return internal::erase_first(b, [&](typename bucket_value_type::const_iterator citer) {
                return *citer == key;
            });
        }

    private:
        std::vector<bucket_value_type> buckets_;
        std::hash<TKey> hasher_;
    };
}

#endif /* SEPARATE_CHAIN_HASHTABLE_HPP */