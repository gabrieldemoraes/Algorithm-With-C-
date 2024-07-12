//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef LINEAR_PROBING_HASHTABLE_HPP
#define LINEAR_PROBING_HASHTABLE_HPP

#include <cstddef>
#include <vector>
#include <functional>
#include <memory>

namespace linear_probing_hashtable
{
    //linear_probing_hashtable::dictionary (bounded, but resizable) interface
    /*
    void add_or_update(const TKey&, const TValue&);
    bool get(const TKey&, TValue&);
    bool remove(const TKey&);
    std::vector<TKey> keys() const;
    bool empty() const;
    std::size_t size() const;
    std::size_t capacity() const;
    */

    template <typename TKey, typename TValue>
    class dictionary
    {
        struct KV
        {
            TKey key;
            TValue value;
        };

        static const std::size_t npos = -1;

    public:
        explicit dictionary(std::size_t bucket_size = 0)
            : buckets_(bucket_size ? bucket_size : 1024), size_(0)
        {
        }

        ~dictionary() = default;

        dictionary(const dictionary<TKey, TValue>& that) :
            dictionary(std::move(clone(that)))
        {
        }

        dictionary(dictionary<TKey, TValue>&& that) :
            buckets_(std::move(that.buckets_)), size_(that.size_)
        {
            that.size_ = 0;
        }

        dictionary<TKey, TValue>& operator=(const dictionary<TKey, TValue>& that)
        {
            if (this != &that)
            {
                dictionary<TKey, TValue> temp = std::move(clone(that));
                buckets_ = std::move(temp.buckets_);
                size_ = temp.size_;
            }
            return *this;
        }

        dictionary<TKey, TValue>& operator=(dictionary<TKey, TValue>&& that)
        {
            if (this != &that)
            {
                buckets_ = std::move(that.buckets_);
                size_ = that.size_;
                that.size_ = 0;
            }
            return *this;
        }

        void add_or_update(const TKey& key, const TValue& value)
        {
            if (needs_to_grow())
                resize(2 * capacity());

            std::size_t bucket_pos = bucket_position(key);
            for (KV* ptr; (ptr = buckets_[bucket_pos].get()); bucket_pos = next_bucket_position(bucket_pos))
            {
                if (ptr->key == key)
                {
                    ptr->value = value; //update
                    return;
                }
            }
            buckets_[bucket_pos].reset(new KV{ key, value }); //add
            ++size_;
        }

        bool get(const TKey& key, TValue& value) const
        {
            std::size_t bucket_pos;
            const KV* ptr = find_key(key, bucket_pos);
            if (ptr)
            {
                value = ptr->value;
                return true;
            }
            return false;
        }

        bool remove(const TKey& key)
        {
            std::size_t bucket_pos;
            if (!find_key(key, bucket_pos))
                return false;

            buckets_[bucket_pos].reset();
            --size_;
            
            //rehash all keys in the path
            bucket_pos = next_bucket_position(bucket_pos);
            for (KV* ptr; (ptr = buckets_[bucket_pos].get()); bucket_pos = next_bucket_position(bucket_pos))
            {
                TKey key = ptr->key; TValue value = ptr->value;
                buckets_[bucket_pos].reset();
                --size_;
                add_or_update(key, value);
            }

            if (needs_to_shrink())
                resize(capacity() / 2);

            return true;
        }

        std::vector<TKey> keys() const
        {
            std::vector<TKey> result;
            for (auto& kv : buckets_)
                if (kv) result.push_back(kv->key);
            return std::move(result);
        }

        bool empty() const
        {
            return size() == 0;
        }

        std::size_t size() const
        {
            return size_;
        }

        std::size_t capacity() const
        {
            return buckets_.size();
        }

    private:
        std::size_t bucket_position(const TKey& key) const
        {
            return hasher_(key) % buckets_.size();
        }

        std::size_t next_bucket_position(std::size_t pos) const
        {
            return (pos + 1) % buckets_.size();
        }

        const KV* find_key(const TKey& key, std::size_t& position) const
        {
            std::size_t bucket_pos = bucket_position(key);
            for (KV* ptr; (ptr = buckets_[bucket_pos].get()); bucket_pos = next_bucket_position(bucket_pos))
            {
                if (ptr->key == key)
                {
                    position = bucket_pos;
                    return ptr;
                }
            }
            position = npos;
            return nullptr;
        }

        void resize(std::size_t new_capacity)
        {
            const std::size_t MIN_CAPACITY = 8;
            if (new_capacity <= MIN_CAPACITY)
                return;
            
            dictionary<TKey, TValue> temp(new_capacity);
            for (auto& kv : buckets_)
                if (kv) temp.add_or_update(kv->key, kv->value); //rehashing
            buckets_ = std::move(temp.buckets_);
            //size_ = temp.size_; //still same size_, don't need to update
        }

        bool needs_to_grow() const
        {
            return size() >= (3 * capacity()) / 4; //75% of buckets occupied 
        }

        bool needs_to_shrink() const
        {
            return 0 < size() && size() <= (1 * capacity()) / 4; //25% of buckets occupied
        }

