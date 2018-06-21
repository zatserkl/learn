// Andriy Zatserklyaniy, zatserkl@gmail.com, Jun 21, 2018

#include <iostream>

using std::cout;    using std::endl;

typedef int data_type;

typedef struct Node {
    data_type data;
    Node *next;
    Node(data_type value) {
        data = value;
    }
} Node;

void printList(const Node* head) {
    while (head) {
        cout<< head->data <<endl;
        head = head->next;
    }
}

///////////////////////
//
// iterative solutions
//
///////////////////////

/**
  * declaration
  *
  * void invertList(Node& *head)    // head is a pointer to reference of Node
  *
  * causes compiler error message:
  *
  * linked_list_invert.cpp:28:23: error: 'head' declared as a pointer to a reference of type 'Node &'
  */
void invertList_CPP(Node* &head)    // head is a reference of pointer to Node
{
    Node* curr = head;              // current node
    Node* prev = 0;                 // previous node
    while (curr)
    {
        head = curr;                // update head

        Node* next = curr->next;    // remember a pointer to the next node
        curr->next = prev;          // curr->next is now points back

        prev = curr;
        curr = next;
    }
}

void invertList_C(Node** head)
{
    Node* curr = *head;
    Node* prev = 0;
    while (curr)
    {
        *head = curr;               // update pointer to the head node

        Node* next = curr->next;    // remember pointer to the next node
        curr->next = prev;          // point back

        prev = curr;
        curr = next;
    }
}

void invertList_C_BAD(Node* head)   // pointer to head (NOT pointer to pointer)
{
    // Here head is a local copy of the head in calling routine.
    // If you change head, it will not be changed in calling routine.

    Node* curr = head;
    Node* prev = 0;
    while (curr)
    {
        head = curr;                // update pointer to the head node
                                    // BUT head is a LOCAL variable,
                                    // a copy of the head in calling routine

        Node* next = curr->next;    // remember pointer to the next node
        curr->next = prev;          // point back

        prev = curr;
        curr = next;
    }

    // The links will be inverted,
    // but head will still be looking at the same node (with value 40)...
}

////////////////////////
//
// recursive solutions
//
////////////////////////

void invertList_CPP_recursive(Node* &head)  // head is a reference of pointer to Node
{
    // Separate list to head node and the rest of the list
    // Make a recursive call to reverse the rest of the list. Then add
    // to the reversed list the head node. Point the tail node to 0.
    // Set head to head of the rest.

    // terminate recursion
    if (!head) return;              // sanity check
    if (!head->next) return;        // nothing to do: just a single node

    Node* head_rest = head->next;
    invertList_CPP_recursive(head_rest);

    // add head to the tail node (it's head->next) of the rest of the list
    head->next->next = head;
    head->next = 0;         // terminate the list

    head = head_rest;
}

void invertList_C_recursive(Node** head)
{
    // Separate list to head node and the rest of the list
    // Make a recursive call to reverse the rest of the list. Then add
    // to the reversed list the head node with null next pointer.
    // Set head to head of the inverted rest of the list.

    // terminate recursion
    if (!(*head)) return;           // sanity check
    if (!(*head)->next) return;     // nothing to do: just a single node

    Node* head_rest = (*head)->next;
    invertList_C_recursive(&head_rest);

    // add *head to the tail node (it's (*head)->next) of the rest of the list
    (*head)->next->next = *head;

    // terminate the list
    (*head)->next = 0;

    // set head_rest as a new head
    *head = head_rest;
}

/////////
//
// main
//
/////////

int main()
{
    Node *head = 0;

    Node *node = new Node(10);
    node->next = head;          // add to head of the list, next is old head
    head = node;                // now head is pointed to the new node

    cout<< "initial tail = " << head <<endl;

    node = new Node(20);
    node->next = head;
    head = node;
    node = new Node(30);
    node->next = head;
    head = node;
    node = new Node(40);
    node->next = head;
    head = node;

    cout<< "initial head = " << head <<endl;

    // invertList_CPP(head);            // pass by reference to pointer
    // invertList_C(&head);             // pass by pointer to pointer

    // invertList_C_BAD(head);          // should not work: pass by pointer

    invertList_CPP_recursive(head);  // pass by reference to pointer
    // invertList_C_recursive(&head);      // pass by pointer to pointer

    cout<< "final head   = " << head <<endl;

    printList(head);
}
