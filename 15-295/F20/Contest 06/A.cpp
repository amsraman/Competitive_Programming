#include <bits/stdc++.h>
#define f first
#define s second
 
using namespace std;
 
int t, n, dist[1000];
vector<pair<int,int>> g[1000];
bool vis[1000];
 
int main()
{
    cin >> t >> n;
    for(int i = 0, x, y, z; i<t; i++)
    {
        cin >> x >> y >> z;
        g[x-1].push_back({y-1,z});
        g[y-1].push_back({x-1,z});
    }
    priority_queue<pair<int,int>> q;
    q.push({0,0});
    for(int i = 1; i<n; i++)
        dist[i] = 0x3f3f3f3f;
    while(!q.empty())
    {
        int x = q.top().s;
        q.pop();
        if(vis[x])
            continue;
        vis[x] = true;
        for(int i = 0; i<g[x].size(); i++)
            if(!vis[g[x][i].f]&&dist[x]+g[x][i].s<dist[g[x][i].f])
                dist[g[x][i].f] = dist[x]+g[x][i].s, q.push({-dist[g[x][i].f],g[x][i].f});
    }
    cout << dist[n-1] << endl;
}