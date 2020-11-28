#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#define INF 0x3f3f3f3f

using namespace std;

int n, edge[250][250];
bool path[250][250] = {false};
vector<int> g[250];

int dij(int t)
{
    priority_queue<pair<int,int> > q;
    bool v[250] = {false};
    int d[n];
    for(int i = 0; i<n; i++){d[i] = INF;}
    d[0] = 0;
    q.push({0,0});
    while(!q.empty())
    {
        int a = q.top().second;
        q.pop();
        if(!v[a])
        {
            v[a] = true;
            for(int i = 0; i<g[a].size(); i++)
            {
                if(!v[g[a][i]])
                {
                    d[g[a][i]] = min(d[g[a][i]],d[a]+edge[min(a,g[a][i])][max(a,g[a][i])]);
                    q.push({-d[g[a][i]],g[a][i]});
                }
            }
        }
    }
    if(t==0)
    {
        int z = n-1;
        while(z!=0)
        {
            for(int i = 0; i<g[z].size(); i++)
            {
                if(d[g[z][i]]+edge[min(g[z][i],z)][max(g[z][i],z)]==d[z])
                {
                    path[min(g[z][i],z)][max(g[z][i],z)] = true;
                    z = g[z][i];
                    break;
                }
            }
        }
    }
    return d[n-1];
}

int main()
{
    ifstream infile("rblock.in");
    ofstream outfile("rblock.out");
    int m, a;
    infile >> n >> m;
    pair<int,int> p[m];
    for(int i = 0; i<m; i++)
    {
        infile >> p[i].first >> p[i].second >> a;
        edge[min(p[i].first,p[i].second)-1][max(p[i].first,p[i].second)-1] = a;
        g[p[i].first-1].push_back(p[i].second-1);
        g[p[i].second-1].push_back(p[i].first-1);
    }
    int d = dij(0), ans = 0;
    for(int i = 0; i<m; i++)
    {
        if(path[min(p[i].first,p[i].second)-1][max(p[i].first,p[i].second)-1])
        {
            edge[min(p[i].first,p[i].second)-1][max(p[i].first,p[i].second)-1]*=2;
            ans = max(ans,dij(1)-d);
            edge[min(p[i].first,p[i].second)-1][max(p[i].first,p[i].second)-1]/=2;
        }
    }
    outfile << ans << endl;
}
