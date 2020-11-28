#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

int n, dp[3000][3000], ans;
string s;

int main()
{
    cin >> n >> s;
    dp[0][0] = 1;
    for(int i = 1; i<n; i++)
    {
        if(s[i-1]=='<')
            for(int j = 1; j<n; j++)
                dp[i][j] = (dp[i-1][j-1]+dp[i][j-1])%MOD;
        else
            for(int j = i-1; j>=0; j--)
                dp[i][j] = (dp[i-1][j]+dp[i][j+1])%MOD;
    }
    for(int i = 0; i<n; i++)
        ans = (ans+dp[n-1][i])%MOD;
    cout << ans << endl;
}
