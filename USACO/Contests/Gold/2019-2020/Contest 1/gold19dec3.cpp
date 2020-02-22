#include <bits/stdc++.h>

using namespace std;

int n, m, k, d[26][26], pre[100001][26], dp[100001][26], mindp[100001];
string s;

int main()
{
    freopen("cowmbat.in","r",stdin);
    freopen("cowmbat.out","w",stdout);
    cin >> n >> m >> k >> s;
    for(int i = 0; i<m; i++)
        for(int j = 0; j<m; j++)
            cin >> d[i][j];
    for(int k = 0; k<m; k++)
        for(int i = 0; i<m; i++)
            for(int j = 0; j<m; j++)
                d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
    for(int i = 1; i<=n; i++)
        for(int j = 0; j<m; j++)
            pre[i][j] = pre[i-1][j]+d[(s[i-1]-'a')][j];
    memset(dp,0x3f3f3f3f,sizeof(dp));
    memset(mindp,0x3f3f3f3f,sizeof(mindp));
    mindp[0] = 0;
    for(int i = 1; i<=n; i++)
        for(int j = 0; j<m; j++)
        {
            dp[i][j] = dp[i-1][j]+d[(s[i-1]-'a')][j];
            if(i>=k)
                dp[i][j] = min(dp[i][j],mindp[i-k]+pre[i][j]-pre[i-k][j]);
            mindp[i] = min(mindp[i],dp[i][j]);
        }
    cout << mindp[n] << endl;
}
