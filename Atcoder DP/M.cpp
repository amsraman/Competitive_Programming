#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

int n, k, a[100], dp[101][100002];

int main()
{
    cin >> n >> k;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    for(int i = 1; i<=k+1; i++)
        dp[0][i] = 1;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<=k; j++)
            dp[i+1][j+1] = (dp[i+1][j]+(dp[i][j+1]-dp[i][max(0,j-a[i])]+MOD)%MOD)%MOD;
    cout << (dp[n][k+1]-dp[n][k]+MOD)%MOD << endl;
}
