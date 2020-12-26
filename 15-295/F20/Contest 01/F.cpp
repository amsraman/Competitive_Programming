#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

int t, n, k, m;
vector<pair<int,ll>> g[100];

bool vert(int x, ll ck)
{
    int ct = 0;
    pair<int,ll> dist[100];
    bool vis[100];
    for(int i = 0; i<n; i++)
        vis[i] = false, dist[i] = {k+1,1e12};
    priority_queue<pair<pair<int,ll>,int>> q;
    q.push({{-1,0},x});
    while(!q.empty())
    {
        int a = -q.top().f.f, c = q.top().s;
        ll b = -q.top().f.s;
        q.pop();
        if(vis[c])
            continue;
        vis[c] = true, ct++;
        if(a>k)
            return false;
        for(int i = 0; i<g[c].size(); i++)
            if(!vis[g[c][i].f])
            {
                if(b+g[c][i].s>ck)
                {
                    pair<int,ll> temp = {a+1,g[c][i].s};
                    if((g[c][i].s<=ck)&&(temp<dist[g[c][i].f]))
                        dist[g[c][i].f] = temp, q.push({{-a-1,-g[c][i].s},g[c][i].f});
                }
                else
                {
                    pair<int,ll> temp = {a,b+g[c][i].s};
                    if(temp<dist[g[c][i].f])
                        dist[g[c][i].f] = temp, q.push({{-a,-b-g[c][i].s},g[c][i].f});
                }
            }
    }
    return (ct==n);
}

bool valid(ll ck)
{
    bool ok = true;
    for(int i = 0; i<n; i++)
        ok&=vert(i,ck);
    return ok;
}

int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n >> k >> m;
        for(int i = 0, u, v, d; i<m; i++)
        {
            cin >> u >> v >> d;
            g[u].push_back({v,d});
            g[v].push_back({u,d});
        }
        ll lb = 0, ub = 1e11;
        while(lb<ub)
        {
            ll mid = (lb+ub)/2;
            if(valid(mid))
                ub = mid;
            else
                lb = mid+1;
        }
        cout << ub << endl;
        for(int i = 0; i<n; i++)
            g[i].clear();
    }
}