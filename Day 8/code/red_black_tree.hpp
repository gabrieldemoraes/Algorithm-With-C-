//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <vector>
#include <functional>
#include <queue>

//#define TRACE

#ifdef TRACE
#include <iostream>
#endif

namespace red_black_tree
{
    enum class Color { Black, Red };

    template <typename T>
    struct rb_node
    {
        T value;
        rb_node* left = nullptr;
        rb_node* right = nullptr;
        Color color = Color::Red;
        bool red() const { return color == Color::Red; }
    };

    template <typename T>
    class rb
    {
        rb_node<T>* root = nullptr;
        std::vector<rb_node<T>*> nodes;
    public:
        rb() = default;

        ~rb()
        {
            destroy_nodes(nodes);
        }

        rb(const rb<T>&) = delete;
        rb<T>& operator=(const rb<T>&) = delete;

        rb(rb<T>&& that) : root(that.root), nodes(std::move(that.nodes))
        {
            that.root = nullptr;
        }

        rb<T>& operator=(rb<T>&& that)
        {
            if (this != *that)
            {
                root = that.root;
                that.root = nullptr;
                destroy_nodes(nodes);
                nodes = std::move(that.nodes);
            }
            return *this;
        }

        const rb_node<T>* get_root() const { return root; }

        void insert(const T& value)
        {
            #ifdef TRACE
            std::cout << value << ": ";
            #endif

            root = insert(root, value, nodes);

            #ifdef TRACE
            std::cout << "\n";
            #endif
        }

    private:
        static rb_node<T>* insert(rb_node<T>* parent, const T& value, std::vector<rb_node<T>*>& nodes)
        {
            if (parent != nullptr)
            {
                //find insertion point
                if (value < parent->value)
                    parent->left = insert(parent->left, value, nodes);
                else //if (value >= parent->value)
                    parent->right = insert(parent->right, value, nodes);

                //adjust nodes (balance)
                if (is_red(parent->right) && !is_red(parent->left))
                    parent = rotate_left(parent);
                if (is_red(parent->left) && is_red(parent->left->left))
                    parent = rotate_right(parent);
                if (is_red(parent->left) && is_red(parent->right))
                    parent = flip_colors(parent);

                return parent;
            }
            nodes.push_back(new rb_node<T>{ value });
            return nodes.back();
            return nullptr;
        }

        static inline bool is_red(rb_node<T>* node)
        {
            if (node)
                return node->red();
            return false;
        }

        static rb_node<T>* rotate_left(rb_node<T>* node)
        {
            #ifdef TRACE
            std::cout << "rotate left" << "; ";
            #endif

            rb_node<T>* temp = node->right;
            node->right = temp->left;
            temp->left = node;
            temp->color = node->color;
            node->color = Color::Red;
            return temp;
        }

        static rb_node<T>* rotate_right(rb_node<T>* node)
        {
            #ifdef TRACE
            std::cout << "rotate right" << "; ";
            #endif

            rb_node<T>* temp = node->left;
            node->left = temp->right;
            temp->right = node;
            temp->color = node->color;
            node->color = Color::Red;
            return temp;
        }

        static rb_node<T>* flip_colors(rb_node<T>* node)
        {
            #ifdef TRACE
            std::cout << "flip colors" << "; ";
            #endif

            node->left->color = Color::Black;
            node->right->color = Color::Black;
            node->color = Color::Red;
            return node;
        }

        static void destroy_nodes(std::vector<rb_node<T>*>& nodes)
        {
            for (rb_node<T>* node : nodes)
                delete node;
        }
    };

    enum class VisitStatus { Continue, Stop };

    //breadth-first search
    template <typename T>
    static bool level_order_traversal(const rb_node<T>* node, std::function<VisitStatus(const T&)> visit)
    {
        if (node)
        {
            std::queue<rb_node<T>*> q;
            q.push(const_cast<rb_node<T>*>(node));
            while (!q.empty())
            {
                rb_node<T>* x = q.front();
                q.pop();
                if (visit(x->value) == VisitStatus::Stop)
                    return true;
                if (x->left)  q.push(x->left);
                if (x->right) q.push(x->right);
            }
        }
        return false;
    }
}

#endif /* RED_BLACK_TREE_HPP */
