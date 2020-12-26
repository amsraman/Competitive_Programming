#include <bits/stdc++.h>

using namespace std;

int n, b[4000], dp[4001][4001], ans;

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> b[i];
    for(int i = 1; i<=n; i++)
        for(int j = 0, pv = 0; j<i; j++)
        {
            dp[j][i] = dp[pv][j]+1;
            if(b[j-1]==b[i-1])
                pv = j;
            ans = max(ans,dp[j][i]);
        }
    cout << ans << endl;
}