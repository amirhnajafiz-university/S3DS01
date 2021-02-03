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

void insert(char newKey)
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

// **************** Input / Output ****************
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

void get_input()
{
    int orders;
    cin >> orders;

    string start;
    cin >> start;

    char chars[start.length() + 1];
    strcpy(chars, start.c_str());
    for (int i = 0; i < start.length(); i++)
    {
        insert(start[i]);
    }

    cursor = head;
    
    string input;
    for (int i = 0; i < orders; i++)
    {
        getline(cin, input); 
        if (input == ">")
        {
            right_shift();
        } else if (input == "<")
        {
            left_shift();
        } else if (input == "-")
        {
            remove();
        } else if ( input.rfind("+", 0) == 0 )
        {
            insert(input[2]);
        } else if (input == "?")
        {
            print_list();
        } else if (input == "!")
        {
            cout << "Eval" << endl;
        }
    }
}
// **************** End Input Output ****************

// A test case
int main() 
{
    init();
    get_input();
    return 0;
}