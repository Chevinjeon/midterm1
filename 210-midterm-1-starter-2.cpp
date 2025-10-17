// Include iostream library for input/output operations (cout, cin)
#include <iostream>
// Use standard namespace to avoid prefixing std:: to standard library elements
using namespace std;

// Define constants for number range (10-99) and list size range (5-20)
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// Define the DoublyLinkedList class - manages a linked list where each node points to both next and previous nodes
class DoublyLinkedList {
    private:
        // Inner struct Node - represents a single element in the doubly linked list
        struct Node {
            int data;        // Integer value stored in this node
            Node* prev;      // Pointer to the previous node in the list (nullptr if this is the first node)
            Node* next;      // Pointer to the next node in the list (nullptr if this is the last node)
            
            // Node constructor - initializes a new node with value and optional prev/next pointers
            Node(int val, Node* p = nullptr, Node* n = nullptr) {
                data = val;  // Set the data value for this node
                prev = p;    // Set the previous pointer (defaults to nullptr)
                next = n;    // Set the next pointer (defaults to nullptr)
            }
        };
    
        Node* head;  // Pointer to the first node in the list (nullptr if list is empty)
        Node* tail;  // Pointer to the last node in the list (nullptr if list is empty)
    