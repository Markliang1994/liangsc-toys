//
// Created by mark on 16-12-18.
//

// I know the code is very ugly. But I don't want to fix it
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *head = NULL, *prev = NULL;
        while(l1 || l2){
            if(!l1 && l2){
                if(head){
                    prev->next = l2;
                    prev = prev->next;
                }
                else{
                    prev = l2;
                    head = l2;
                }
                l2 = l2->next;
            }
            else if(l1 && !l2){
                if(head){
                    prev->next = l1;
                    prev = prev->next;
                }
                else{
                    prev = l1;
                    head = l1;
                }
                l1 = l1->next;
            }
            else{
                if(l1->val < l2->val){
                    if(head){
                        prev->next = l1;
                        prev = prev->next;
                    }
                    else{
                        prev = l1;
                        head = l1;
                    }
                    l1 = l1->next;
                }
                else{
                    if(head){
                        prev->next = l2;
                        prev = prev->next;
                    }
                    else{
                        prev = l2;
                        head = l2;
                    }
                    l2 = l2->next;
                }
            }
        }
        return head;
    }
};
