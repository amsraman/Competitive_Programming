#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, p[1000];
ll dp[1000][1000][2];

int main()
{
    freopen("cowrun.in","r",stdin);
    freopen("cowrun.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        cin >> p[i];
    }
    sort(p,p+n);
    for(int i = 0; i<n; i++)
    {
        dp[i][i][0] = dp[i][i][1] = ll(abs(p[i])*n);
    }
    for(int i = n-1; i>=0; i--)
    {
        for(int j = i+1; j<n; j++)
        {
            ll a = (p[j]-p[i])*ll(n+i-j), b = (p[i+1]-p[i])*ll(n+i-j), c = (p[j]-p[j-1])*ll(n+i-j);
            dp[i][j][0] = min(min(dp[i+1][j][0]+b,dp[i+1][j][1]+a),min(dp[i][j-1][0]+a+(p[j]-p[i])*(n+i-j-1),dp[i][j-1][1]+c+(p[j]-p[i])*(n+i-j-1)));
            dp[i][j][1] = min(min(dp[i][j-1][0]+a,dp[i][j-1][1]+c),min(dp[i+1][j][0]+b+(p[j]-p[i])*(n+i-j-1),dp[i+1][j][1]+a+(p[j]-p[i])*(n+i-j-1)));
        }
    }
    cout << min(dp[0][n-1][0],dp[0][n-1][1]) << endl;
}
