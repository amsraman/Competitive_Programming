#include <bits/stdc++.h>

using namespace std;

int n;
double p[3000], dp[3000][3000], ans;

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> p[i];
    dp[0][0] = 1;
    for(int i = 1; i<=n; i++)
        for(int j = 0; j<=i; j++)
        {
            if(j>0)
                dp[j][i-j]+=p[i-1]*dp[j-1][i-j];
            if(j<i)
                dp[j][i-j]+=(1-p[i-1])*dp[j][i-j-1];
        }
    for(int j = 0; j<=n; j++)
        if(j>n-j)
            ans+=dp[j][n-j];
    cout << fixed << setprecision(10) << ans << endl;
}
