/*
ID: adityasund1
TASK: milk6
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 0x3f3f3f3f

using namespace std;

int n, m, edge[32][32], edge1[32][32], path[32], mincut;
vector<int> g[32], rem;

bool bfs()
{
    queue<int> q;
    path[0] = -2;
    for(int i = 1; i<n; i++){path[i] = -1;}
    q.push(0);
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
    return (path[n-1]!=-1);
}

int main()
{
    ifstream infile("milk6.in");
    ofstream outfile("milk6.out");
    infile >> n >> m;
    pair<int,int> in[m], ed[m];
    int a, b, c;
    for(int i = 0; i<m; i++)
    {
        infile >> a >> b >> c;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
        edge[a-1][b-1]+=c;
        edge1[a-1][b-1]+=c;
        in[i] = {a-1,b-1};
        ed[i] = {-c,i};
    }
    sort(ed,ed+m);
    while(bfs())
    {
        int a = n-1, mi = INF;
        while(path[a]!=-2)
        {
            mi = min(mi,edge1[path[a]][a]);
            a = path[a];
        }
        a = n-1;
        while(path[a]!=-2)
        {
            edge1[path[a]][a]-=mi;
            edge1[a][path[a]]+=mi;
            a = path[a];
        }
        mincut+=mi;
    }
    int curcut = mincut, counter = 0;
    while(curcut!=0)
    {
        int cut = 0;
        for(int i = 0; i<n; i++){for(int j = 0; j<n; j++){edge1[i][j] = edge[i][j];}}
        edge1[in[ed[counter].second].first][in[ed[counter].second].second]+=ed[counter].first;
        while(bfs())
        {
            int a = n-1, mi = INF;
            while(path[a]!=-2)
            {
                mi = min(mi,edge1[path[a]][a]);
                a = path[a];
            }
            a = n-1;
            while(path[a]!=-2)
            {
                edge1[path[a]][a]-=mi;
                edge1[a][path[a]]+=mi;
                a = path[a];
            }
            cut+=mi;
        }
        if(cut==curcut+ed[counter].first)
        {
            rem.push_back(ed[counter].second);
            curcut+=ed[counter].first;
            edge[in[ed[counter].second].first][in[ed[counter].second].second]+=ed[counter].first;
        }
        counter++;
    }
    sort(rem.begin(),rem.end());
    outfile << mincut << " " << rem.size() << endl;
    for(int i = 0; i<rem.size(); i++)
    {
        outfile << rem[i]+1 << endl;
    }
}
