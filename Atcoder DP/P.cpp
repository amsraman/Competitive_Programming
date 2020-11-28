#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;

using namespace std;

int n, dp[100000][2];
vector<int> g[100000];

int add(int a, int b)
{
    return (a+b)%MOD;
}

int mul(int a, int b)
{
    return (ll(a)*ll(b))%MOD;
}

void dfs(int x, int p)
{
    dp[x][0] = dp[x][1] = 1;
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=p)
            dfs(g[x][i],x), dp[x][0] = mul(dp[x][0],dp[g[x][i]][1]), dp[x][1] = mul(dp[x][1],add(dp[g[x][i]][0],dp[g[x][i]][1]));
}

int main()
{
    cin >> n;
    for(int i = 0, x, y; i<n-1; i++)
    {
        cin >> x >> y;
        g[x-1].push_back(y-1);
        g[y-1].push_back(x-1);
    }
    dfs(0,0);
    cout << add(dp[0][0],dp[0][1]) << endl;
}
