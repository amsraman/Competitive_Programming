#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

int n, q, a, b, x;
ll c, dp[200000];
vector<pair<int,ll> > g[200000];

ll dfs(int cur, int p = 0)
{
    dp[cur] = 0xfffffffffffffff;
    for(int i = 0; i<g[cur].size(); i++)
        if(g[cur][i].f!=p)
            dp[cur] = min(dp[cur],g[cur][i].s+min(0LL,dfs(g[cur][i].f,cur)));
    if(dp[cur]==0xfffffffffffffff)
        dp[cur] = 0;
    return dp[cur];
}

int main()
{
    cin >> n >> q;
    for(int i = 0; i<n-1; i++)
    {
        cin >> a >> b >> c;
        g[a-1].push_back({b-1,c});
        g[b-1].push_back({a-1,c});
    }
    dfs(0);
    for(int i = 0; i<q; i++)
    {
        cin >> x;
        cout << dp[x-1] << endl;
    }
}
