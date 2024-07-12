//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef DOUBLY_LINKED_LIST_ALT_HPP
#define DOUBLY_LINKED_LIST_ALT_HPP

#include <memory>
#include <cstddef>

namespace doubly_linked_list_alt
{
    //doubly_linked_list_alt interface
    /*
    void traverse_forward(doubly_linked_list_alt<T>&, Visit);
    void traverse_backward(doubly_linked_list_alt<T>& list, Visit visit);
    std::shared_ptr<doubly_linked_node_alt<T>> find_forward(doubly_linked_list_alt<T>&, const T&);
    std::shared_ptr<doubly_linked_node_alt<T>> find_backward(doubly_linked_list_alt<T>&, const T&);
    void prepend(doubly_linked_list_alt<T>&, const T&);
    void append(doubly_linked_list_alt<T>&, const T&);
    void insert_before(doubly_linked_list_alt<T>&, const T&, const T&);
    void insert_after(doubly_linked_list_alt<T>&, const T&, const T&);
    void remove_forward(doubly_linked_list_alt<T>&, const T&);
    void remove_backward(doubly_linked_list_alt<T>&, const T&);
    void remove_front(doubly_linked_list_alt<T>&);
    void remove_back(doubly_linked_list_alt<T>&);
    void clear(doubly_linked_list_alt<T>&);
    std::size_t count(doubly_linked_list_alt<T>&);
    */
    
    template <typename T>
    struct doubly_linked_node_alt final
    {
        std::weak_ptr<doubly_linked_node_alt<T>> prev;
        std::shared_ptr<doubly_linked_node_alt<T>> next;
        T data;
    };

    template <typename T>
    struct doubly_linked_list_alt final
    {
        std::shared_ptr<doubly_linked_node_alt<T>> first;
        std::weak_ptr<doubly_linked_node_alt<T>> last;
    };

    namespace internal
    {
        template <typename T>
        static inline void insert_node_before(doubly_linked_list_alt<T>& list, std::shared_ptr<doubly_linked_node_alt<T>> node, std::shared_ptr<doubly_linked_node_alt<T>> new_node)
        {
            new_node->next = node;			
            auto prev_node = node->prev.lock();
            if (!prev_node)
            {
                list.first = new_node;
            }
            else
            {
                new_node->prev = node->prev;
                prev_node->next = new_node;
            }
            node->prev = new_node;
        }

        template <typename T>
        static inline void insert_node_after(doubly_linked_list_alt<T>& list, std::shared_ptr<doubly_linked_node_alt<T>> node, std::shared_ptr<doubly_linked_node_alt<T>> new_node)
        {
            new_node->prev = node;
            if (!node->next)
            {
                list.last = new_node;
            }
            else
            {
                new_node->next = node->next;
                node->next->prev = new_node;
            }
            node->next = new_node;
        }

        template <typename T>
        static inline std::shared_ptr<doubly_linked_node_alt<T>> make_node(const T& new_val)
        {
            //std::shared_ptr<doubly_linked_node_alt<T>> new_node(new doubly_linked_node_alt<T>);
            std::shared_ptr<doubly_linked_node_alt<T>> new_node = std::make_shared<doubly_linked_node_alt<T>>();
            new_node->data = new_val;
            return new_node;
        }

        template <typename T>
        static inline void remove_node(doubly_linked_list_alt<T>& list, std::shared_ptr<doubly_linked_node_alt<T>> node)
        {
            if (node)
            {
                auto node_prev = node->prev.lock();
                if (!node_prev)
                {
                    list.first = node->next;
                }
                else
                {
                    node_prev->next = node->next;
                }

                if (!node->next)
                {
                    list.last = node->prev;					
                }
                else
                {
                    node->next->prev = node->prev;
                }
            }
        }
    }

    template <typename T, typename Visit>
    static inline void traverse_forward(doubly_linked_list_alt<T>& list, Visit visit)
    {
        doubly_linked_node_alt<T>* node = list.first.get();
        while (node)
        {
            visit(node->data);
            node = node->next.get();
        }
    }

