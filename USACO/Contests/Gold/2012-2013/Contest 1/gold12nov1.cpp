#include <bits/stdc++.h>

using namespace std;

int n, a[1000], dp[1000][1000];
string s;

int main()
{
    freopen("bbreeds.in","r",stdin);
    freopen("bbreeds.out","w",stdout);
    cin >> s;
    n = s.length();
    for(int i = 0; i<n; i++)
    {
        if(i!=0) a[i] = a[i-1];
        a[i]+=((s[i]=='(')?1:-1);
    }
    dp[0][0] = dp[0][1] = 1;
    for(int i = 1; i<n; i++)
    {
        for(int j = 0; j<=a[i]; j++)
        {
            if(s[i]==')')
            {
                dp[i][j] = (dp[i-1][j]+dp[i-1][j+1])%2012;
            }
            else
            {
                if(j!=0) dp[i][j] = dp[i-1][j-1];
                if(j!=a[i]) dp[i][j] = (dp[i][j]+dp[i-1][j])%2012;
            }
        }
    }
    cout << dp[n-1][0] << endl;
}
