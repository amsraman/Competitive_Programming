#include <bits/stdc++.h>

using namespace std;

int n, m, a, b, c, moo[1000], dp[1001][1000], ans;
vector<int> g[1000];

int main()
{
    freopen("time.in","r",stdin);
    freopen("time.out","w",stdout);
    cin >> n >> m >> c;
    for(int i = 0; i<n; i++)
        cin >> moo[i];
    for(int i = 0; i<m; i++)
    {
        cin >> a >> b;
        g[a-1].push_back(b-1);
    }
    memset(dp,-0x3f3f3f3f,sizeof(dp));
    dp[0][0] = 0;
    for(int i = 0; i<1000; i++)
    {
        for(int j = 0; j<n; j++)
            for(int k = 0; k<g[j].size(); k++)
                dp[i+1][g[j][k]] = max(dp[i+1][g[j][k]],dp[i][j]+moo[g[j][k]]);
        ans = max(ans,dp[i+1][0]-c*(i+1)*(i+1));
    }
    cout << ans << endl;
}
