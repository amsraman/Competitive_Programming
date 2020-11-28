#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int a;
string z;
vector<string> in;

int toint(string s)
{
    int sign = 1, ret = 0;
    for(int i = 0; i<s.size(); i++)
    {
        if(s[i]=='-') sign = -1;
        else ret = ret*10+(s[i]-'0');
    }
    return ret*sign;
}

int f()
{
    a++;
    if(in[a-1]=="+")
    {
        int x = f(), y = f();
        return x+y;
    }
    else if(in[a-1]=="-")
    {
        int x = f(), y = f();
        return x-y;
    }
    else if(in[a-1]=="*")
    {
        int x = f(), y = f();
        return x*y;
    }
    else if(in[a-1]=="@")
    {
        int x = f(), y = f(), z = f();
        return ((x>0)?(y):(z));
    }
    else if(in[a-1]==">")
    {
        int x = f(), y = f(), z = f();
        return max(max(x,y),z);
    }
    else if(in[a-1]=="|")
    {
        int x = f();
        return ((x>0)?(x):(-x));
    }
    else
    {
        return toint(in[a-1]);
    }
}

int main()
{
    ifstream fin("sr4.txt");
    for(int i = 0; i<5; i++)
    {
        while(fin.good())
        {
            fin >> z;
            in.push_back(z);
        }
        cout << f() << endl;
    }
}
