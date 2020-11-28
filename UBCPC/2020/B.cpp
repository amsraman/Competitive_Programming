#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int k, n, w[100000];

bool ok(ll x)
{
    ll cur = 0;
    int ret = 1;
    for(int i = 0; i<n; i++)
    {
        cur+=w[i];
        if(cur>x)
            ret++, cur = w[i];
    }
    return (ret<=k);
}

int main()
{
    cin >> n >> k;
    for(int i = 0; i<n; i++)
        cin >> w[i];
    ll lb = 0, ub = 1e14;
    for(int i = 0; i<n; i++)
        lb = max(lb,ll(w[i]));
    while(lb<ub)
    {
        ll mid = (lb+ub)/2;
        if(ok(mid))
            ub = mid;
        else
            lb = mid+1;
    }
    cout << ub << endl;
}
