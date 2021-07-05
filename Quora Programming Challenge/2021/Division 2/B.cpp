#include <bits/stdc++.h>
#define f first
#define s second
#define MOD 1000000007

using namespace std;

int n;
string grid[1000];
pair<int,int> dp[1000][1000];

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> grid[i];
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            dp[i][j] = {-1,1};
    dp[0][0] = {0,1};
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
        {
            if(i>0)
                dp[i][j] = dp[i-1][j];
            if(j>0&&dp[i][j-1].f>dp[i][j].f)
                dp[i][j] = dp[i][j-1];
            else if(j>0&&dp[i][j-1].f==dp[i][j].f)
                dp[i][j].s = (dp[i][j].s+dp[i][j-1].s)%MOD;
            if(grid[i][j]=='1')
                ++dp[i][j].f;
        }
    cout << dp[n-1][n-1].f << " " << dp[n-1][n-1].s << endl;
}