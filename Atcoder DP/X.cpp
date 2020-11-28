#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n;
ll dp[20001], ans;
array<int,3> blocks[1000];

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> blocks[i][1] >> blocks[i][0] >> blocks[i][2];
    for(int i = 0; i<n; i++)
        blocks[i][0]+=blocks[i][1];
    sort(blocks,blocks+n);
    for(int i = 0; i<=2e4; i++)
        dp[i] = -1e12;
    dp[0] = 0;
    for(int i = 0; i<n; i++)
        for(int j = blocks[i][0]-blocks[i][1]; j>=0; j--)
            if(j+blocks[i][1]<=2e4)
                dp[j+blocks[i][1]] = max(dp[j+blocks[i][1]],dp[j]+blocks[i][2]);
    for(int i = 0; i<=2e4; i++)
        ans = max(ans,dp[i]);
    cout << ans << endl;
}
