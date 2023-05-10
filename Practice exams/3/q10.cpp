#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int val): val(val), next(nullptr) {}
};

ListNode* reverse_linked_list(ListNode* head) {
// Reverse the linked list and return the new head after reversing
    ListNode *prev = nullptr, *curr = head, *next;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

bool is_target_in_list(ListNode* head, int target) {
// check if the linked list contains the target
    ListNode *curr = head;
    while (curr != nullptr) {
        if (curr->val == target) {
            return true;
        } else {
            curr = curr->next;
        }
    }
    return false;
}

int find_max(ListNode* head) {
// find the largest value in the node
    int max = head->val;
    ListNode *curr = head->next;
    while (curr != nullptr) {
        if (curr->val > max) {
            max = curr->val;
        }
        curr = curr->next;
    }
    return max;
}


int main() {
    ListNode* head = new ListNode(-1);
    ListNode* curr = head;
    for (int i = 0; i < 5; i++) {
        curr->next = new ListNode(i);
        curr = curr->next;
    }
    
    curr = head;
    while (curr != nullptr) {
        cout << curr->val << ' ';
        curr = curr->next;
    }
    cout << endl;

    cout << find_max(head) << endl;
    head = reverse_linked_list(head);

    curr = head;
    while (curr != nullptr) {
        cout << curr->val << ' ';
        curr = curr->next;
    }
    cout << endl;

    cout << is_target_in_list(head, 3) << endl;
    cout << is_target_in_list(head, 5) << endl;
    
    cout << find_max(head) << endl;

    return 0;
}