#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

int n, k, a[400], tot, tmax, dp[400][400];

int main()
{
    freopen("snakes.in","r",stdin);
    freopen("snakes.out","w",stdout);
    cin >> n >> k;
    for(int i = 0; i<n; i++) cin >> a[i];
    memset(dp,INF,sizeof(dp));
    for(int i = 0; i<n; i++)
    {
        tot+=a[i], tmax = max(tmax,a[i]);
        dp[i][0] = tmax*(i+1)-tot;
        for(int j = 1; j<=k; j++)
        {
            int cmax = 0, ctot = 0;
            for(int ch = i; ch>0; ch--)
            {
                cmax = max(cmax,a[ch]), ctot+=a[ch];
                dp[i][j] = min(dp[i][j],dp[ch-1][j-1]+cmax*(i-ch+1)-ctot);
            }
        }
    }
    cout << dp[n-1][k] << endl;
}
