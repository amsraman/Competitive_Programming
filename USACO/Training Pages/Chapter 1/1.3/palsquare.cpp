/*
ID: adisund1
LANG: C++
TASK: palsquare
*/
#include <fstream>
#include <iostream>

using namespace std;

int exp(int a, int b)
{
    int ret = 1;
    for(int i = 0; i<b; i++)
    {
        ret = ret*a;
    }
    return ret;
}

string base(int a, int b)
{
    string num = "0123456789ABCDEFGHIJK";
    string ret;
    int c;
    int log = 0;
    while(exp(b,log)<a)
    {
        log++;
    }
    if(exp(b,log)!=a)
    {
        log--;
    }
    for(int i = log; i>=0; i--)
    {
        c = a/exp(b,i);
        ret = ret+num[c];
        a = a-c*exp(b,i);
    }
    return ret;
}

int check(string a)
{
    for(int i = 0; i<a.length(); i++)
    {
        if(a[i]!=a[a.length()-1-i])
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int n;
    string b;
    ifstream infile("palsquare.in");
    ofstream outfile("palsquare.out");
    infile >> n;
    for(int i = 1; i<=300; i++)
    {
        b = base(i*i,n);
        if(check(b)==1)
        {
            outfile << base(i,n) << " " << base(i*i,n) << endl;
        }
    }
    return 0;
}
