#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;
const int MAX = 4096;
string stack[MAX];
int tos = 0; 

void push(int i) { 
    if (tos >= MAX) {
        printf("Стек полон\n");
        return;
    } 
    stack[tos] = i;
    tos++;
}
string pop(void) {

    stack[tos-1] = "";
    tos--;  
    if (tos < 0) {
        printf("Стек пуст\n"); return 0;
    } 
    return stack[tos];
}
int priority(string s) {
    char symbols[2][4]{ { '(', ')', '+', '*'} ,{'_', '_', '-', '/'} };
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            if (s[0] == symbols[i][j] && isdigit(s[0]) == false)
            {
                return j;
            }

        }

    }


}
void in_file(string str)
{
    fstream in;
    in.open("out.txt");
    if (in.is_open())
    {
        in << str;
    }
    in.close();
}
void opz(string str2[], int size) {
    
    int* flag = new int[size];
    for (size_t i = 0; i < size; i++)
    {
        flag[i] = 0;
    }
    string out = "";
    for (size_t i = 0; i < size; i++)
    {
        if (i == size - 1)
        {
            while (tos)
            {
                out += (stack[tos - 1] != "(" && stack[tos - 1] != ")") ? stack[tos - 1] : "";
                pop();
            }
            continue;
        }
        if (isdigit(str2[i][0]) || str2[i] == "")
        {
            out += str2[i];
        }
        
        

        if (!isdigit(str2[i][0]) && tos == 0)
        {
            push(str2[i][0]);
            continue;
        }
        
        if (str2[i][0] == '(')
        {
            push(str2[i][0]);
            continue;
        }
        if (str2[i][0] == ')')
        {
            while (stack[tos-1] != "(" && tos > 0)
            { 
                out += stack[tos] != "(" || stack[tos] != ")" ? stack[tos - 1] : "";
                pop();
                if (stack[tos - 1] == "(")
                {
                    stack[tos - 1] = "";
                    tos--;
                    break;
                }
            }
            continue;
        }

        if (!isdigit(str2[i][0]) && str2[i] != "")
        {
            if ((priority(str2[i]) <= priority(stack[tos - 1])) && tos > 0)
            {
                while (priority(str2[i]) <= priority(stack[tos - 1]) && tos > 0)
                {
                    out += stack[tos - 1];
                    pop();
                }
                push(str2[i][0]);
                continue;
            }
            else
            {
                push(str2[i][0]);
                continue;
            }

        }


        
    }
    in_file(out);
    cout << out;

}
string open_f()
{
    ifstream fin;
    fin.open("input.txt", ios_base::in);
    string tempstr = "";
    if (fin.is_open())
    {
        getline(fin, tempstr);
        fin.close();
        return tempstr;
    }
    else
    {
        fin.close();
        while (1)
        {
            cout << "File 'Input.txt' was not opened!\n";
            system("pause");
        }
    }
}
int main()
{
    setlocale(LC_ALL, "rus");
    string str1 = open_f();
    string* arr = new string[str1.size()];
    string temp = "";

    for (int i = 0; i < str1.size(); i++)
    {
        if (isdigit(str1[i]) && isdigit(str1[i + 1]))
        {
            temp += str1[i];
            continue;
        }
        else
        {
            temp += str1[i];
        }
        arr[i] = temp;
        temp = "";
    }
    for (size_t i = 0; i < MAX; i++)
    {
        stack[i] = "";
    }
    opz(arr, str1.size());

}

