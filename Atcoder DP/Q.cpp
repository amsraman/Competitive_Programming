#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, h[200000], a[200000];
ll dp_seg[(1<<19)];

ll qry(int x)
{
    int lo = (1<<18), hi = x+(1<<18);
    ll ret = 0;
    while(lo<=hi)
    {
        if(hi%2==0) ret = max(ret,dp_seg[hi]), hi--;
        if(lo%2==1) ret = max(ret,dp_seg[lo]), lo++;
        lo/=2, hi/=2;
    }
    return ret;
}

void upd(int k, ll x)
{
    k+=(1<<18), dp_seg[k] = x;
    while(k>1)
        k/=2, dp_seg[k] = max(dp_seg[2*k],dp_seg[2*k+1]);
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> h[i];
    for(int i = 0; i<n; i++)
        cin >> a[i];
    for(int i = 0; i<n; i++)
        upd(h[i]-1,qry(h[i]-1)+a[i]);
    cout << qry(n-1) << endl;
}
