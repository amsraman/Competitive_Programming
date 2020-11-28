#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, m, dp[100000];
vector<int> g[100000];

int mul(int a, int b)
{
    return (ll(a)*ll(b))%m;
}

void dfs1(int x, int p)
{
    dp[x] = 1;
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=p)
            dfs1(g[x][i],x), dp[x] = mul(dp[x],dp[g[x][i]]+1);
}

void dfs2(int x, int p, int prod)
{
    vector<int> pf, sf;
    pf.push_back(1);
    for(int i = 0, num; i<g[x].size(); i++)
    {
        num = (g[x][i]==p?0:dp[g[x][i]]);
        pf.push_back(num+1), sf.push_back(num+1);
    }
    sf.push_back(1);
    for(int i = 1; i<=g[x].size(); i++)
        pf[i] = mul(pf[i],pf[i-1]), sf[g[x].size()-i] = mul(sf[g[x].size()-i],sf[g[x].size()-i+1]);
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=p)
            dfs2(g[x][i],x,mul(mul(pf[i],sf[i+1]),prod)+1);
    dp[x] = mul(dp[x],prod);
}

int main()
{
    cin >> n >> m;
    for(int i = 0, x, y; i<n-1; i++)
    {
        cin >> x >> y;
        g[x-1].push_back(y-1);
        g[y-1].push_back(x-1);
    }
    dfs1(0,0), dfs2(0,0,1);
    for(int i = 0; i<n; i++)
        cout << dp[i] << endl;
}
