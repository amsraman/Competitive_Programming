/*
ID: adityasund1
TASK: zerosum
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n;
string s, op = " +-";
vector<string> ans;

bool valid()
{
    int sum = 0, cur = 1;
    s+=".";
    char curop = '+';
    for(int i = 1; i<=n; i++)
    {
        if(s[i-1]==' ')
        {
            cur*=10;
            cur+=(i+1);
        }
        else
        {
            if(curop=='+')
            {
                sum+=cur;
            }
            if(curop=='-')
            {
                sum-=cur;
            }
            curop = s[i-1];
            cur = i+1;
        }
    }
    s = s.substr(0,s.length()-1);
    if(sum==0)
    {
        return true;
    }
    return false;
}
void gen(int a)
{
    if(a==n-1)
    {
        if(valid())
        {
            ans.push_back(s);
        }
        return;
    }
    for(int i = 0; i<3; i++)
    {
        s+=op.substr(i,1);
        gen(a+1);
        s=s.substr(0,s.length()-1);
    }
}

int main()
{
    ifstream infile("zerosum.in");
    ofstream outfile("zerosum.out");
    infile >> n;
    gen(0);
    for(int i = 0; i<ans.size(); i++)
    {
        outfile << 1;
        for(int j = 1; j<n; j++)
        {
            outfile << ans[i][j-1] << j+1;
        }
        outfile << endl;
    }
}
