#include <bits/stdc++.h>

using namespace std;

int t, n, x, y, dp[1000][2];
string s;

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> x >> y >> s;
        n = s.length(), dp[0][0] = (s[0]=='J'?0x3f3f3f3f:0), dp[0][1] = (s[0]=='C'?0x3f3f3f3f:0);
        for(int i = 1; i<n; i++)
        {
            if(s[i]=='C')
                dp[i][0] = min(dp[i-1][0],dp[i-1][1]+y), dp[i][1] = 0x3f3f3f3f;
            if(s[i]=='J')
                dp[i][1] = min(dp[i-1][1],dp[i-1][0]+x), dp[i][0] = 0x3f3f3f3f;
            if(s[i]=='?')
                dp[i][0] = min(dp[i-1][0],dp[i-1][1]+y), dp[i][1] = min(dp[i-1][1],dp[i-1][0]+x);
        }
        cout << "Case #" << _ << ": " << min(dp[n-1][0],dp[n-1][1]) << endl;
    }
}