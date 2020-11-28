#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

int n, dp[(1<<21)];
bool a[21][21];

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> a[i][j];
    dp[0] = 1;
    for(int i = 1; i<(1<<n); i++)
        for(int j = 0; j<n; j++)
            if(((1<<j)&i)&&a[j][__builtin_popcount(i)-1])
                dp[i] = (dp[i]+dp[i^(1<<j)])%MOD;
    cout << dp[(1<<n)-1] << endl;
}
