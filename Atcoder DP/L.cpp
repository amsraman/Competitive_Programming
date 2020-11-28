#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, a[3000];
ll dp[3000][3000];

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    for(int i = 0; i<n; i++)
        dp[i][i] = (-1+2*(n%2))*a[i];
    for(int i = n-1; i>=0; i--)
        for(int j = i+1; j<n; j++)
        {
            if((j-i)%2==(n-1)%2)
                dp[i][j] = max(a[i]+dp[i+1][j],a[j]+dp[i][j-1]);
            else
                dp[i][j] = min(dp[i+1][j]-a[i],dp[i][j-1]-a[j]);
        }
    cout << dp[0][n-1] << endl;
}
