#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, k, dp[30001][31][31], ans = 0x3f3f3f3f;
vector<pair<int,int>> mvs;
string w[10000];

int main()
{
    cin >> n >> k;
    for(int i = 0, a, b; i<n; i++)
    {
        cin >> a >> b;
        mvs.push_back({0,a});
        mvs.push_back({a,b});
        mvs.push_back({b,0});
    }
    for(int i = 0; i<n; i++)
        cin >> w[i];
    memset(dp,0x3f3f3f3f,sizeof(dp));
    dp[0][0][0] = 0;
    for(int i = 0; i<3*n; i++)
    {
        if(w[i/3][i%3]=='S')
            for(int x = 0; x<=k; x++)
                for(int y = 0; y<=k; y++)
                    dp[i+1][x][y] = dp[i][x][y];
        for(int x = 0; x<=k; x++)
            dp[i+1][mvs[i].s][x] = min(dp[i+1][mvs[i].s][x],dp[i][mvs[i].f][x]+1);
        for(int x = 0; x<=k; x++)
            dp[i+1][x][mvs[i].s] = min(dp[i+1][x][mvs[i].s],dp[i][x][mvs[i].f]+1);
        dp[i+1][mvs[i].s][mvs[i].s] = min(dp[i+1][mvs[i].s][mvs[i].s],dp[i][mvs[i].f][mvs[i].f]+1);
    }
    for(int i = 0; i<=k; i++)
        for(int j = 0; j<=k; j++)
            ans = min(ans,dp[3*n][i][j]);
    cout << ans << endl;
}
