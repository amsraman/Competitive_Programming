#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

int n;
long long dp[500][500][2];
string in[500];

int main()
{
    freopen("palpath.in","r",stdin);
    freopen("palpath.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> in[i];
    for(int i = 0; i<n; i++)
        dp[i][i][0] = 1;
    for(int k = 1; k<n; k++)
    {
        for(int i = 0; i<n; i++)
            for(int j = i; j<n; j++)
                if((n-i-k-1>=0)&&(n-j+k-1<n)&&(in[i][n-i-k-1]==in[j][n-j+k-1]))
                    dp[i][j][1] = (dp[i][j][0]+dp[i+1][j][0]+dp[i][j-1][0]+dp[i+1][j-1][0])%MOD;
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
                dp[i][j][0] = dp[i][j][1], dp[i][j][1] = 0;
    }
    cout << dp[0][n-1][0] << endl;
}
