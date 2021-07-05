#include <bits/stdc++.h>

using namespace std;

int x, y, dp[100][100][51], ans = 0x3f3f3f3f;
string key, grid[100];

int main()
{
    cin >> x >> y >> key;
    for(int i = 0; i<y; i++)
        cin >> grid[y-i-1];
    for(int i = 0; i<y; i++)
        for(int j = 0; j<x; j++)
            for(int k = 0; k<=key.length(); k++)
            {
                dp[i][j][k] = 0x3f3f3f3f;
                if(i==0&&j==0&&k==0)
                    dp[i][j][k] = (grid[i][j]-'0');
                if(i>0)
                    dp[i][j][k] = min(dp[i][j][k],dp[i-1][j][k]+(grid[i][j]-'0'));
                if(j>0)
                    dp[i][j][k] = min(dp[i][j][k],dp[i][j-1][k]+(grid[i][j]-'0'));
                if(k>0&&i>(key[k-1]-'0'))
                    dp[i][j][k] = min(dp[i][j][k],dp[i-(key[k-1]-'0'+1)][j][k-1]+(grid[i][j]-'0'));
                if(k>0&&j>(key[k-1]-'0'))
                    dp[i][j][k] = min(dp[i][j][k],dp[i][j-(key[k-1]-'0'+1)][k-1]+(grid[i][j]-'0'));
            }
    for(int i = 0; i<=key.length(); i++)
        ans = min(ans,dp[y-1][x-1][i]);
    cout << ans << endl;
}