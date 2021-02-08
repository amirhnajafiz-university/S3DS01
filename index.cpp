/**
 * Data structures and Algorithm final project.
 * 
 * Sources that I used for this project :
 *  1. https://github.com/sinamna/DSA/blob/master/Data%20Structures/Lists/LinkedList/CPP/double_list.cpp => Double linked list
 *  2. https://runestone.academy/runestone/books/published/pythonds/BasicDS/InfixPrefixandPostfixExpressions.html => Basics of post-fix and in-fix
 *  3. https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/ => Convert in-fix to post-fix
 *  4. https://www.includehelp.com/c/evaluation-of-postfix-expressions-using-stack-with-c-program.aspx => Evaluation of in-fix
 * 
 * - I used a double linkedlist with two sentinels ( "head" & "tail" ) to store the strings.
 * - By using two methods , first I convert in-fix to post-fix, then I calculate the string.
 * - For cursor I used a pointer. If it is on the head then it will appear at beginnig of string, else if it s on tail it will appear at the end,
 *   else it would be appear after a pointing node value.
 * - Shifts are basically moving the pointer on the nodes.
 * - Our hash-table is open-addressing mode table.
 * - For hashing, since we are only gonna use 20 '!' orders, we create a memory of 20, and we hash the strings by their length , plus a probe
 *   that increases one by one.
 * 
 * Author : Amirhossein Najafizadeh
 * Student ID : 9831065
 * 
 */
#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stack>

using namespace std;


/**
 * Node is a single element to store the data
 * of a full calculator string.
 * Each node stores a single charecter.
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
 * @newkey is the single charecter
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
 * Like two sentinels and the cursor that points to head.
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
 * This function is for
 * setting everything back to its default.
 * 
 */
void reset()
{
    cursor = head;
    head->next = tail;
    tail->prev = head;
}

// **************** Data-Structure ****************
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
// **************** End Data-Structure ****************


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


// **************** Hash Table Implementing ****************
const int CAPACITY = 20;
class HashNode 
{ 
    public:
        int free; 
        long long int value; 
        string key; 
}; 

HashNode memory[CAPACITY];

/**
 * Sets the memory for program.
 * 
 */
void init_cache()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        memory[i].free = 1; // This flag is used to find the empty houses in memory ( 1 is free / 0 is full )
        memory[i].key = "NULL";
        memory[i].value = 0;
    }
}

long long int hash_function(string line)
{
    return line.length();
}

int key_generate(string line)
{
    long long int total_length = hash_function(line);
    int temp = 0;
    for (int i = 0; i < CAPACITY; i++)
    {
        temp = (int)(total_length + i) % CAPACITY;
        if (memory[temp].free == 1)
        {
            return temp;
        }
    }
    return -1;
}

/**
 * Stores a new value into hash-map.
 * 
 */
void cache_in(string line, long long int value)
{
    int index = key_generate(line);
    if (index == -1)
    {
        return;
    } else 
    {
        memory[index].key = line;
        memory[index].free = 0;
        memory[index].value = value;
    }
}

/**
 * Does a search in hash-map and returns the index if founded. ( -1 means not found )
 * 
 */
int cache_out(string line)
{
    long long int total_length = hash_function(line);
    int temp = 0;
    for (int i = 0; i < CAPACITY; i++)
    {
        temp = (int)(total_length + i) % CAPACITY;
        if (memory[temp].key == line)
        {
            return temp;
        }
    }
    return -1;
}
// **************** End Hash Table Implementing ****************

// **************** Infix to Postfix ****************
bool IsOperator(char c)  
{  
    if(c == '+' || c == '-' || c == '*')  
        return true;     
    return false;  
}  
    
bool IsOperand(char c)  
{  
    if(c >= '0' && c <= '9')  
        return true;  
    return false;  
}  

int precedence(char op)  
{  
    if(op == '+' || op == '-')                  
        return 1;  
    if (op == '*')  
        return 2;
    return 0;     
} 

bool eqlOrhigher(char op1, char op2)  
{  
    return precedence(op1) >= precedence(op2) ? true : false;  
}  
    
string convert(string infix)  
{  
    stack <char> S;  
    string postfix ="", temp = "";    
    char ch;  
    
    S.push( '(' );  
    infix += ')';  
    
    for(long long int i = 0; i < infix.length(); i++)  
    {  
        ch = infix[i];  
        if(ch == ' ') 
        { 
            postfix += temp + " ";
            temp = "";
            continue;  
        }
        else if (ch == '(')
        {  
            postfix += temp + " ";
            temp = "";
            S.push(ch); 
        } 
        else if ( IsOperand(ch) ) 
        { 
            temp += ch;  
        }    
        else if ( IsOperator(ch) )  
        {  
            postfix += temp + " ";
            temp = "";
            while( !S.empty() && eqlOrhigher(S.top(), ch) )  
            {  
                postfix += S.top();  
                S.pop();  
            }  
            S.push(ch);  
        }  
        else if(ch == ')')  
        {  
            postfix += temp + " ";
            temp = "";
            while( !S.empty() && S.top() != '(' )  
            {  
                postfix += S.top();  
                S.pop();  
            }  
            S.pop();  
        }  
    }  
    return postfix;  
}  
// **************** End Infix to Postfix ****************

// **************** Postfix evaluate ****************
const long long int LIMIT = 1000000007;
long long int evaluatePostfix(string exp) 
{ 
	stack<long long int> S; 
	
	for (long long int i = 0; i < exp.length(); i++) 
	{ 
		if(exp[i] == ' ')
            continue; 
		else if ( IsOperand(exp[i]) ) 
		{ 
			long long int num=0; 
			while( IsOperand(exp[i]) ) 
			{ 
			    num = ( num * 10 + (long long int)(exp[i] - '0') ) % LIMIT; 
				i++; 
			} 
			i--; 
			S.push(num); 
		} else
		{ 
			long long int val1 = S.top(); 
            S.pop();
			long long int val2 = S.top(); 
            S.pop();
			switch (exp[i]) 
			{ 
                case '+': S.push((val2 + val1) % LIMIT); break; 
                case '-': S.push((val2 - val1) % LIMIT); break; 
                case '*': S.push((val2 * val1) % LIMIT); break; 
			} 
		} 
	} 
	return S.top(); 
} 

long long int evaulate()
{
    Node* temp = head->next;

    string full_s = "";
    while (temp != tail)
    {
        full_s += temp->key;
        temp = temp->next;
    }
    full_s = convert(full_s);

    int index_result = cache_out(full_s);
    long long int result;
    if (index_result == -1)
    {
        result = evaluatePostfix(full_s);
        if ( result < 0)
        {
            result += LIMIT;
        }
        cache_in(full_s, result);
    } else 
    {
        result = memory[index_result].value;
    }

    return result;
}
// **************** End Postfix evaluate ****************

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

/**
 * Program main function to get the data from console.
 * 
 */
void get_input()
{
    int orders;
    cin >> orders;

    string start;
    cin >> start;

    char chars[start.length() + 1];
    strcpy(chars, start.c_str());
    for (long i = 0; i < start.length(); i++)
    {
        insert(start[i]);
    }

    cursor = head;
    
    string input;
    for (long i = 0; i < orders; i++)
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
            if (head->next == tail)
            {
                continue;
            }
            cout << evaulate() << endl;
        }
    }
}
// **************** End Input Output ****************

// **************** Main ****************
int main() 
{
    init();
    init_cache();
    get_input();
    return 0;
}
// **************** End Main ****************