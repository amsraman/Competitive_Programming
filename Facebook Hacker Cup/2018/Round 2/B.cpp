#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, m, a, b, c[200000], id[200000];
ll ans;
vector<int> g[200000];
priority_queue<ll> pq[200000];

void dfs(int x, int p)
{
    pq[x].push(x);
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=p)
        {
            dfs(g[x][i],x);
            if(pq[id[x]].size()<pq[id[g[x][i]]].size())
                swap(id[x],id[g[x][i]]);
            while(!pq[id[g[x][i]]].empty())
                pq[id[x]].push(pq[id[g[x][i]]].top()), pq[id[g[x][i]]].pop();
        }
    int temp = min(c[x],(int)pq[id[x]].size());
    for(int i = 0; i<temp; i++)
        ans+=pq[id[x]].top(), pq[id[x]].pop();
}

int main()
{
    freopen("jacks_candy_shop_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 0; _<t; _++)
    {
        cin >> n >> m >> a >> b;
        for(int i = 0; i<m; i++)
            c[(ll(a)*i+b)%n]++;
        for(int i = 0, p; i<n-1; i++)
        {
            cin >> p;
            g[p].push_back(i+1);
            g[i+1].push_back(p);
        }
        for(int i = 0; i<n; i++)
            id[i] = i;
        dfs(0,0);
        cout << "Case #" << _+1 << ": " << ans << endl;
        while(!pq[id[0]].empty())
            pq[id[0]].pop();
        for(int i = 0; i<n; i++)
            g[i].clear(), c[i] = 0;
        ans = 0;
    }
}
