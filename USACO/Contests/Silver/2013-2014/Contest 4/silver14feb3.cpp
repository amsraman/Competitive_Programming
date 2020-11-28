#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int mod = 2014;
map<string,int> m;
map<string,bool> b;

int solve(string s)
{
    int ret = 1;
    if(s.length()==1)
    {
        return 1;
    }
    if(b[s])
    {
        return m[s];
    }
    for(int i = (1+(s.length())/2); i<s.length(); i++)
    {
        if(s.substr(0,s.length()-i)==s.substr(i,s.length()-i))
        {
            ret+=solve(s.substr(0,i));
            ret%=mod;
        }
        if(s.substr(2*i-s.length(),s.length()-i)==s.substr(i,s.length()-i))
        {
            ret+=solve(s.substr(0,i));
            ret%=mod;
        }
    }
    for(int i = (s.length()-1)/2; i>0; i--)
    {
        if(s.substr(0,i)==s.substr(i,i))
        {
            ret+=solve(s.substr(i,s.length()-i));
            ret%=mod;
        }
        if(s.substr(0,i)==s.substr(s.length()-i,i))
        {
            ret+=solve(s.substr(i,s.length()-i));
            ret%=mod;
        }
    }
    return ret%mod;
}

int main()
{
    ifstream infile("scode.in");
    ofstream outfile("scode.out");
    string in;
    infile >> in;
    for(int i = 1; i<=in.length(); i++)
    {
        for(int j = 0; j<=in.length()-i; j++)
        {
            m[in.substr(j,i)] = solve(in.substr(j,i));
            b[in.substr(j,i)] = true;
        }
    }
    outfile << m[in]-1 << endl;
}
