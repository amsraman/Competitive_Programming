#include <bits/stdc++.h>

using namespace std;

int n, m, w, l, r, dp[300][300], maxw[300][300][300];

int main()
{
    freopen("pieaters.in","r",stdin);
    freopen("pieaters.out","w",stdout);
    cin >> n >> m;
    for(int i = 0; i<m; i++)
    {
        cin >> w >> l >> r;
        for(int j = l-1; j<r; j++)
            maxw[l-1][r-1][j] = max(maxw[l-1][r-1][j],w);
    }
    for(int i = n-1; i>=0; i--)
        for(int j = i; j<n; j++)
            for(int k = i; k<=j; k++)
            {
                if(i!=n-1)
                    maxw[i][j][k] = max(maxw[i][j][k],maxw[i+1][j][k]);
                if(j!=0)
                    maxw[i][j][k] = max(maxw[i][j][k],maxw[i][j-1][k]);
                dp[i][j] = max(dp[i][j],maxw[i][j][k]);
            }
    for(int i = n-1; i>=0; i--)
        for(int j = i+1; j<n; j++)
        {
            for(int k = i; k<j; k++)
                dp[i][j] = max(dp[i][j],dp[i][k]+dp[k+1][j]);
            for(int k = i+1; k<j; k++)
                dp[i][j] = max(dp[i][j],dp[i][k-1]+dp[k+1][j]+maxw[i][j][k]);
            dp[i][j] = max(dp[i][j],maxw[i][j][i]+dp[i+1][j]);
            dp[i][j] = max(dp[i][j],dp[i][j-1]+maxw[i][j][j]);
        }
    cout << dp[0][n-1] << endl;
}
