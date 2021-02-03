#include <bits/stdc++.h> 
#include <stack>
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std; 
 
// **************** Postfix evaluate ****************
bool digit(char c)  
{  
    if(c >= '0' && c <= '9')  
        return true;  
    return false;  
}  

int evaluatePostfix(string exp) 
{ 
	stack<int> S; 
	
	for (int i = 0; i < exp.length(); i++) 
	{ 
		if(exp[i] == ' ')
            continue; 
		else if ( digit(exp[i]) ) 
		{ 
			int num=0; 
			while( digit(exp[i]) ) 
			{ 
			    num = num * 10 + (int)(exp[i] - '0'); 
				i++; 
			} 
			i--; 
			S.push(num); 
		} else
		{ 
			int val1 = S.top(); 
            S.pop();
			int val2 = S.top(); 
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
// **************** End Postfix evaluate ****************

int main() 
{ 
	string exp = "12 44 +"; 
	cout << evaluatePostfix(exp); 
	return 0; 
} 
