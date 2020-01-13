/*
ID: adityasund1
TASK: stall4
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;

int n, m, edge[402][402], path[402];
vector<int> g[402];

bool bfs()
{
    queue<int> q;
    for(int i = 1; i<=n+m+1; i++)
    {
        path[i] = -1;
    }
    path[0] = -2;
    q.push(0);
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        for(int i = 0; i<g[x].size(); i++)
        {
            if((edge[x][g[x][i]]!=0)&&(path[g[x][i]]==-1))
            {
                path[g[x][i]] = x;
                q.push(g[x][i]);
            }
        }
    }
    return (path[n+m+1]!=-1);
}

int main()
{
    ifstream infile("stall4.in");
    ofstream outfile("stall4.out");
    int s, a, ans = 0;
    infile >> n >> m;
    for(int i = 1; i<=n; i++)
    {
        infile >> s;
        edge[0][i] = 1;
        g[0].push_back(i);
        for(int j = 0; j<s; j++)
        {
            infile >> a;
            g[i].push_back(n+a);
            g[n+a].push_back(i);
            edge[i][n+a] = 1;
        }
    }
    for(int i = n+1; i<n+m+1; i++)
    {
        g[i].push_back(n+m+1);
        edge[i][n+m+1] = 1;
    }
    while(bfs())
    {
        int curn = n+m+1;
        while(path[curn]!=-2)
        {
            edge[path[curn]][curn]--;
            edge[curn][path[curn]]++;
            curn = path[curn];
        }
        ans++;
    }
    outfile << ans << endl;
}
