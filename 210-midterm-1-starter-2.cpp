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
            
            // Update the node after newNode (if it exists) to point back to newNode
            if (temp->next)
                temp->next->prev = newNode;  // Update the next node's prev pointer to newNode
            else
                tail = newNode;  // If temp was the tail, update tail to point to newNode
            
            temp->next = newNode;  // Finally, make temp's next point to newNode, completing the insertion
        }
    
        // delete_val - deletes the first node that contains the specified value
        void delete_val(int value) {
            // Check if list is empty - nothing to delete
            if (!head) return;  // Exit if head is nullptr (empty list)
    
            // Start traversing from the head to find the node with the target value
            Node* temp = head;  // temp pointer starts at the first node
            
            // Traverse the list while temp is not nullptr AND data doesn't match value
            while (temp && temp->data != value)
                temp = temp->next;  // Move temp to the next node
    
            // If we reached the end without finding the value, exit
            if (!temp) return;  // temp is nullptr means value not found in list
    
            // Update the previous node's next pointer to skip over temp
            if (temp->prev)
                temp->prev->next = temp->next;  // Make previous node point to node after temp
            else
                head = temp->next;  // If temp is the head, update head to the next node
    
            // Update the next node's prev pointer to skip over temp
            if (temp->next)
                temp->next->prev = temp->prev;  // Make next node point back to node before temp
            else
                tail = temp->prev;  // If temp is the tail, update tail to the previous node
    
            delete temp;  // Free the memory occupied by the node we're deleting
        }
    
        // delete_pos - deletes the node at the specified position (1-indexed)
        void delete_pos(int pos) {
            // Check if list is empty
            if (!head) {
                cout << "List is empty." << endl;  // Error message for empty list
                return;  // Exit without deleting
            }
        
            // Special case: deleting the first node (position 1)
            if (pos == 1) {
                pop_front();  // Call pop_front() to handle deletion of head node
                return;  // Exit after deletion
            }
        
            // Traverse to find the node at position pos
            Node* temp = head;  // Start temp at the head (position 1)
        
            // Loop to move temp to the node at position pos
            for (int i = 1; i < pos; i++){
                // Check if we've reached the end prematurely
                if (!temp) {
                    cout << "Position doesn't exist." << endl;  // Error: position beyond list
                    return;  // Exit without deleting
                }
                else
                    temp = temp->next;  // Move temp to the next node
            }
            
            // Double-check that temp is valid (position exists)
            if (!temp) {
                cout << "Position doesn't exist." << endl;  // Error: position doesn't exist
                return;  // Exit without deleting
            }
        
            // Special case: if temp is the last node (tail)
            if (!temp->next) {
                pop_back();  // Call pop_back() to handle deletion of tail node
                return;  // Exit after deletion
            }
        
            // Delete temp (middle node case)
            Node* tempPrev = temp->prev;        // Store pointer to the previous node
            tempPrev->next = temp->next;        // Make previous node skip over temp, point to next node
            temp->next->prev = tempPrev;        // Make next node point back to previous node
            delete temp;                        // Free the memory of the deleted node
        }
    
        // push_back - adds a new node with value v at the end of the list
        void push_back(int v) {
            Node* newNode = new Node(v);  // Allocate memory for new node and initialize with value v
            
            // Check if list is empty (tail is nullptr)
            if (!tail)
                head = tail = newNode;  // Make both head and tail point to newNode (first element)
            else {
                tail->next = newNode;   // Make current tail's next pointer point to newNode
                newNode->prev = tail;   // Make newNode's prev pointer point back to current tail
                tail = newNode;         // Update tail to point to newNode (new last element)
            }
        }
        
        // push_front - adds a new node with value v at the beginning of the list
        void push_front(int v) {
            Node* newNode = new Node(v);  // Allocate memory for new node and initialize with value v
            
            // Check if list is empty (head is nullptr)
            if (!head)
                head = tail = newNode;  // Make both head and tail point to newNode (first element)
            else {
                newNode->next = head;   // Make newNode's next pointer point to current head
                head->prev = newNode;   // Make current head's prev pointer point back to newNode
                head = newNode;         // Update head to point to newNode (new first element)
            }
        }
        
        // pop_front - removes the first node from the list
        void pop_front() {
            // Check if list is empty
            if (!head) {
                cout << "List is empty." << endl;  // Error message for empty list
                return;  // Exit without deleting
            }
    
            Node * temp = head;  // Store pointer to current head (node to be deleted)
    
            // Check if there's more than one node in the list
            if (head->next) {
                head = head->next;      // Move head pointer to the second node
                head->prev = nullptr;   // Set new head's prev to nullptr (it's now the first node)
            }
            else
                head = tail = nullptr;  // List had only one node, so make both head and tail nullptr
            
            delete temp;  // Free the memory of the old head node
        }
    
        // pop_back - removes the last node from the list
        void pop_back() {
            // Check if list is empty
            if (!tail) {
                cout << "List is empty." << endl;  // Error message for empty list
                return;  // Exit without deleting
            }
            
            Node * temp = tail;  // Store pointer to current tail (node to be deleted)
    
            // Check if there's more than one node in the list
            if (tail->prev) {
                tail = tail->prev;      // Move tail pointer to the second-to-last node
                tail->next = nullptr;   // Set new tail's next to nullptr (it's now the last node)
            }
            else
                head = tail = nullptr;  // List had only one node, so make both head and tail nullptr
            
            delete temp;  // Free the memory of the old tail node
        }
    
        // Destructor - cleans up all allocated memory when the list object is destroyed
        ~DoublyLinkedList() {
            // Loop through all nodes starting from head
            while (head) {
                Node* temp = head;      // Store current head in temp
                head = head->next;      // Move head to the next node
                delete temp;            // Free the memory of the previous head
            }
            // When loop ends, all nodes have been deleted and head is nullptr
        }
        
        // print - outputs all elements in the list from head to tail
        void print() {
            Node* current = head;  // Start current pointer at the head
            
            // Check if list is empty
            if (!current) {
                cout << "List is empty." << endl;  // Message for empty list
                return;  // Exit function
            }
            
            // Traverse the list from head to tail
            while (current) {
                cout << current->data << " ";  // Output the data in the current node
                current = current->next;       // Move current to the next node
            }
            cout << endl;  // Print newline after all elements
        }
    
        // print_reverse - outputs all elements in the list from tail to head
        void print_reverse() {
            Node* current = tail;  // Start current pointer at the tail
            
            // Check if list is empty
            if (!current) { 
                cout << "List is empty." << endl;  // Message for empty list
                return;  // Exit function
            }
            
            // Traverse the list from tail to head using prev pointers
            while (current) {
                cout << current->data << " ";  // Output the data in the current node
                current = current->prev;       // Move current to the previous node
            }
            cout << endl;  // Print newline after all elements
        }
        
        // every_other_element - outputs elements at positions 0, 2, 4, 6, etc. (skipping odd positions)
        void every_other_element() {
            Node* current = head;  // Start current pointer at the head (position 0)
            
            // Check if list is empty
            if (!current) {
                cout << "List is empty." << endl;  // Message for empty list
                return;  // Exit function
            }
            
            cout << "Every other element: ";  // Descriptive message
            
            // Traverse the list, outputting every other element
            while (current) {
                cout << current->data << " ";  // Output the data in the current node
                
                // Skip the next node by moving current two positions forward
                if (current->next)
                    current = current->next->next;  // Move to the node after next (skip one)
                else
                    current = nullptr;  // If there's no next->next, we're done
            }
            cout << endl;  // Print newline after all elements
        }
    };
    