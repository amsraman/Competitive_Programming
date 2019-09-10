/*
ID: adityasund1
TASK: milk4
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int q, p, in[100], cur[101];
bool done, v[50001];

bool check(int a)
{
    v[0] = true;
    for(int i = 1; i<=q; i++)
    {
        v[i] = false;
    }
    for(int i = 0; i<=q-cur[a-1]; i++)
    {
        for(int j = 0; j<a; j++)
        {
            if(v[i])
            {
                v[i+cur[j]] = true;
                if(v[q])
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void dfs(int a, int b, int c)
{
    if(a==c)
    {
        if(check(c))
        {
            done = true;
        }
        return;
    }
    for(int i = b; i<p; i++)
    {
        cur[a] = in[i];
        dfs(a+1,i+1,c);
        if(done)
        {
            break;
        }
    }
}

int main()
{
    ifstream infile("milk4.in");
    ofstream outfile("milk4.out");
    infile >> q >> p;
    for(int i = 0; i<p; i++)
    {
        infile >> in[i];
    }
    sort(in,in+p);
    for(int i = 1; i<=p; i++)
    {
        dfs(0,0,i);
        if(done)
        {
            outfile << i;
            for(int j = 0; j<i; j++)
            {
                outfile << " " << cur[j];
            }
            outfile << endl;
            break;
        }
    }
}
