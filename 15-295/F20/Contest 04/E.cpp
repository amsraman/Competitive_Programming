#include <bits/stdc++.h>

using namespace std;

int t, n, p, q, a[2000], nxt1[2000], nxt2[2000], dp[2001][2001];

bool ok(int x)
{
    int p1 = n-1, p2 = n-1;
    for(int i = n-1; i>=0; i--)
    {
        while(a[p1]-a[i]>=x)
            p1--;
        while(a[p2]-a[i]>=2*x)
            p2--;
        nxt1[i] = p1, nxt2[i] = p2;
    }
    for(int i = 0; i<=p; i++)
        for(int j = 0; j<=q; j++)
        {
            dp[i][j] = 0;
            if(i>0)
                dp[i][j] = 1+nxt1[dp[i-1][j]];
            if(j>0)
                dp[i][j] = max(dp[i][j],1+nxt2[dp[i][j-1]]);
            if(dp[i][j]==n)
                return true;
        }
    return false;
}

int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n >> p >> q;
        for(int i = 0; i<n; i++)
            cin >> a[i];
        p = min(p,n), q = min(q,n);
        sort(a,a+n);
        int lb = 1, ub = 2e9;
        while(lb<ub)
        {
            int mid = (lb+ub)/2;
            if(ok(mid))
                ub = mid;
            else
                lb = mid+1;
        }
        cout << ub << endl;
    }
}