/*
ID: adityasund1
TASK: telecow
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m, c1, c2, a, b, edge[200][200], edge1[200][200], path[200], maxf, maxf1;
vector<int> g[200], setans;

bool bfs(int a, int b)
{
    queue<int> q;
    for(int i = 0; i<2*n; i++)
    {
        path[i] = -1;
    }
    path[a+n] = -2;
    q.push(a+n);
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        for(int i = 0; i<g[x].size(); i++)
        {
            if((edge1[x][g[x][i]]!=0)&&(path[g[x][i]]==-1))
            {
                q.push(g[x][i]);
                path[g[x][i]] = x;
            }
        }
    }
    return (path[b]!=-1);
}

int main()
{
    ifstream infile("telecow.in");
    ofstream outfile("telecow.out");
    infile >> n >> m >> c1 >> c2;
    c1--, c2--;
    for(int i = 0; i<n; i++)
    {
        g[i].push_back(i+n);
        g[i+n].push_back(i);
        edge[i][i+n] = edge[i+n][i] = edge1[i][i+n] = edge1[i+n][i] = 1;
    }
    for(int i = 0; i<m; i++)
    {
        infile >> a >> b;
        g[a+n-1].push_back(b-1);
        g[b+n-1].push_back(a-1);
        edge[a+n-1][b-1] = edge1[a+n-1][b-1] = edge[b+n-1][a-1] = edge1[b+n-1][a-1] = 1;
    }
    while(bfs(c1,c2))
    {
        int a = path[c2];
        while(path[a]!=-2)
        {
            edge1[path[a]][a]--;
            edge1[a][path[a]]++;
            a = path[a];
        }
        maxf++;
    }
    outfile << maxf << endl;
    for(int i = 0; i<n; i++)
    {
        maxf1 = 0;
        for(int j = 0; j<2*n; j++)
        {
            for(int k = 0; k<2*n; k++)
            {
                edge1[j][k] = edge[j][k];
            }
        }
        edge1[i][i+n] = edge1[i+n][i] = 0;
        while(bfs(c1,c2))
        {
            int a = path[c2];
            while(path[a]!=-2)
            {
                edge1[path[a]][a]--;
                edge1[a][path[a]]++;
                a = path[a];
            }
            maxf1++;
        }
        if((maxf1==maxf-1)&&(i!=c1)&&(i!=c2))
        {
            setans.push_back(i);
            edge[i][i+n] = edge[i+n][i] = 0;
            maxf--;
        }
    }
    for(int i = 0; i<setans.size(); i++)
    {
        if(i!=0) outfile << " ";
        outfile << setans[i]+1;
    }
    outfile << endl;
}
