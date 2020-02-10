/*
ID: adisund1
LANG: C++
TASK: barn1
*/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int m, s, c, ans;
    ifstream infile("barn1.in");
    ofstream outfile("barn1.out");
    infile >> m >> s >> c;
    int inp[c], diff[c-1], temp;
    infile >> inp[0];
    for(int i = 1; i<c; i++)
    {
        infile >> inp[i];
    }
    for(int i = 0; i<c; i++)
    {
        for(int j = i+1; j<c; j++)
        {
            if(inp[j]<inp[i])
            {
                temp = inp[i];
                inp[i] = inp[j];
                inp[j] = temp;
            }
        }
    }
    for(int i = 1; i<c; i++)
    {
        diff[i-1] = inp[i]-inp[i-1];
    }
    ans = inp[c-1]-inp[0]+1;
    for(int i = 0; i<c-1; i++)
    {
        for(int j = i+1; j<c-1; j++)
        {
            if(diff[j]<diff[i])
            {
                temp = diff[j];
                diff[j] = diff[i];
                diff[i] = temp;
            }
        }
    }
    for(int i = 0; i<m-1; i++)
    {
        ans = ans-diff[c-2-i]+1;
    }
    if(m>=c)
    {
        ans = c;
    }
    outfile << ans << endl;
}
