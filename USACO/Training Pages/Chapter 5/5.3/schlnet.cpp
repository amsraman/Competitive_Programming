/*
ID: adityasund1
TASK: schlnet
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n, d, cd, cnt;
vector<int> g[100], g2[100];
bool va[100], va1[100], va2[100], v[100][100], cc = true;

void dfs1(int x)
{
    va[x] = va2[x] = true;
    for(int i = 0; i<g[x].size(); i++)
    {
        if(!va2[g[x][i]]){dfs1(g[x][i]);}
    }
}

void dfs2(int x)
{
    va1[x] = va2[x] = true;
    for(int i = 0; i<g2[x].size(); i++)
    {
        if(!va2[g2[x][i]]){dfs2(g2[x][i]);}
    }
}

void dfs3(int x, int y)
{
    v[x][y] = true;
    cnt++;
    for(int i = 0; i<g[x].size(); i++)
    {
        if(!v[g[x][i]][y])
        {
            dfs3(g[x][i],y);
        }
    }
}

int main()
{
    ifstream infile("schlnet.in");
    ofstream outfile("schlnet.out");
    infile >> n;
    int t;
    for(int i = 0; i<n; i++)
    {
        infile >> t;
        while(t!=0)
        {
            g[i].push_back(t-1);
            g2[t-1].push_back(i);
            infile >> t;
        }
    }
    for(int i = 0; i<n; i++)
    {
        if(!va[i])
        {
            for(int i = 0; i<n; i++){va2[i] = false;}
            dfs1(i);
            va[i] = false;
        }
        if(!va1[i])
        {
            for(int i = 0; i<n; i++){va2[i] = false;}
            dfs2(i);
            va1[i] = false;
        }
    }
    for(int i = 0; i<n; i++)
    {
        if(!va[i]){d++;}
        if(!va1[i]){cd++;}
        cnt = 0;
        dfs3(i,i);
        if(cnt!=n){cc = false;}
    }
    if(cc)
    {
        outfile << 1 << endl << 0 << endl;
        return 0;
    }
    outfile << d << endl << max(d,cd) << endl;
}
