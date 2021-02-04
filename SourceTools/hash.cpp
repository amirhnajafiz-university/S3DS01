#include <bits/stdc++.h> 
#include <string>

using namespace std; 
const int CAPACITY = 20;

class HashNode 
{ 
    public:
        int free; 
        int value; 
        string key; 
}; 


HashNode memory[CAPACITY];


void init()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        memory[i].free = 1;
        memory[i].key = "NULL";
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

void insert(string line)
{
    int index = key_generate(line);
    if (index == -1)
    {
        return;
    } else 
    {
        memory[index].key = line;
        memory[index].free = 0;
        memory[index].value = 1;
    }
}

void print()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        if (memory[i].free == 1)
        {
            cout << " __ ";
        } else
        {
            cout << " " << memory[i].key << " "; 
        }
        if (i == CAPACITY / 2)
        {
            cout << endl;
        }
    }
    cout << endl;
}

int main()
{
    init();
    insert("12+3");
    print();
    insert("12+32");
    insert("1");
    insert("12+25244****3");
    insert("11+12+252443");
    insert("12+341643");
    insert("12+252443");
    insert("12+2524425^463");
    insert("12+252443");
    insert("12+252444444444444444444443");
    insert("12+252443");
    insert("12+24452443");
    insert("12+252452443");
    insert("12+252443");
    insert("12+252443");
    insert("12+25442443");
    insert("12+25");
    insert("12+2524432352");
    insert("12+252###443");
    insert("12+2522443");
    print();
    return 0;
}
  
