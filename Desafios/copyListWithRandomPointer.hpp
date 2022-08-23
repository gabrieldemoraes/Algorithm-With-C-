#ifndef DEEP_COPY_HPP
#define DEEP_COPY_HPP

#include <iostream>
#include <stdlib.h>
#include <vector>

// Definition for a Node.
class Node 
{
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) 
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    
    void insert_next_node(Node *newHead, Node *nextNode)
    {
        while (newHead->next != NULL)
            newHead = newHead->next;

        newHead->next = nextNode;
    }
    
    static inline void insert_random(Node* newHead, Node *node, int position)
    {
        if (position == -1)
            node->random = nullptr;
        else
        {
            Node* inter = newHead;
            
            for (int i = 0; i < position; ++i)
                inter = inter->next;

            node->random = inter;
        }
    }
    
    Node* copyRandomList(Node* head) 
    {
        Node* reference = head;

        std::vector <int> values;
        std::vector <int> positions;
        std::vector <int>::iterator it;

        while (reference != NULL)
        {
            values.push_back(reference->val);
            reference = reference->next;
        }
        
        if(head != nullptr)
        {
            reference = head;
            int j = 0;
            for (int i = 0; i < values.size(); ++i)
            {
                j = 0;
                if (reference != NULL && reference->random != NULL)
                {
                    Node* random = reference->random;
                    Node* node = head;
                    while (node != random && node->next != NULL)
                    {
                        node = node->next;
                        ++j;
                    }
                    positions.push_back(j);
                    reference = reference->next;
                }
                else if(reference && reference->random == NULL)
                {
                    positions.push_back(-1);
                    reference = reference->next;
                }
            }
        }
        if (values.empty())
        {
            Node* newHead = nullptr;
            return newHead;
        }
        else
        {
            it = values.begin();
            Node* newHead = new Node(*it);
            ++it;

            for (; it != values.end(); ++it)
            {
                Node* n = new Node(*it);
                insert_next_node(newHead, n);
            }

            Node* inter = newHead;

            for (it = positions.begin(); it != positions.end(); ++it)
            {
                insert_random(newHead, inter, *it);
                inter = inter->next;
            }
            return newHead;
        }
    }
};

#endif