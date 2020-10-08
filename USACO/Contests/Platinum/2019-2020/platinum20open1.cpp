#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;

using namespace std;

int n, I2 = 5e8+4;
ll dp1[2001][2001], dp2[2001][2001], ans;
string grid[2000];

int main()
{
    freopen("sprinklers2.in","r",stdin);
    freopen("sprinklers2.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> grid[i];
    dp1[0][0] = dp2[0][0] = 1;
    for(int i = 0; i<=n; i++)
        for(int j = 0; j<=n; j++)
        {
            if(i>0)
                dp1[i][j] = dp1[i-1][j];
            if(j>0)
                dp2[i][j] = dp2[i][j-1];
            if((i>0)&&(j>0)&&(grid[i-1][j-1]!='W'))
            {
                dp1[i][j] = (dp1[i][j]+dp2[i-1][j]*I2)%MOD;
                dp2[i][j] = (dp2[i][j]+dp1[i][j-1]*I2)%MOD;
            }
        }
    ans = (dp1[n][n]+dp2[n][n])%MOD;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            if(grid[i][j]=='.')
                ans = (ans*2)%MOD;
    cout << ans << endl;
}
