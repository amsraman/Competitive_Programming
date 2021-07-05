#include <bits/stdc++.h>
typedef long long ll;
#define INF 0xfffffffffffffff

using namespace std;

int n, k, r[1000];
ll ps[1000], dp[1000][7], ans = INF;

void solve(int lo, int hi, int lb, int ub, int ind)
{
    int mid = (lo+hi)/2, opt = lb;
    if(lb<mid)
        dp[mid][ind] = dp[lb][ind-1]+(dp[mid][0]-dp[lb][0])-(lb+1)*(ps[mid]-ps[lb]);
    for(int i = lb; i<=min(ub,mid-1); i++)
        if(dp[i][ind-1]+(dp[mid][0]-dp[i][0])-(ll)(i+1)*(ps[mid]-ps[i])<=dp[mid][ind])
            opt = i, dp[mid][ind] = dp[i][ind-1]+(dp[mid][0]-dp[i][0])-(ll)(i+1)*(ps[mid]-ps[i]);
    if(lo==hi)
        return;
    solve(lo,mid,lb,min(mid-1,opt),ind);
    solve(mid+1,hi,opt,min(hi-1,ub),ind);
}

int main()
{
    freopen("cbarn.in","r",stdin);
    freopen("cbarn.out","w",stdout);
    cin >> n >> k;
    for(int i = 0; i<n; i++)
        cin >> r[i];
    for(int i = 0; i<n; i++)
    {
        ps[0] = r[0];
        for(int j = 1; j<n; j++)
            ps[j] = ps[j-1]+r[j], dp[j][0] = dp[j-1][0]+(ll)j*r[j];
        for(int j = 1; j<k; j++)
            solve(0,n-1,0,n-1,j);
        for(int j = 0; j<n-1; j++)
            swap(r[j],r[j+1]);
        ans = min(ans,dp[n-1][k-1]);
    }
    cout << ans << endl;
}