#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, k, a[10000], dp[10000][4], ans;

int main()
{
    cin >> t;
    for(int _ = 0; _<t; _++)
    {
        cin >> k;
        for(int i = 0; i<k; i++)
            cin >> a[i];
        memset(dp,0,sizeof(dp));
        for(int i = k-2; i>=0; i--)
        {
            if(a[i]>a[i+1])
            {
                dp[i][3] = 1+min(min(dp[i+1][0],dp[i+1][1]),min(dp[i+1][2],dp[i+1][3]));
                dp[i][2] = dp[i+1][3];
                dp[i][1] = min(dp[i][2],dp[i+1][2]);
                dp[i][0] = min(dp[i][1],dp[i+1][1]);
            }
            else if(a[i]<a[i+1])
            {
                dp[i][0] = 1+min(min(dp[i+1][0],dp[i+1][1]),min(dp[i+1][2],dp[i+1][3]));
                dp[i][1] = dp[i+1][0];
                dp[i][2] = min(dp[i][1],dp[i+1][1]);
                dp[i][3] = min(dp[i][2],dp[i+1][2]);
            }
            else
                for(int j = 0; j<4; j++)
                    dp[i][j] = dp[i+1][j];
        }
        ans = min(min(dp[0][0],dp[0][1]),min(dp[0][2],dp[0][3]));
        cout << "Case #" << _+1 << ": " << ans << endl;
    }
}
