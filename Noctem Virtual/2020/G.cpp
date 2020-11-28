#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n;
ll m[4000], dp[4000], ans;

int main()
{
    freopen("spring.in","r",stdin);
    freopen("spring.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> m[i];
    for(int i = 0; i<n; i++)
    {
        ll cur = 0;
        for(int j = 0; j<i; j++)
            if(m[j]<=m[i])
                cur = max(cur,dp[j]);
        dp[i] = cur+m[i];
        ans = max(ans,dp[i]);
    }
    cout << ans << endl;
}
