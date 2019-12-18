#include <bits/stdc++.h>
#define INF 0xfffffffffffffff
typedef long long ll;

using namespace std;

int n, m, k, q, u, v, d, hub[200], ai, bi, pos;
ll dist[200][20000][2], cur, ans;
vector<pair<int,ll> > g[20000][2];

void dij(int a, int b)
{
    bool v[20000];
    for(int i = 0; i<n; i++) v[i] = false;
    priority_queue<pair<ll,int> > q;
    dist[a][hub[a]][b] = 0;
    q.push({0,hub[a]});
    while(!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if(!v[x])
        {
            v[x] = true;
            for(int i = 0; i<g[x][b].size(); i++)
            {
                if((!v[g[x][b][i].first])&&(dist[a][x][b]+g[x][b][i].second<dist[a][g[x][b][i].first][b]))
                {
                    dist[a][g[x][b][i].first][b] = dist[a][x][b]+g[x][b][i].second;
                    q.push({-dist[a][g[x][b][i].first][b],g[x][b][i].first});
                }
            }
        }
    }
}

int main()
{
    freopen("vacationgold.in","r",stdin);
    freopen("vacationgold.out","w",stdout);
    cin >> n >> m >> k >> q;
    for(int i = 0; i<m; i++)
    {
        cin >> u >> v >> d;
        g[u-1][0].push_back({v-1,d});
        g[v-1][1].push_back({u-1,d});
    }
    for(int i = 0; i<k; i++)
    {
        cin >> hub[i];
        hub[i]--;
    }
    for(int i = 0; i<k; i++) for(int j = 0; j<n; j++) dist[i][j][0] = dist[i][j][1] = INF;
    for(int i = 0; i<k; i++) dij(i,0), dij(i,1);
    for(int i = 0; i<q; i++)
    {
        cin >> ai >> bi;
        cur = INF;
        for(int j = 0; j<k; j++)
        {
            cur = min(cur,dist[j][ai-1][1]+dist[j][bi-1][0]);
        }
        if(cur<INF) pos++, ans+=cur;
    }
    cout << pos << endl << ans << endl;
}
