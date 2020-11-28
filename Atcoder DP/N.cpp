#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n;
ll a[401], dp[400][400];

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> a[i+1];
    for(int i = 0; i<n; i++)
        a[i+1]+=a[i];
    for(int i = 0; i<n; i++)
        for(int j = i+1; j<n; j++)
            dp[i][j] = 1e16;
    for(int i = n-1; i>=0; i--)
        for(int j = i+1; j<n; j++)
            for(int k = i; k<j; k++)
                dp[i][j] = min(dp[i][j],a[j+1]-a[i]+dp[i][k]+dp[k+1][j]);
    cout << dp[0][n-1] << endl;
}
