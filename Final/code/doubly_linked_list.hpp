//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <cstddef>

namespace doubly_linked_list
{
    //doubly_linked_list interface
    /*
    void traverse_forward(doubly_linked_list<T>&, Visit);
    void traverse_backward(doubly_linked_list<T>&, Visit);
    doubly_linked_node<T>* find_forward(doubly_linked_list<T>&, const T&);
    doubly_linked_node<T>* find_backward(doubly_linked_list<T>&, const T&);
    void prepend(doubly_linked_list<T>&, const T&);
    void append(doubly_linked_list<T>&, const T&);
    void insert_before(doubly_linked_list<T>&, const T&, const T&);
    void insert_after(doubly_linked_list<T>&, const T&, const T&);
    void remove_forward(doubly_linked_list<T>&, const T&);
    void remove_backward(doubly_linked_list<T>&, const T&);
    void remove_front(doubly_linked_list<T>&);
    void remove_back(doubly_linked_list<T>&);
    void clear(doubly_linked_list<T>&);
    std::size_t count(doubly_linked_list<T>&);
    std::ptrdiff_t distance_forward(doubly_linked_list<T>&, const T&)
    std::ptrdiff_t distance_backward(doubly_linked_list<T>&, const T&)
    */
    
    template <typename T>
    struct doubly_linked_node final
    {
        doubly_linked_node<T>* prev = nullptr;
        doubly_linked_node<T>* next = nullptr;
        T data;
    };

    template <typename T>
    struct doubly_linked_list final
    {
        doubly_linked_node<T>* first = nullptr;
        doubly_linked_node<T>* last = nullptr;
    };

    namespace internal
    {
        template <typename T>
        static inline void insert_node_before(doubly_linked_list<T>& list, doubly_linked_node<T>* node, doubly_linked_node<T>* new_node)
        {
            new_node->next = node;
            if (node->prev == nullptr)
            {
                list.first = new_node;
            }
            else
            {
                new_node->prev = node->prev;
                node->prev->next = new_node;
            }
            node->prev = new_node;
        }

        template <typename T>
        static inline void insert_node_after(doubly_linked_list<T>& list, doubly_linked_node<T>* node, doubly_linked_node<T>* new_node)
        {
            new_node->prev = node;
            if (node->next == nullptr)
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
        static inline doubly_linked_node<T>* make_node(const T& new_val)
        {
            doubly_linked_node<T>* new_node = new doubly_linked_node<T>;
            new_node->data = new_val;
            new_node->prev = new_node->next = nullptr;
            return new_node; //leak
        }

        template <typename T>
        static inline void remove_node(doubly_linked_list<T>& list, doubly_linked_node<T>* node)
        {
            if (node != nullptr)
            {
                if (node->prev == nullptr)
                {
                    list.first = node->next;
                }
                else
                {
                    node->prev->next = node->next;
                }

                if (node->next == nullptr)
                {
                    list.last = node->prev;
                }
                else
                {
                    node->next->prev = node->prev;
                }
                delete node; //unleak
            }
        }
    }

    template <typename T, typename Visit>
    static inline void traverse_forward(doubly_linked_list<T>& list, Visit visit)
    {
        doubly_linked_node<T>* node = list.first;
        while (node != nullptr)
        {
            visit(node->data);
            node = node->next;
        }
    }

    template <typename T, typename Visit>
    static inline void traverse_backward(doubly_linked_list<T>& list, Visit visit)
    {
        doubly_linked_node<T>* node = list.last;
        while (node != nullptr)
        {
            visit(node->data);
            node = node->prev;
        }
    }

    template <typename T>
    static inline doubly_linked_node<T>* find_forward(doubly_linked_list<T>& list, const T& val)
    {
        doubly_linked_node<T>* node = list.first;
        while (node != nullptr)
        {
            if (node->data == val)
                return node;
            node = node->next;
        }
        return nullptr;
    }

    template <typename T>
    static inline doubly_linked_node<T>* find_backward(doubly_linked_list<T>& list, const T& val)
    {
        doubly_linked_node<T>* node = list.last;
        while (node != nullptr)
        {
            if (node->data == val)
                return node;
            node = node->prev;
        }
        return nullptr;
    }

    template <typename T>
    static inline void prepend(doubly_linked_list<T>& list, const T& new_val)
    {
        if (list.first == nullptr)
        {
            list.first = list.last = internal::make_node(new_val);
        }
        else
        {
            internal::insert_node_before(list, list.first, internal::make_node(new_val));
        }
    }

    template <typename T>
    static inline void append(doubly_linked_list<T>& list, const T& new_val)
    {
        if (list.last == nullptr)
        {
            prepend(list, new_val);
        }
        else
        {
            internal::insert_node_after(list, list.last, internal::make_node(new_val));
        }
    }

    template <typename T>
    static inline void insert_before(doubly_linked_list<T>& list, const T& val, const T& new_val)
    {
        doubly_linked_node<T>* node = find_backward(list, val);
        if (node == nullptr)
        {
            prepend(list, new_val);
        }
        else
        {
            internal::insert_node_before(list, node, internal::make_node(new_val));
        }
    }

    template <typename T>
    static inline void insert_after(doubly_linked_list<T>& list, const T& val, const T& new_val)
    {
        doubly_linked_node<T>* node = find_forward(list, val);
        if (node == nullptr)
        {
            append(list, new_val);
        }
        else
        {
            internal::insert_node_after(list, node, internal::make_node(new_val));
        }
    }

    template <typename T>
    static inline void remove_forward(doubly_linked_list<T>& list, const T& val)
    {
        internal::remove_node(list, find_forward(list, val));
    }

    template <typename T>
    static inline void remove_backward(doubly_linked_list<T>& list, const T& val)
    {
        internal::remove_node(list, find_backward(list, val));
    }

    template <typename T>
    static inline void remove_front(doubly_linked_list<T>& list)
    {
        internal::remove_node(list, list.first);
    }
    
    template <typename T>
    static inline void remove_back(doubly_linked_list<T>& list)
    {
        internal::remove_node(list, list.last);
    }

    template <typename T>
    static inline void clear(doubly_linked_list<T>& list)
    {
        doubly_linked_node<T>* node = list.first;
        while (node != nullptr)
        {
            doubly_linked_node<T>* next = node->next;
            delete node;
            node = next;
        }
        list.first = list.last = nullptr;
    }

    template <typename T>
    static inline std::size_t count(doubly_linked_list<T>& list)
    {
        std::size_t counter = 0;
        doubly_linked_node<T>* node = list.first;
        while (node != nullptr)
        {
            ++counter;
            node = node->next;
        }
        return counter;
    }

    template <typename T>
    static inline std::ptrdiff_t distance_forward(doubly_linked_list<T>& list, const T& val)
    {
        std::ptrdiff_t counter = 0;
        doubly_linked_node<T>* node = list.first;
        while (node != nullptr)
        {
            if (node->data == val)
                return counter;
            node = node->next;
            ++counter;
        }
        return -1;
    }

    template <typename T>
    static inline std::ptrdiff_t distance_backward(doubly_linked_list<T>& list, const T& val)
    {
        std::ptrdiff_t counter = 0;
        doubly_linked_node<T>* node = list.last;
        while (node != nullptr)
        {
            if (node->data == val)
                return counter;
            node = node->prev;
            ++counter;
        }
        return -1;
    }
}

#endif /* DOUBLY_LINKED_LIST_HPP */