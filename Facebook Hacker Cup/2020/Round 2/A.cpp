#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, k, as, bs, cs, ds, ax, bx, cx, dx, ay, by, cy, dy, s[1000000], x[1000000], y[1000000];
ll tots, totx, toty, u, d;

int add(int a, int b, int md)
{
    return (a+b)%md;
}

int mul(int a, int b, int md)
{
    return (ll(a)*ll(b))%md;
}

int main()
{
    freopen("capastaty_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> k;
        for(int i = 0; i<k; i++)
            cin >> s[i];
        cin >> as >> bs >> cs >> ds;
        for(int i = 0; i<k; i++)
            cin >> x[i];
        cin >> ax >> bx >> cx >> dx;
        for(int i = 0; i<k; i++)
            cin >> y[i];
        cin >> ay >> by >> cy >> dy;
        for(int i = k; i<n; i++)
        {
            s[i] = add(add(mul(as,s[i-2],ds),mul(bs,s[i-1],ds),ds),cs,ds);
            x[i] = add(add(mul(ax,x[i-2],dx),mul(bx,x[i-1],dx),dx),cx,dx);
            y[i] = add(add(mul(ay,y[i-2],dy),mul(by,y[i-1],dy),dy),cy,dy);
        }
        tots = totx = toty = 0;
        for(int i = 0; i<n; i++)
            tots+=s[i], totx+=x[i], toty+=y[i];
        cout << "Case #" << _ << ": ";
        if((tots>totx+toty)||(tots<totx))
            cout << -1 << endl;
        else
        {
            u = d = 0;
            for(int i = 0; i<n; i++)
            {
                if(s[i]>x[i]+y[i])
                    u+=(s[i]-x[i]-y[i]);
                if(s[i]<x[i])
                    d+=(x[i]-s[i]);
            }
            cout << max(u,d) << endl;
        }
    }
}
