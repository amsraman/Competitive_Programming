#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, sz = 1, cur;
ll c, h[200000], dp[200000];

struct L
{
    ll m, b;
    double sect(const L &L2)
    {
        return (double)(L2.b-b)/(m-L2.m);
    }
} hull[200000];

int main()
{
    cin >> n >> c;
    for(int i = 0; i<n; i++)
        cin >> h[i];
    dp[0] = 0, hull[0] = {-2*h[0],dp[0]+h[0]*h[0]};
    for(int i = 1; i<n; i++)
    {
        while(cur<sz-1&&h[i]>hull[cur].sect(hull[cur+1]))
            ++cur;
        dp[i] = hull[cur].m*h[i]+hull[cur].b+h[i]*h[i]+c;
        L nxt = {-2*h[i],dp[i]+h[i]*h[i]};
        while(sz>1&&nxt.sect(hull[sz-1])<nxt.sect(hull[sz-2]))
            --sz;
        cur = min(cur,sz-1);
        hull[sz++] = nxt;
    }
    cout << dp[n-1] << endl;
}