        static dictionary<TKey, TValue> clone(const dictionary<TKey, TValue>& that)
        {
            dictionary<TKey, TValue> temp(that.capacity());
            temp.size_ = that.size_;
            for (std::size_t i = 0; i < that.capacity(); ++i)
            {
                KV* ptr = that.buckets_[i].get();
                if (ptr) temp.buckets_[i].reset(new KV{ ptr->key, ptr->value });
            }
            return std::move(temp);
        }

    private:
        std::vector<std::unique_ptr<KV>> buckets_;
        std::size_t size_;
        std::hash<TKey> hasher_;
    };

    //linear_probing_hashtable::dictionary (bounded, but resizable) interface
    /*
    void add(const TKey&);
    bool exists(const TKey&) const;
    bool remove(const TKey&);
    std::vector<TKey> keys() const;
    bool empty() const;
    std::size_t size() const;
    std::size_t capacity() const;
    */

    template <typename TKey>
    class set
    {
        static const std::size_t npos = -1;

    public:
        explicit set(std::size_t bucket_size = 0)
            : buckets_(bucket_size ? bucket_size : 1024), size_(0)
        {
        }

        ~set() = default;

        set(const set<TKey>& that) :
            set(std::move(clone(that)))
        {
        }

        set(set<TKey>&& that) :
            buckets_(std::move(that.buckets_)), size_(that.size_)
        {
            that.size_ = 0;
        }

        set<TKey>& operator=(const set<TKey>& that)
        {
            if (this != &that)
            {
                set<TKey> temp = std::move(clone(that));
                buckets_ = std::move(temp.buckets_);
                size_ = temp.size_;
            }
            return *this;
        }

        set<TKey>& operator=(set<TKey>&& that)
        {
            if (this != &that)
            {
                buckets_ = std::move(that.buckets_);
                size_ = that.size_;
                that.size_ = 0;
            }
            return *this;
        }

        void add(const TKey& key)
        {
            if (needs_to_grow())
                resize(2 * capacity());

            std::size_t bucket_pos = bucket_position(key);
            for (TKey* ptr; (ptr = buckets_[bucket_pos].get()); bucket_pos = next_bucket_position(bucket_pos))
            {
                if (*ptr == key)
                    return;
            }
            buckets_[bucket_pos].reset(new TKey{ key });
            ++size_;
        }

        bool exists(const TKey& key) const
        {
            std::size_t bucket_pos;
            return find_key(key, bucket_pos) != nullptr;
        }

        bool remove(const TKey& key)
        {
            std::size_t bucket_pos;
            if (!find_key(key, bucket_pos))
                return false;

            buckets_[bucket_pos].reset();
            --size_;

            //rehash all keys in the path
            bucket_pos = next_bucket_position(bucket_pos);
            for (TKey* ptr; (ptr = buckets_[bucket_pos].get()); bucket_pos = next_bucket_position(bucket_pos))
            {
                TKey key = *ptr;
                buckets_[bucket_pos].reset();
                --size_;
                add(key);
            }

            if (needs_to_shrink())
                resize(capacity() / 2);

            return true;
        }

        std::vector<TKey> keys() const
        {
            std::vector<TKey> result;
            for (auto& k : buckets_)
                if (k) result.push_back(*k);
            return std::move(result);
        }

        bool empty() const
        {
            return size() == 0;
        }

        std::size_t size() const
        {
            return size_;
        }

        std::size_t capacity() const
        {
            return buckets_.size();
        }

    private:
        std::size_t bucket_position(const TKey& key) const
        {
            return hasher_(key) % buckets_.size();
        }

        std::size_t next_bucket_position(std::size_t pos) const
        {
            return (pos + 1) % buckets_.size();
        }

        const TKey* find_key(const TKey& key, std::size_t& position) const
        {
            std::size_t bucket_pos = bucket_position(key);
            for (TKey* ptr; (ptr = buckets_[bucket_pos].get()); bucket_pos = next_bucket_position(bucket_pos))
            {
                if (*ptr == key)
                {
                    position = bucket_pos;
                    return ptr;
                }
            }
            position = npos;
            return nullptr;
        }

        void resize(std::size_t new_capacity)
        {
            const std::size_t MIN_CAPACITY = 8;
            if (new_capacity <= MIN_CAPACITY)
                return;

            set<TKey> temp(new_capacity);
            for (auto& k : buckets_)
                if (k) temp.add(*k); //rehashing
            buckets_ = std::move(temp.buckets_);
            //size_ = temp.size_; //still same size_, don't need to update
        }

        bool needs_to_grow() const
        {
            return size() >= (3 * capacity()) / 4; //75% of buckets occupied 
        }

        bool needs_to_shrink() const
        {
            return 0 < size() && size() <= (1 * capacity()) / 4; //25% of buckets occupied
        }

        static set<TKey> clone(const set<TKey>& that)
        {
            set<TKey> temp(that.capacity());
            temp.size_ = that.size_;
            for (std::size_t i = 0; i < that.capacity(); ++i)
            {
                TKey* ptr = that.buckets_[i].get();
                if (ptr) temp.buckets_[i].reset(new TKey{ *ptr });
            }
            return std::move(temp);
        }

    private:
        std::vector<std::unique_ptr<TKey>> buckets_;
        std::size_t size_;
        std::hash<TKey> hasher_;
    };
}

#endif /* LINEAR_PROBING_HASHTABLE_HPP */