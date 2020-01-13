/*
ID: adityasund1
TASK: ditch
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;

vector<int> g[200];
int n, m, edge[200][200], path[200], maxflow = 0;

bool bfs()
{
    path[0] = -2;
    for(int i = 1; i<m; i++)
    {
        path[i] = -1;
    }
    queue<int> q;
    q.push(0);
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        for(int i = 0; i<g[x].size(); i++)
        {
            if((edge[x][g[x][i]]!=0)&&(path[g[x][i]]==-1))
            {
                q.push(g[x][i]);
                path[g[x][i]] = x;
            }
        }
    }
    return (path[m-1]!=-1);
}

int main()
{
    ifstream infile("ditch.in");
    ofstream outfile("ditch.out");
    infile >> n >> m;
    int s, e, c;
    for(int i = 0; i<n; i++)
    {
        infile >> s >> e >> c;
        g[s-1].push_back(e-1);
        g[e-1].push_back(s-1);
        edge[s-1][e-1]+=c;
    }
    while(bfs())
    {
        int a = m-1, mi = INF;
        while(path[a]!=-2)
        {
            mi = min(mi,edge[path[a]][a]);
            a = path[a];
        }
        a = m-1;
        while(path[a]!=-2)
        {
            edge[path[a]][a]-=mi;
            edge[a][path[a]]+=mi;
            a = path[a];
        }
        maxflow+=mi;
    }
    outfile << maxflow << endl;
}
