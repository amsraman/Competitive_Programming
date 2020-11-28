#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, m;
ll s[100000], mx;

bool ok(ll k)
{
    int num = 0;
    ll cur = 0;
    for(int i = 0; i<n; i++)
    {
        cur+=s[i];
        if(cur>k)
            num++, cur = s[i];
    }
    num++;
    return (num<=m);
}

int main()
{
    freopen("verybest.in","r",stdin);
    freopen("verybest.out","w",stdout);
    cin >> n >> m;
    for(int i = 0; i<n; i++)
        cin >> s[i];
    for(int i = 0; i<n; i++)
        mx = max(mx,s[i]);
    ll l = mx, g = 1e14;
    while(l<g)
    {
        ll mid = (l+g)/2;
        if(ok(mid))
            g = mid;
        else
            l = mid+1;
    }
    cout << g << endl;
}
