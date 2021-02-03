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
    next = NULL;
    prev = NULL;
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
    head = create_node("NULL");
    tail = create_node("NULL");
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
void remove_from_end()
{
    Node* temp = tail->prev;
    tail->prev = temp->prev;
    tail->prev->next = tail;
    delete temp;
}

void remove_from_middle()
{
    Node* temp = cursor;
    temp->prev->next = cursor->next;
    temp->next->prev = cursor->prev;
    cursor = temp->prev;
    delete temp;
}

void remove()
{
    if (head->next == tail || cursor == head)
    {
        return;
    } else if (cursor == tail)
    {
        remove_from_end();
    } else 
    {
        remove_from_middle();
    }
    if (head->next == tail)
    {
        reset();
    }
}
// **************** End Deletion in linkedlist ****************

// **************** Cursor shifts ****************
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
// **************** End Cursor shifts ****************

void print_list()
{
    if (head == cursor)
    {
        cout << "|";
    }
    Node* temp = head->next;
    while (temp != tail)
    {
        cout << temp->key;
        if (temp == cursor)
            cout << "|";
        temp = temp->next;
    }
    if (tail == cursor)
    {
        cout << "|";
    }
    cout << endl;
}

// A test case
int main() 
{
    init();
    print_list(); // |
    insert("5"); // 5|
    print_list();
    insert("+"); // 5+|
    print_list();
    insert("2"); // 5+2|
    print_list();
    insert("*"); // 5+2*|
    print_list();
    remove(); // 5+2|
    print_list();
    remove(); // 5+|
    print_list();
    remove(); // 5|
    print_list();
    remove(); // |
    print_list();
    remove(); // |
    print_list();
    return 0;
}