#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, m, k, s, ap, bp, cp, dp, aq, bq, cq, dq, p[1000010], q[1000010];

int add(int x, int y, int md)
{
    return (x+y)%md;
}

int mul(int x, int y, int md)
{
    return (ll(x)*ll(y))%md;
}

bool ok(ll x)
{
    int pos, cur = 0, num;
    ll cost, l, r;
    for(int i = 0; i<n; i++)
    {
        pos = p[i], cost = num = 0;
        if(q[cur]<pos)
            l = pos-q[cur], r = 0;
        else
            l = 0, r = q[cur]-pos;
        while((cur+num<m)&&(cost+2*min(l,r)+max(l,r)+s<=x))
            cost+=s, num++, r = max(0,q[cur+num]-p[i]);
        cur+=num;
        if(cur==m)
            return true;
    }
    return false;
}

int main()
{
    freopen("dislodging_logs_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> m >> k >> s;
        for(int i = 0; i<k; i++)
            cin >> p[i];
        cin >> ap >> bp >> cp >> dp;
        for(int i = 0; i<k; i++)
            cin >> q[i];
        cin >> aq >> bq >> cq >> dq;
        for(int i = k; i<n; i++)
            p[i] = 1+add(add(mul(ap,p[i-2],dp),mul(bp,p[i-1],dp),dp),cp,dp);
        for(int i = k; i<m; i++)
            q[i] = 1+add(add(mul(aq,q[i-2],dq),mul(bq,q[i-1],dq),dq),cq,dq);
        sort(p,p+n);
        sort(q,q+m);
        ll l = 0, g = 0xfffffffffffffff;
        while(l<g)
        {
            ll mid = (l+g)/2;
            if(ok(mid))
                g = mid;
            else
                l = mid+1;
        }
        cout << "Case #" << _ << ": " << g << endl;
    }
}
