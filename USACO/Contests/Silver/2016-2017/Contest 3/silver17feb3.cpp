#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n;
bool v[100][100] = {false};
bool c[100][100] = {false};
bool u[100][100] = {false};
bool e[100][100] = {false};
vector<int> rc;

void dfs(int a, int b, int &r)
{
    if(v[a][b])
    {
        return;
    }
    v[a][b] = true;
    if(c[a][b])
    {
        r++;
    }
    if(a>0)
    {
        if(!u[a-1][b])
        {
            dfs(a-1,b,r);
        }
    }
    if(a<n-1)
    {
        if(!u[a][b])
        {
            dfs(a+1,b,r);
        }
    }
    if(b>0)
    {
        if(!e[a][b-1])
        {
            dfs(a,b-1,r);
        }
    }
    if(b<n-1)
    {
        if(!e[a][b])
        {
            dfs(a,b+1,r);
        }
    }
}

int main()
{
    int r, k;
    int t1, t2, t3, t4;
    ifstream infile("countcross.in");
    ofstream outfile("countcross.out");
    infile >> n >> k >> r;
    for(int i = 0; i<r; i++)
    {
        infile >> t1 >> t2 >> t3 >> t4;
        if(t1==t3)
        {
            e[t1-1][min(t2,t4)-1] = true;
        }
        else
        {
            u[min(t1,t3)-1][t2-1] = true;
        }
    }
    for(int i = 0; i<k; i++)
    {
        infile >> t1 >> t2;
        c[t1-1][t2-1] = true;
    }
    int rcount = 0;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(!v[i][j])
            {
                int z = 0;
                dfs(i,j,z);
                rc.push_back(z);
                rcount++;
            }
        }
    }
    int ans = 0;
    for(int i = 0; i<rc.size(); i++)
    {
        for(int j = i+1; j<rc.size(); j++)
        {
            ans = ans + rc[i]*rc[j];
        }
    }
    outfile << ans << endl;
}
