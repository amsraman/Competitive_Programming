#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

ll n, x, y;
pair<ll,ll> dir[6] = {{-1,2},{-2,0},{-1,-2},{1,-2},{2,0},{1,2}};

ll f(ll x)
{
    return 3*x*(x+1);
}

int main()
{
    cin >> n;
    ll lo = 0, hi = 1e9;
    while(lo<hi)
    {
        ll mid = (lo+hi+1)/2;
        if(f(mid)>=n)
            hi = mid-1;
        else
            lo = mid;
    }
    if(f(lo)==n)
        cout << 2*lo << " " << 0 << endl;
    else if(f(lo+1)==n)
        cout << 2*lo+2 << " " << 0 << endl;
    else
    {
        n-=f(lo), x = 2*lo+2, y = 0;
        for(int i = 0; i<6; i++)
        {
            x+=dir[i].f*min(n,lo+1), y+=dir[i].s*min(n,lo+1);
            n-=min(n,lo+1);
        }
        cout << x << " " << y << endl;
    }
}