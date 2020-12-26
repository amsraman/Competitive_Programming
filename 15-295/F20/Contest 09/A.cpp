#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

int n, k, dp[2001][2001], ans;
vector<int> fact[2001];

int main()
{
    cin >> n >> k;
    dp[1][0] = 1;
    for(int i = 1; i<=n; i++)
        for(int j = 0; j<=n; j+=i)
            fact[j].push_back(i);
    for(int i = 1; i<=n; i++)
        for(int j = 0; j<k; j++)
            for(int x = 0; x<fact[i].size(); x++)
                dp[i][j+1] = (dp[i][j+1]+dp[fact[i][x]][j])%MOD;
    for(int i = 0; i<=n; i++)
        ans = (ans+dp[i][k])%MOD;
    cout << ans << endl;
}