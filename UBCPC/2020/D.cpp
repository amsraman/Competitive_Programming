#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, k;
ll p, dp[2001][2001][8][2], pre[2001][2002][8][2];

int main()
{
    cin >> n >> k >> p;
    for(int i = 0; i<=k; i++)
        dp[0][0][i][0] = dp[0][0][i][1] = 1;
    for(int i = 0; i<=n; i++)
        for(int j = 0; j<=k; j++)
            pre[0][i+1][j][0] = pre[0][i][j][0]+dp[0][i][j][0], pre[0][i+1][j][1] = pre[0][i][j][1]+dp[0][i][j][1];
    for(int i = 1; i<=n; i++)
    {
        for(int j = 0; j<=i; j++)
            for(int str = 0; str<=k; str++)
            {
                dp[i][j][str][0] = pre[i-1][j][2][1];
                dp[i][j][str][1] = pre[i-1][i+1][2][0]-pre[i-1][j][2][0]+p;
                if(str<k)
                    dp[i][j][str][0]+=(pre[i-1][i+1][str+1][0]-pre[i-1][j][str+1][0]+p), dp[i][j][str][1]+=pre[i-1][j][str+1][1];
                dp[i][j][str][0]%=p, dp[i][j][str][1]%=p;
            }
        for(int j = 0; j<=n; j++)
            for(int str = 0; str<=k; str++)
            {
                pre[i][j+1][str][0] = (pre[i][j][str][0]+dp[i][j][str][0])%p;
                pre[i][j+1][str][1] = (pre[i][j][str][1]+dp[i][j][str][1])%p;
            }
    }
    cout << dp[n][0][0][0] << endl;
}
