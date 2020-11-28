#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

int t, n;
ll ans;
pair<ll,ll> points[100000];

ll ycount(int x)
{
    ll ret = 0;
    for(ll i = 0; i<n; i++)
        ret+=abs(x+i-points[i].f);
    return ret;
}

ll xcount(ll x)
{
    ll ret = 0;
    for(int i = 0; i<n; i++)
        ret+=abs(x-points[i].s);
    return ret;
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> points[i].f >> points[i].s;
        sort(points,points+n);
        ll lb = -5e9, ub = 5e9;
        while(lb<ub)
        {
            ll m1 = lb+(ub-lb)/3, m2 = ub-(ub-lb)/3;
            if(ycount(m1)>ycount(m2))
                lb = m1+1;
            else
                ub = m2-1;
        }
        ans = ycount(ub);
        lb = -5e9, ub = 5e9;
        while(lb<ub)
        {
            ll m1 = lb+(ub-lb)/3, m2 = ub-(ub-lb)/3;
            if(xcount(m1)>xcount(m2))
                lb = m1+1;
            else
                ub = m2-1;
        }
        ans+=xcount(ub);
        cout << "Case #" << _ << ": " << ans << endl;
    }
}
