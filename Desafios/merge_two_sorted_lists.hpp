
//Definition for singly-linked list.
struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *node = nullptr;
        ListNode *inter = nullptr;
        while(list1 != nullptr || list2 != nullptr)
        {
            if(list1 != nullptr && list2 != nullptr)
            {
                int v1 = list1->val;
                int v2 = list2->val;
                if(v1 < v2)
                {
                    ListNode *n1 = new ListNode(v1);
                    if(inter != nullptr)
                        inter->next = n1;
                    if(node == nullptr)
                        node = n1;
                    inter = n1;
                    list1 = list1->next;
                }
                else if(v1 == v2)
                {
                    ListNode *n2 = new ListNode(v2);
                    ListNode *n1 = new ListNode(v1, n2);
                    if(inter != nullptr)
                        inter->next = n1;
                    if(node == nullptr)
                        node = n1;
                    inter = n2;
                    list1 = list1->next;
                    list2 = list2->next;
                }
                else
                {
                    ListNode *n1 = new ListNode(v2);
                    if(inter != nullptr)
                        inter->next = n1;
                    if(node == nullptr)
                        node = n1;
                    inter = n1;
                    list2 = list2->next;
                } 
            }

            if(list1 != nullptr && list2 == nullptr)
            {
                ListNode *n1 = new ListNode(list1->val);
                if(inter != nullptr)
                    inter->next = n1;
                if(node == nullptr)
                    node = n1;
                list1 = list1->next;
                inter = n1;
            }
            if(list1 == nullptr && list2 != nullptr)
            {
                ListNode *n1 = new ListNode(list2->val);
                if(inter != nullptr)
                    inter->next = n1;
                if(node == nullptr)
                    node = n1;
                list2 = list2->next;
                inter = n1;
            }
        }
        return node;
    }
};
