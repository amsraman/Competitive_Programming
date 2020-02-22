#include <bits/stdc++.h>

using namespace std;

int n, m, a, b, c, f, cost[1000][1000], flow[1000][1000], d[1000], ans;
vector<int> g[1000];
bool v[1000];

int dij(int x)
{
    memset(d,0x3f3f3f3f,sizeof(d));
    memset(v,false,sizeof(v));
    priority_queue<pair<int,int> > q;
    d[0] = 0, q.push({0,0});
    while(!q.empty())
    {
        int cur = q.top().second;
        q.pop();
        if(!v[cur])
        {
            v[cur] = true;
            for(int i = 0; i<g[cur].size(); i++)
                if((!v[g[cur][i]])&&(flow[cur][g[cur][i]]>=x)&&(d[cur]+cost[cur][g[cur][i]]<d[g[cur][i]]))
                    d[g[cur][i]] = d[cur]+cost[cur][g[cur][i]], q.push({-d[g[cur][i]],g[cur][i]});
        }
    }
    return d[n-1];
}

int main()
{
    freopen("pump.in","r",stdin);
    freopen("pump.out","w",stdout);
    cin >> n >> m;
    for(int i = 0; i<m; i++)
    {
        cin >> a >> b >> c >> f;
        cost[b-1][a-1] = cost[a-1][b-1] = c, flow[b-1][a-1] = flow[a-1][b-1] = f;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    for(int i = 1; i<=1000; i++)
        if(dij(i))
            ans = max(ans,(1000000*i)/dij(i));
    cout << ans << endl;
}
