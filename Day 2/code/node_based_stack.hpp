//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef NODE_BASED_STACK_HPP
#define NODE_BASED_STACK_HPP

#include <cstddef>
#include <utility>

namespace node_based_stack
{
    //stack interface
    /*
    bool empty() const;
    size_t size() const;
    T& top();
    void push(const T&);
    void pop();
    void swap(stack&);
    */

    template <typename T>
    class node_based_stack final
    {
        struct singly_linked_node final
        {
            T item;
            singly_linked_node* next = nullptr;
        };

    public:
        using value_type = T;
        using size_type = std::size_t;

        node_based_stack() = default;
        ~node_based_stack()
        {
            while (!empty()) pop();
        }
        node_based_stack(const node_based_stack<T>&) = delete;
        node_based_stack<T>& operator=(const node_based_stack<T>&) = delete;

        bool empty() const
        {
            return root == nullptr;
        }

        std::size_t size() const
        {
            return n;
        }

        T& top()
        {
            return root->item;
        }

        void push(const T& val)
        {
            singly_linked_node* next = root;
            root = new singly_linked_node();
            root->item = val;
            root->next = next;
            ++n;
        }

        void pop()
        {
            singly_linked_node* previous = root;
            root = root->next;
            delete previous;
            --n;
        }

        void swap(node_based_stack<T>& that)
        {
            if (&that != this)
            {
                std::swap(root, that.root);
                std::swap(n, that.n);
            }
        }

    private:
        singly_linked_node* root = nullptr;
        std::size_t n = 0;
    };
};

#endif /* NODE_BASED_STACK_HPP */