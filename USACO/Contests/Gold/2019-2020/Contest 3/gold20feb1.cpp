#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, c, a, b, x, state[100000], dp[100000];
vector<int> top;
vector<pair<int,int>> g[100000];

void toposort(int u)
{
    if(state[u]==2)
        return;
    state[u] = 1;
    for(int i = 0; i<g[u].size(); i++)
        toposort(g[u][i].f);
    state[u] = 2;
    top.push_back(u);
}

int main()
{
    freopen("timeline.in","r",stdin);
    freopen("timeline.out","w",stdout);
    memset(dp,0x3f3f3f3f,sizeof(dp));
    cin >> n >> m >> c;
    for(int i = 0; i<n; i++)
        cin >> dp[i];
    for(int i = 0; i<c; i++)
    {
        cin >> a >> b >> x;
        g[a-1].push_back({b-1,x});
    }
    for(int i = 0; i<n; i++)
        if(!state[i])
            toposort(i);
    for(int i = n-1; i>=0; i--)
        for(int j = 0; j<g[top[i]].size(); j++)
            dp[g[top[i]][j].f] = max(dp[g[top[i]][j].f],dp[top[i]]+g[top[i]][j].s);
    for(int i = 0; i<n; i++)
        cout << dp[i] << endl;
}
