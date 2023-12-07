// Author: Emre Çelik
// Question Link: https://leetcode.com/problems/swap-nodes-in-pairs/
// Reviewer: Denis Davidoglu

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        // If rest of our linked list is empty or have one node, return it from the head.
        if (head == NULL || head->next == NULL)
            return head;

        // Initialize our temporary head and next of our head.
        ListNode* tempHead = head;
        ListNode* temp = tempHead->next;

        // Swap our nodes.
        tempHead->next = tempHead->next->next;
        temp->next = tempHead;
        tempHead->next = swapPairs(tempHead->next);

        // Return next node from the temporary head recursively.
        return temp;
    }
};
