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
    
    public:
        // Constructor - initializes an empty doubly linked list
        DoublyLinkedList() { 
            head = nullptr;  // Set head pointer to nullptr (empty list)
            tail = nullptr;  // Set tail pointer to nullptr (empty list)
        }
    
        // insert_after - inserts a new node with 'value' after the node at 'position'
        void insert_after(int value, int position) {
            // Validate position - must be non-negative
            if (position < 0) {
                cout << "Position must be >= 0." << endl;  // Error message for negative position
                return;  // Exit function without inserting
            }
    
            // Allocate memory for new node on the heap and initialize it with the value
            Node* newNode = new Node(value);
            
            // Special case: if list is empty (head is nullptr)
            if (!head) {
                head = tail = newNode;  // Make both head and tail point to the new node (single-element list)
                return;  // Exit function - insertion complete
            }
    
            // Traverse to find the node at the specified position
            Node* temp = head;  // Start temp pointer at the head of the list
            // Loop from 0 to position-1, moving temp forward each time
            for (int i = 0; i < position && temp; ++i)
                temp = temp->next;  // Move temp to point to the next node
    
            // Check if position exceeds list bounds (temp became nullptr before reaching position)
            if (!temp) {
                cout << "Position exceeds list size. Node not inserted.\n";  // Error message
                delete newNode;  // Free the memory we allocated for newNode (prevent memory leak)
                return;  // Exit without inserting
            }
    
            // Insert newNode after temp
            newNode->next = temp->next;  // Make newNode's next point to what temp was pointing to
            newNode->prev = temp;        // Make newNode's prev point back to temp
