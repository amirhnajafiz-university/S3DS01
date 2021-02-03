#include <iostream>  
#include <stack>  

using namespace std;  

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
    
int main()  
{  
    string infix_expression, postfix_expression;  
    int ch;  
    do  
    {  
        cout << " Enter an infix expression: ";  
        cin >> infix_expression;  
        postfix_expression = convert(infix_expression);  
        cout << "\n Your Infix expression is: " << infix_expression;  
        cout << "\n Postfix expression is: " << postfix_expression;  
        cout << "\n \t Do you want to enter infix expression (1/ 0)?";  
        cin >> ch;  
    } while(ch == 1);  
    return 0;  
}  