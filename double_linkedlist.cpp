#include <iostream>

using namespace std;


class Node
{
    public:
        char key;
        Node* next;
        Node* prev;
        Node(int key);
};

Node::Node(char newKey) 
{
    key = newKey;
}


// Head address as a global variable
Node* head = NULL;
Node* tail = NULL;
Node* cursor = NULL;


// Methods of list :
// Create a node in memory and return the address
Node* create_node(char newkey)
{
    Node* temp = new Node(newkey);
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}


// Inserts a new node at the head
void insert_at_head(char newKey)
{
    Node* temp = create_node(newKey);
    if (head == NULL)
    {
        head = temp;
        tail = temp;
        return;
    }
    temp->next = head;
    temp->next->prev = temp;
    head = temp;
    temp->prev = NULL;
    return;
}
// Adds a new node at tail
void insert_at_tail(char newKey)
{
    Node* temp = create_node(newKey);
    if (tail == NULL)
    {
        tail = temp;
        head = temp;
        return;
    }
    temp->prev = tail;
    temp->prev->next = temp;
    tail = temp;
    temp->next = NULL;
    return;
}

// Removes the node at the head
void remove_from_head()
{
    Node* temp = head;
    head = temp->next;
    head->prev = NULL;
    delete temp;
}
// Deletes the node at the tail
void remove_from_tail()
{
    Node* temp = tail;
    tail = temp->prev;
    tail->next = NULL;
    delete temp;
}

// Adds a new node anywhere in the list
void insert(char newKey)
{
    Node* temp = cursor;
    if (cursor == head)
    {
        insert_at_head(newKey);
        return;
    }
    if (cursor == tail)
    {
        insert_at_tail(newKey);
        return;
    }
    Node* newNode = create_node(newKey);
    newNode->next = temp->next;
    temp->next->prev = newNode;
    newNode->prev = temp;
    temp->next = newNode;
    return;
}

// Removes a node at any given place from the list
void remove()
{
    Node* temp = cursor;
    if (temp == head)
    {
        remove_from_head();
        return;
    }
    if (temp == tail)
    {
        remove_from_tail();
        return;
    }
    Node* temp1 = temp->next;
    temp->next = temp1->next;
    temp->next->prev = temp;
    delete temp1;
}

// Prints the linked list objects
void print_list()
{
    Node* temp = head;
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
    insert(2);
    insert(20); 
    insert(23); 
    insert(7); 
    insert(4); 
    insert(10); 
    print_list();
    remove(); 
    print_list();
    remove(); 
    print_list();
    insert(2);
    print_list();
    return 0;
}