#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stack>

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

void init_cache()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        memory[i].free = 1;
        memory[i].key = "NULL";
        memory[i].value = 0;
    }
}

int hash_function(string line)
{
    return line.length();
}

int key_generate(string line)
{
    int total_length = hash_function(line);
    int temp = 0;
    for (int i = 0; i < CAPACITY; i++)
    {
        temp = (total_length + i) % CAPACITY;
        if (memory[temp].free == 1)
        {
            return temp;
        }
    }
    return -1;
}

void cache_in(string line, long long int evaulate)
{
    int index = key_generate(line);
    if (index == -1)
    {
        return;
    } else 
    {
        memory[index].key = line;
        memory[index].free = 0;
        memory[index].value = evaulate;
    }
}

int cache_out(string line)
{
    int total_length = hash_function(line);
    int temp = 0;
    for (int i = 0; i < CAPACITY; i++)
    {
        temp = (total_length + i) % CAPACITY;
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
    
    for(int i = 0; i < infix.length(); i++)  
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
const long long int LIMIT = 1000000000 + 7;
long long int evaluatePostfix(string exp) 
{ 
	stack<long long int> S; 
	
	for (long i = 0; i < exp.length(); i++) 
	{ 
		if(exp[i] == ' ')
            continue; 
		else if ( IsOperand(exp[i]) ) 
		{ 
			long long int num=0; 
			while( IsOperand(exp[i]) ) 
			{ 
			    num = num * 10 + (long long int)(exp[i] - '0'); 
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
                case '+': S.push(val2 + val1);break; 
                case '-': S.push(val2 - val1); break; 
                case '*': S.push(val2 * val1); break; 
                case '/': S.push(val2 / val1); break; 
			} 
		} 
	} 
	return S.top(); 
} 

long evaulate()
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
        result = evaluatePostfix(full_s) % (LIMIT);
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