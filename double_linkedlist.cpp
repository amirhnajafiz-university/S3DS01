#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;


/**
 * Node is a single element to store the data
 * of a full calculator string.
 * 
 */
class Node
{
    public:
        char key;
        Node* next;
        Node* prev;
        Node(char key);
};
// Constructor
Node::Node(char newKey) 
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
Node* create_node(char newkey)
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
    head = create_node('N');
    tail = create_node('N');
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
void insert_at_first(char newKey)
{
    Node* temp = create_node(newKey);
    temp->prev = head;
    temp->next = tail;
    tail->prev = temp;
    head->next = temp;
    cursor = temp;
}

void insert_at_head(char newKey)
{
    Node* temp = create_node(newKey);
    temp->next = head->next;
    temp->prev = head;
    temp->next->prev = temp;
    head->next = temp;
    cursor = temp;
}

void insert_at_tail(char newKey)
{
    Node* temp = create_node(newKey);
    temp->prev = tail->prev;
    temp->next = tail;
    temp->prev->next = temp;
    tail->prev = temp;
}

void insert_at_middle(char newKey)
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
    char chars[newKey.length() + 1];
    strcpy(chars, newKey.c_str());
    for(int i = 0; i < newKey.length(); i++)
    {
        char c = chars[i];
        if (head->next == tail)
        {
            insert_at_first(c);
        } else if (cursor == head)
        {
            insert_at_head(c);
        } else if (cursor == tail)
        {
            insert_at_tail(c);
        } else
        {
            insert_at_middle(c);
        }
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
    if (cursor == tail)
    {
        cursor = tail->prev;
    }
    if (cursor->prev != NULL)
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
    return 0;
}