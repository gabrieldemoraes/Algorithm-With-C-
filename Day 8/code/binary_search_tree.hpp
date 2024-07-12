//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <vector>
#include <functional>
#include <queue>
#include <iostream>

namespace binary_search_tree
{
    template <typename T>
    struct bst_node
    {
        T value;
        bst_node* left = nullptr;
        bst_node* right = nullptr;
    };

    template <typename T>
    class bst
    {
        bst_node<T>* root = nullptr;
        std::vector<bst_node<T>*> nodes;
    public:
        bst() = default;

        ~bst()
        {
            destroy_nodes(nodes);
        }

        bst(const bst<T>&) = delete;
        bst<T>& operator=(const bst<T>&) = delete;

        bst(bst<T>&& that) : root(that.root), nodes(std::move(that.nodes))
        {
            that.root = nullptr;
        }

        bst<T>& operator=(bst<T>&& that)
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

        const bst_node<T>* get_root() const { return root; }

        void insert(const T& value) 
        { 
            root = insert(root, value, nodes); 
        }

    private:
        static bst_node<T>* insert(bst_node<T>* parent, const T& value, std::vector<bst_node<T>*>& nodes)
        {
            if (parent != nullptr)
            {
                if (value < parent->value)
                    parent->left = insert(parent->left, value, nodes);
                else //if (value >= parent->value)
                    parent->right = insert(parent->right, value, nodes);
                return parent;
            }
            nodes.push_back(new bst_node<T>{ value });
            return nodes.back();
        }

        static void destroy_nodes(std::vector<bst_node<T>*>& nodes)
        {
            for (bst_node<T>* node : nodes)
                delete node;
        }
    };

    enum class VisitStatus { Continue, Stop	};

    //breadth-first search
    template <typename T>
    static bool level_order_traversal(const bst_node<T>* node, std::function<VisitStatus(const T&)> visit)
    {
        if (node)
        {
            std::queue<bst_node<T>*> q;
            q.push(const_cast<bst_node<T>*>(node));
            while (!q.empty())
            {
                bst_node<T>* x = q.front();
                q.pop();
                if (visit(x->value) == VisitStatus::Stop)
                    return true;
                if (x->left)  q.push(x->left);
                if (x->right) q.push(x->right);
            }
        }
        return false;
    }

    //depth-first search
    namespace internal
    {
        template <typename T>
        static VisitStatus pre_order_traversal_recursive(const bst_node<T>* node, std::function<VisitStatus(const T&)> visit)
        {
            if (node)
            {
                VisitStatus visit_status = visit(node->value);
                if (visit_status == VisitStatus::Stop) return VisitStatus::Stop;
                
                visit_status = pre_order_traversal_recursive<T>(node->left, visit);
                if (visit_status == VisitStatus::Stop) return VisitStatus::Stop;
                
                visit_status = pre_order_traversal_recursive<T>(node->right, visit);
                if (visit_status == VisitStatus::Stop) return VisitStatus::Stop;
            }
            return VisitStatus::Continue;
        }
    }

    template <typename T>
    static bool pre_order_traversal(const bst_node<T>* node, std::function<VisitStatus(const T&)> visit)
    {
        return internal::pre_order_traversal_recursive(node, visit) == VisitStatus::Stop;
    }

    namespace internal
    {
        template <typename T>
        static VisitStatus in_order_traversal_recursive(const bst_node<T>* node, std::function<VisitStatus(const T&)> visit)
        {
            if (node)
            {
                VisitStatus visit_status = in_order_traversal_recursive<T>(node->left, visit);
                if (visit_status == VisitStatus::Stop) return VisitStatus::Stop;

                visit_status = visit(node->value);
                if (visit_status == VisitStatus::Stop) return VisitStatus::Stop;

                visit_status = in_order_traversal_recursive<T>(node->right, visit);
                if (visit_status == VisitStatus::Stop) return VisitStatus::Stop;
            }
            return VisitStatus::Continue;
        }
    }

    template <typename T>
    static bool in_order_traversal(const bst_node<T>* node, std::function<VisitStatus(const T&)> visit)
    {
        return internal::in_order_traversal_recursive(node, visit) == VisitStatus::Stop;
    }

    namespace internal
    {
        template <typename T>
        static VisitStatus out_order_traversal_recursive(const bst_node<T>* node, std::function<VisitStatus(const T&)> visit)
        {
            if (node)
            {
                VisitStatus visit_status = out_order_traversal_recursive<T>(node->right, visit);
                if (visit_status == VisitStatus::Stop) return VisitStatus::Stop;

                visit_status = visit(node->value);
                if (visit_status == VisitStatus::Stop) return VisitStatus::Stop;

                visit_status = out_order_traversal_recursive<T>(node->left, visit);
                if (visit_status == VisitStatus::Stop) return VisitStatus::Stop;
            }
            return VisitStatus::Continue;
        }
    }

    template <typename T>
    static bool out_order_traversal(const bst_node<T>* node, std::function<VisitStatus(const T&)> visit)
    {
        return internal::out_order_traversal_recursive(node, visit) == VisitStatus::Stop;
    }

    namespace internal
    {
        template <typename T>
        static VisitStatus post_order_traversal_recursive(const bst_node<T>* node, std::function<VisitStatus(const T&)> visit)
        {
            if (node)
            {
                VisitStatus visit_status = post_order_traversal_recursive<T>(node->left, visit);
                if (visit_status == VisitStatus::Stop) return VisitStatus::Stop;

                visit_status = post_order_traversal_recursive<T>(node->right, visit);
                if (visit_status == VisitStatus::Stop) return VisitStatus::Stop;

                visit_status = visit(node->value);
                if (visit_status == VisitStatus::Stop) return VisitStatus::Stop;
            }
            return VisitStatus::Continue;
        }
    }

    template <typename T>
    static bool post_order_traversal(const bst_node<T>* node, std::function<VisitStatus(const T&)> visit)
    {
        return internal::post_order_traversal_recursive(node, visit) == VisitStatus::Stop;
    }
}

#endif /* BINARY_SEARCH_TREE_HPP */