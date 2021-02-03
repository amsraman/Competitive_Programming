#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, deg[200000], dist[200000], cnt;
vector<int> g[200000];
vector<pair<int,int>> edges;
bool vis[200000], red[200000];

int main()
{
    cin >> n >> m;
    for(int i = 0, u, v; i<m; i++)
    {
        cin >> u >> v;
        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
        edges.push_back({u-1,v-1});
    }
    queue<int> q;
    fill(dist,dist+n,0x3f3f3f3f);
    q.push(0), vis[0] = true;
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        for(int i: g[x])
            if(!vis[i])
                q.push(i), dist[i] = dist[x]+1, vis[i] = true;
    }
    for(int i = 0; i<m; i++)
    {
        if(dist[edges[i].f]<=dist[edges[i].s])
            deg[edges[i].s]++;
        if(dist[edges[i].f]>=dist[edges[i].s])
            deg[edges[i].f]++, swap(edges[i].f,edges[i].s);
    }
    for(int i = 0; i<m; i++)
        if(deg[edges[i].s]>1)
        {
            cout << i+1 << endl;
            ++cnt;
        }
    if(cnt==0)
        cout << "NO" << endl;
}