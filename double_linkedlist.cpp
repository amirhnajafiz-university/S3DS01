#include <iostream>
#include <string>

using namespace std;

/**
 * Node is a single element to store the data
 * of a full calculator string.
 * 
 */
class Node
{
    public:
        string key;
        Node* next;
        Node* prev;
        Node(string key);
};
// Constructor
Node::Node(string newKey) 
{
    key = newKey;
    temp->next = NULL;
    temp->prev = NULL;
}

/**
 * A function for creating the node elements.
 * @newkey is the single char holder
 * 
 */
Node* create_node(string newkey)
{
    Node* temp = new Node(newkey);
    return temp;
}

// global pointers
Node* head;
Node* tail;
Node* cursor;

/**
 * This function sets the basics of our program.
 * 
 */
void init()
{
    // Using two sentinels for our data structure
    head = create_node(NULL);
    tail = create_node(NULL);
    // The program cursor starting from head
    cursor = head;
    head->next = tail;
    tail->prev = head;
}

/**
 * Setting everything back to its default.
 * 
 */
void reset()
{
    cursor = head;
    head->next = tail;
    tail->prev = head;
}


// **************** Insertion in linkedlist ****************
void insert_at_first(string newKey)
{
    Node* temp = create_node(newKey);
    temp->prev = head;
    temp->next = tail;
    tail->prev = temp;
    head->next = temp;
    cursor = temp;
}

void insert_at_head(string newKey)
{
    Node* temp = create_node(newKey);
    temp->next = head->next;
    temp->prev = head;
    temp->next->prev = temp;
    cursor = temp;
}

void insert_at_tail(string newKey)
{
    Node* temp = create_node(newKey);
    temp->prev = tail->prev;
    temp->next = tail;
    temp->prev->next = temp;
}

void insert_at_middle(string newKey)
{
    Node* temp = create_node(newKey);
    temp->next = cursor->next;
    temp->prev = cursor;
    cursor->next = temp;
    temp->next->prev = temp;
    cursor = temp;
}

void insert(string newKey)
{
    if (head->next == tail)
    {
        insert_at_first(newKey);
    } else if (cursor == head)
    {
        insert_at_head(newKey);
    } else if (cursor == tail)
    {
        insert_at_tail(newKey);
    } else
    {
        insert_at_middle(newKey);
    }
}
// **************** End Insertion in linkedlist ****************

// **************** Deletion in linkedlist ****************
void remove()
{
    if (cursor == head)
    {
        remove_from_head();
        return;
    }
    if (cursor == tail)
    {
        remove_from_tail();
        return;
    }
    cursor->next->prev = cursor->prev;
    cursor->prev->next = cursor->next;
    Node* temp1 = cursor;
    cursor = temp1->prev;
    delete temp1;
}
// **************** End Deletion in linkedlist ****************
void right_shift()
{
    if (cursor->next != NULL)
    {
        cursor = cursor->next;
    }
}

void left_shift()
{
    if(cursor->prev != NULL)
    {
        cursor = cursor->prev;
    }
}

// Prints the linked list objects
void print_list()
{
    Node* temp = head;
    if (head == NULL)
    {
        cout << "|" << endl;
        return;
    }
    while (temp != NULL)
    {
        cout << temp->key << " ";
        temp = temp->next;
        if (temp == cursor)
        cout << "| ";
    }
    cout << endl;
}

// A test case
int main() 
{
    insert('c');
    insert('c'); 
    insert('c'); 
    insert('c'); 
    insert('c'); 
    insert('c'); 
    print_list();
    left_shift();
    left_shift();
    remove(); 
    print_list();
    left_shift();
    remove(); 
    print_list();
    insert(2);
    print_list();
    return 0;
}