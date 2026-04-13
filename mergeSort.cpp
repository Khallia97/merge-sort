#include <iostream>
using namespace std;

// node struct
struct node {
    int data;
    node* next;
};

// split the list into two halves
void split(node* head, node*& left, node*& right) {
    node* slow = head;
    node* fast = head->next;

    // move fast twice as fast as slow to find middle
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    left = head;           // first half
    right = slow->next;    // second half
    slow->next = NULL;     // break the list
}

// merge two sorted linked lists
node* merge(node* left, node* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;

    node* result;

    // pick smaller value and recurse
    if (left->data <= right->data) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

// merge sort on linked list
node* mergeSort(node* head) {
    // base cases
    if (head == NULL || head->next == NULL)
        return head;

    node* left;
    node* right;

    split(head, left, right);   // divide

    left = mergeSort(left);     // sort left
    right = mergeSort(right);   // sort right

    return merge(left, right);  // combine
}

// insert node at end of list
void insert(node*& head, int val) {
    node* temp = new node{val, NULL};

    if (head == NULL) {
        head = temp;
        return;
    }

    node* curr = head;
    while (curr->next != NULL)
        curr = curr->next;

    curr->next = temp;
}

// print the linked list
void printList(node* head) {
    while (head != NULL) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL\n";
}

int main() {
    node* head = NULL;

    // array used to populate linked list
    int arr[] = {5, 2, 9, 1, 3};
    int size = 5;

    for (int i = 0; i < size; i++) {
        insert(head, arr[i]);
    }

    cout << "Original list:\n";
    printList(head);

    head = mergeSort(head);

    cout << "Sorted list:\n";
    printList(head);

    return 0;
}
