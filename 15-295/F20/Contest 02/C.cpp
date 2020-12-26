#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

ll n, m, a[100000], b[100000];

ll f(ll x)
{
    ll ret = 0;
    for(int i = 0; i<n; i++)
        ret+=max(0LL,x-a[i]);
    for(int i = 0; i<m; i++)
        ret+=max(0LL,b[i]-x);
    return ret;
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    for(int i = 0; i<m; i++)
        cin >> b[i];
    ll lb = 0, ub = 1e14;
    while(lb<ub)
    {
        ll m1 = lb+(ub-lb)/3, m2 = ub-(ub-lb)/3;
        if(f(m1)>f(m2))
            lb = m1+1;
        else
            ub = m2-1;
    }
    cout << f(ub) << endl;
}