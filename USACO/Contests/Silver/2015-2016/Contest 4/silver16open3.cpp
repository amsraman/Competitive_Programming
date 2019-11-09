#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n, m, co, start;
vector<int> g[3000];
bool v[3000], closed[3000];

void dfs(int a)
{
    v[a] = true;
    co++;
    for(int i = 0; i<g[a].size(); i++)
    {
        if((!v[g[a][i]])&&(!closed[g[a][i]]))
        {
            dfs(g[a][i]);
        }
    }
}

int main()
{
    ifstream infile("closing.in");
    ofstream outfile("closing.out");
    infile >> n >> m;
    int a, b;
    for(int i = 0; i<m; i++)
    {
        infile >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    co = 0;
    dfs(0);
    if(co==n)
    {
        outfile << "YES" << endl;
    }
    else
    {
        outfile << "NO" << endl;
    }
    for(int i = 0; i<n; i++)
    {
        infile >> a;
        closed[a-1] = true;
        start = 3001;
        for(int i = 0; i<n; i++)
        {
            v[i] = false;
            if(!closed[i])
            {
                start = i;
            }
        }
        co = 0;
        dfs(start);
        if((co==n-1-i)&&(i<n-1))
        {
            outfile << "YES" << endl;
        }
        else if(i<n-1)
        {
            outfile << "NO" << endl;
        }
    }
}
