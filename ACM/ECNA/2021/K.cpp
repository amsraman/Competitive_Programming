#include <bits/stdc++.h>

using namespace std;

int n, m, dp[5001][21], mn, mx;

int main()
{
    cin >> n >> m;
    for(int i = 1; i<=n; i++)
        dp[i][0] = 0x3f3f3f3f;
    for(int i = 1; i<=n; i++)
        for(int j = 1; j<=m; j++)
        {
            dp[i][j] = 0x3f3f3f3f;
            for(int k = 1; k<=i; k++)
                dp[i][j] = min(dp[i][j],1+max(dp[k-1][j-1],dp[i-k][j]));
        }
    mn = 1, mx = n;
    while(1+max(dp[mn-1][m-1],dp[n-mn][m])!=dp[n][m])
        mn++;
    while(1+max(dp[mx-1][m-1],dp[n-mn][m])!=dp[n][m])
        mx--;
    cout << dp[n][m] << " ";
    if(mn==mx)
        cout << mn << endl;
    else
        cout << mn << '-' << mx << endl;
}