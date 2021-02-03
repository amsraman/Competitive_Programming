#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, a[1000000];
ll dp[1000001][2];

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    for(int i = 1; i<n; i++)
    {
        dp[i][0] = dp[i][1] = max(dp[i-1][0],dp[i-1][1]);
        if(a[i-1]<=a[i])
            dp[i][0] = max(dp[i][0],dp[i-1][0]+a[i]-a[i-1]);
        if(a[i-1]>=a[i])
            dp[i][1] = max(dp[i][1],dp[i-1][1]+a[i-1]-a[i]);
    }
    cout << max(dp[n-1][0],dp[n-1][1]) << endl;
}