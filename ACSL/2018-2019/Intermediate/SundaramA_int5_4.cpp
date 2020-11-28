#include <fstream>
#include <iostream>

using namespace std;

int a;
char z;
string in;

int f()
{
    a++;
    if(in[a-1]=='+')
    {
        int x = f(), y = f();
        return x+y;
    }
    else if(in[a-1]=='-')
    {
        int x = f(), y = f();
        return x-y;
    }
    else if(in[a-1]=='*')
    {
        int x = f(), y = f();
        return x*y;
    }
    else if(in[a-1]=='@')
    {
        int x = f(), y = f(), z = f();
        return ((x>0)?(y):(z));
    }
    else if(in[a-1]=='>')
    {
        int x = f(), y = f(), z = f();
        return max(max(x,y),z);
    }
    else
    {
        return (in[a-1]-'0');
    }
}

int main()
{
    ifstream fin("int4.txt");
    for(int i = 0; i<5; i++)
    {
        while(fin.good())
        {
            fin >> z;
            in+=z;
        }
        cout << f() << endl;
    }
}
