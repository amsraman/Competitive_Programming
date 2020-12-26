#include <bits/stdc++.h>
#define f first
#define s second
 
using namespace std;
 
int n, m, edge[250][250], prv[250], prv1[250], dist[250], ans1, ans2;
vector<int> g[250];
bool vis[250];
 
int dij()
{
    memset(vis,0,sizeof(vis));
    memset(dist,0x3f3f3f3f,sizeof(dist));
    priority_queue<pair<int,int>> q;
    q.push({0,0}), dist[0] = 0;
    while(!q.empty())
    {
        int x = q.top().s;
        q.pop();
        if(vis[x])
            continue;
        vis[x] = true;
        for(int i = 0; i<g[x].size(); i++)
            if(!vis[g[x][i]]&&dist[x]+edge[x][g[x][i]]<dist[g[x][i]])
                dist[g[x][i]] = dist[x]+edge[x][g[x][i]], prv[g[x][i]] = x, q.push({-dist[g[x][i]],g[x][i]});
    }
    return dist[n-1];
}
 
int main()
{
    cin >> n >> m;
    for(int i = 0, x, y, z; i<m; i++)
    {
        cin >> x >> y >> z;
        g[x-1].push_back(y-1);
        g[y-1].push_back(x-1);
        edge[x-1][y-1] = edge[y-1][x-1] = z;
    }
    ans1 = ans2 = dij();
    for(int i = 0; i<n; i++)
        prv1[i] = prv[i];
    int cur = n-1;
    while(cur!=0)
    {
        edge[cur][prv1[cur]]*=2, edge[prv1[cur]][cur]*=2;
        ans2 = max(ans2,dij());
        edge[cur][prv1[cur]]/=2, edge[prv1[cur]][cur]/=2, cur = prv1[cur];
    }
    cout << ans2-ans1 << endl;
}