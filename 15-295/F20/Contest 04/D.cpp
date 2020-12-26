#include <bits/stdc++.h>
typedef long long ll;
#define MOD 1000000007

using namespace std;

int n, m, bal, mb, dp[2001][2001], ans;
string s;

int mul(int a, int b)
{
    return (ll(a)*ll(b))%MOD;
}

int main()
{
    cin >> n >> m >> s;
    for(int i = 0; i<m; i++)
        bal+=(2*(s[i]=='(')-1), mb = min(mb,bal);
    dp[0][0] = 1;
    for(int i = 1; i<=n-m; i++)
        for(int j = 0; j<=n-m; j++)
        {
            if(j>0)
                dp[i][j] = dp[i-1][j-1];
            if(j<n)
                dp[i][j] = (dp[i][j]+dp[i-1][j+1])%MOD;
        }
    for(int i = 0; i<=n-m; i++)
        for(int j = -mb; j<=i; j++)
            if(bal+j<=n-m)
                ans = (ans+mul(dp[i][j],dp[n-m-i][bal+j]))%MOD;
    cout << ans << endl;   
}