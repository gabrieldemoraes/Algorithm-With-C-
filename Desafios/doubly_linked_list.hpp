#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP

#include <iostream>

class double_linked_list
{
public:
    class double_linked_node {
        public:
            int val;
            double_linked_node* next;
            double_linked_node* previous;

            double_linked_node(int _val) {
                val = _val;
                next = NULL;
                previous = NULL;
            }
    };

    class list
    {
        public:
            double_linked_node* first = nullptr;
            double_linked_node* last = nullptr;
    };

static void append(list *list, double_linked_node *newNode)
{
    if(list->first == nullptr)
        list->first = newNode;
    else 
    {
        newNode->next = list->first;
        list->first->previous = newNode;
        list->first = newNode;
    }
}

static void prepend(list *list, double_linked_node *newNode)
{
    if(list->first == nullptr)
        list->first = newNode;
    else if(list->first!=nullptr && list->last == nullptr)
    {
        list->first->next = newNode;
        newNode->previous = list->first;
        list->last = newNode;
    }
    else
    {
        list->last->next = newNode;
        newNode->previous = list->last;
        list->last = newNode;
    }
}

static void insert_before(list *list, double_linked_node *newNode, int value)
{
    double_linked_node *node = list->first;
    while(node->val != value)
        node = node->next; 
    if(node != nullptr)
    {
        double_linked_node *inter = node->previous;
        newNode->previous = inter;
        newNode->next = node;
        node->previous = newNode; 
    }
    else std::cout << "Didn't find the inserted value." << "\n";
}

static void insert_after(list *list, double_linked_node *newNode, int value)
{
    double_linked_node *node = list->first;
    while(node->val != value)
        node = node->next; 
    if(node != nullptr)
    {
        double_linked_node *inter = node->next;
        newNode->previous = node;
        newNode->next = inter;
        node->next = newNode; 
    }
    else std::cout << "Didn't find the inserted value." << "\n";
}

static void remove_node(list *list, int value)
{
    double_linked_node *node = list->first;
    while(node->val != value)
        node = node->next; 
    if(node != nullptr)
    {
        double_linked_node *before = node->previous;
        double_linked_node *after = node->next;
        before->next = after;
        after->previous = before;
        delete node;
    }
    else std::cout << "Didn't find the inserted value." << "\n";
}

static void remove_before(list *list, int value)
{
    double_linked_node *node = list->first;
    while(node->val != value)
        node = node->next; 
    if(node != nullptr)
    {
        double_linked_node *del = node->previous;
        double_linked_node *inter = del->previous;
        node->previous = inter;
        inter->next = node;

        delete del;
    }
    else std::cout << "Didn't find the inserted value." << "\n";
}

static void remove_after(list *list, int value)
{
    double_linked_node *node = list->first;
    while(node->val != value)
        node = node->next; 
    if(node != nullptr)
    {
        double_linked_node *del = node->next;
        double_linked_node *inter = del->next;
        node->previous = inter;
        inter->next = node;

        delete del;
    }
    else std::cout << "Didn't find the inserted value." << "\n";
}

static void transverse_foward(list *list, int value)
{
    double_linked_node *node = list->first;
    while(node->val != value)
        node = node->next; 
    if(node != nullptr)
    {
       while(node!=nullptr)
       {
         std::cout << "Value: " << node->val << "\n";
         node = node->next;
       }
    }
    else std::cout << "Didn't find the inserted value." << "\n";
}

static void transverse_backward(list *list, int value)
{
    double_linked_node *node = list->first;
    while(node->val != value)
        node = node->next; 
    if(node != nullptr)
    {
       while(node!=nullptr)
       {
         std::cout << "Value: " << node->val << "\n";
         node = node->previous;
       }
    }
    else std::cout << "Didn't find the inserted value." << "\n";
}

};
#endif