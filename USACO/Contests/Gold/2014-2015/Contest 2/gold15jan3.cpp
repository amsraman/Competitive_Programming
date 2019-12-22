#include <bits/stdc++.h>

using namespace std;

int n, m, sccs, scc[100000], counts[100000], dp[100000][2], ans;
bool v[100000][2];
pair<int,int> edges[100000];
vector<int> g[100000][2], dag[100000][2], st;

void dfs(int a, int b)
{
    v[a][b] = true;
    if(b) scc[a] = sccs, counts[sccs]++;
    for(int i = 0; i<g[a][b].size(); i++)
        if(!v[g[a][b][i]][b])
            dfs(g[a][b][i],b);
    if(!b) st.push_back(a);
}

int findDP(int a, int b)
{
    if(dp[a][b]!=0)
        return dp[a][b];
    if(a!=scc[0]) dp[a][b] = -0x3f3f3f3f;
    for(int i = 0; i<dag[a][b^1].size(); i++)
        dp[a][b] = max(dp[a][b],findDP(dag[a][b^1][i],b));
    dp[a][b]+=counts[a];
    return dp[a][b];
}

int main()
{
    freopen("grass.in","r",stdin);
    freopen("grass.out","w",stdout);
    cin >> n >> m;
    for(int i = 0; i<m; i++)
    {
        cin >> edges[i].first >> edges[i].second;
        g[edges[i].first-1][0].push_back(edges[i].second-1);
        g[edges[i].second-1][1].push_back(edges[i].first-1);
    }
    for(int i = 0; i<n; i++)
        if(!v[i][0])
            dfs(i,0);
    for(int i = n-1; i>=0; i--)
        if(!v[st[i]][1])
            dfs(st[i],1), sccs++;
    for(int i = 0; i<m; i++)
    {
        if(scc[edges[i].first-1]!=scc[edges[i].second-1])
        {
            dag[scc[edges[i].first-1]][0].push_back(scc[edges[i].second-1]);
            dag[scc[edges[i].second-1]][1].push_back(scc[edges[i].first-1]);
        }
    }
    for(int i = 0; i<sccs; i++)
        findDP(i,0), findDP(i,1);
    ans = 2*counts[scc[0]];
    for(int i = 0; i<sccs; i++)
        for(int j = 0; j<dag[i][0].size(); j++)
            ans = max(ans,dp[dag[i][0][j]][0]+dp[i][1]);
    cout << ans-counts[scc[0]] << endl;
}
