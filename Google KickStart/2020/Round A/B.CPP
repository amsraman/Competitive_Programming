#include <bits/stdc++.h>

using namespace std;

int t, n, k, p, pre[50][31], dp[51][1501];

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        memset(dp,0,sizeof(dp));
        cin >> n >> k >> p;
        for(int i = 0; i<n; i++)
            for(int j = 0; j<k; j++)
                cin >> pre[i][j+1];
        for(int i = 0; i<n; i++)
            for(int j = 2; j<=k; j++)
                pre[i][j]+=pre[i][j-1];
        for(int i = 0; i<n; i++)
            for(int j = 0; j<=p; j++)
                for(int l = 0; l<=min(p-j,k); l++)
                    dp[i+1][j+l] = max(dp[i+1][j+l],dp[i][j]+pre[i][l]);
        cout << "Case #" << cs+1 << ": " << dp[n][p] << endl;
    }
}
