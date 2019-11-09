/*
ID: adityasund1
TASK: heritage
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int ipos[26];
string in, pre;

string tree(int a, int b, int l)
{
    if(l==0)
    {
        return "";
    }
    if(l==1)
    {
        return pre.substr(a,1);
    }
    int ltl = ipos[pre[a]-'A']-a-b;
    return tree(a+1,b-1,ltl)+tree(a+1+ltl,b,l-ltl-1)+pre.substr(a,1);
}

int main()
{
    ifstream infile("heritage.in");
    ofstream outfile("heritage.out");
    infile >> in >> pre;
    for(int i = 0; i<pre.length(); i++)
    {
        ipos[in[i]-'A'] = i;
    }
    outfile << tree(0,0,in.length()) << endl;
}
