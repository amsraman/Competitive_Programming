#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, b, s[20][20], num[(1<<20)], dp[(1<<20)];
vector<pair<int,int>> bonus[20];

int main()
{
    freopen("dec.in","r",stdin);
    freopen("dec.out","w",stdout);
    cin >> n >> b;
    for(int i = 0, k, p, a; i<b; i++)
    {
        cin >> k >> p >> a;
        bonus[k-1].push_back({p,a});
    }
    for(int i = 0; i<n; i++)
        sort(bonus[i].begin(),bonus[i].end());
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> s[i][j];
    for(int i = 1; i<(1<<n); i++)
        num[i] = __builtin_popcount(i);
    for(int i = 1; i<(1<<n); i++)
    {
        for(int j = 0; j<n; j++)
            if((1<<j)&i)
                dp[i] = max(dp[i],dp[i^(1<<j)]+s[j][num[i]-1]);
        for(int j = 0; j<bonus[num[i]-1].size(); j++)
            if(dp[i]>=bonus[num[i]-1][j].f)
                dp[i]+=bonus[num[i]-1][j].s;
    }
    cout << dp[(1<<n)-1] << endl;
}