    template <typename T, typename Visit>
    static inline void traverse_backward(doubly_linked_list_alt<T>& list, Visit visit)
    {
        doubly_linked_node_alt<T>* node = list.last.lock().get();
        while (node)
        {
            visit(node->data);
            node = node->prev.lock().get();
        }
    }

    template <typename T>
    static inline std::shared_ptr<doubly_linked_node_alt<T>> find_forward(doubly_linked_list_alt<T>& list, const T& val)
    {
        std::shared_ptr<doubly_linked_node_alt<T>> node = list.first;
        while (node)
        {
            if (node->data == val)
                return node;
            node = node->next;
        }
        return nullptr;
    }

    template <typename T>
    static inline std::shared_ptr<doubly_linked_node_alt<T>> find_backward(doubly_linked_list_alt<T>& list, const T& val)
    {
        std::shared_ptr<doubly_linked_node_alt<T>> node = list.last.lock();
        while (node)
        {
            if (node->data == val)
                return node;
            node = node->prev.lock();
        }
        return nullptr;
    }

    template <typename T>
    static inline void prepend(doubly_linked_list_alt<T>& list, const T& new_val)
    {
        if (!list.first)
        {
            list.first = internal::make_node(new_val);
            list.last = list.first;
        }
        else
        {
            internal::insert_node_before(list, list.first, internal::make_node(new_val));
        }
    }

    template <typename T>
    static inline void append(doubly_linked_list_alt<T>& list, const T& new_val)
    {
        auto list_last = list.last.lock();
        if (!list_last)
        {
            prepend(list, new_val);
        }
        else
        {
            internal::insert_node_after(list, list_last, internal::make_node(new_val));
        }
    }

    template <typename T>
    static inline void insert_before(doubly_linked_list_alt<T>& list, const T& val, const T& new_val)
    {
        std::shared_ptr<doubly_linked_node_alt<T>> node = find_backward(list, val);
        if (!node)
        {
            prepend(list, new_val);
        }
        else
        {
            internal::insert_node_before(list, node, internal::make_node(new_val));
        }
    }

    template <typename T>
    static inline void insert_after(doubly_linked_list_alt<T>& list, const T& val, const T& new_val)
    {
        std::shared_ptr<doubly_linked_node_alt<T>> node = find_forward(list, val);
        if (!node)
        {
            append(list, new_val);
        }
        else
        {
            internal::insert_node_after(list, node, internal::make_node(new_val));
        }
    }

    template <typename T>
    static inline void remove_forward(doubly_linked_list_alt<T>& list, const T& val)
    {
        internal::remove_node(list, find_forward(list, val));
    }

    template <typename T>
    static inline void remove_backward(doubly_linked_list_alt<T>& list, const T& val)
    {
        internal::remove_node(list, find_backward(list, val));
    }

    template <typename T>
    static inline void remove_front(doubly_linked_list_alt<T>& list)
    {
        internal::remove_node(list, list.first);
    }

    template <typename T>
    static inline void remove_back(doubly_linked_list_alt<T>& list)
    {
        internal::remove_node(list, list.last.lock());
    }

    template <typename T>
    static inline void clear(doubly_linked_list_alt<T>& list)
    {
        std::shared_ptr<doubly_linked_node_alt<T>>& node = list.first;
        while (node != nullptr)
        {
            std::shared_ptr<doubly_linked_node_alt<T>> next = node->next;
            node.reset();
            node = next;
        }
    }

    template <typename T>
    static inline std::size_t count(doubly_linked_list_alt<T>& list)
    {
        std::size_t counter = 0;
        doubly_linked_node_alt<T>* node = list.first.get();
        while (node != nullptr)
        {
            ++counter;
            node = node->next.get();
        }
        return counter;
    }
}

#endif /* DOUBLY_LINKED_LIST_ALR_HPP */