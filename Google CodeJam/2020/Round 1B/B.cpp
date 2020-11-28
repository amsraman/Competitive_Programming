#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, a, b, p1, p2, lxb, uxb, lyb, uyb, mx = 1000000000;
bool found;

bool qry(int x, int y)
{
    string res;
    cout << x << " " << y << endl;
    cin >> res;
    if(res=="CENTER")
        found = true;
    return (res!="MISS");
}

void find_point()
{
    for(p1 = -mx; p1<=mx; p1+=(mx/4))
        for(p2 = -mx; p2<=mx; p2+=(mx/4))
            if(qry(p1,p2))
                return;
}

void solve()
{
    found = false;
    find_point();
    if(found) return;
    int l = -mx, g = p1;
    while(l<g)
    {
        int mid = l+(g-l)/2;
        if(qry(mid,p2)) g = mid;
        else l = mid+1;
        if(found) return;
    }
    lxb = g, l = p1, g = mx;
    while(l<g)
    {
        int mid = g-(g-l)/2;
        if(qry(mid,p2)) l = mid;
        else g = mid-1;
        if(found) return;
    }
    uxb = g, l = -mx, g = p2;
    while(l<g)
    {
        int mid = l+(g-l)/2;
        if(qry(p1,mid)) g = mid;
        else l = mid+1;
        if(found) return;
    }
    lyb = g, l = p2, g = mx;
    while(l<g)
    {
        int mid = g-(g-l)/2;
        if(qry(p1,mid)) l = mid;
        else g = mid-1;
        if(found) return;
    }
    uyb = g;
    qry((lxb+uxb)/2,(lyb+uyb)/2);
}

int main()
{
    cin >> t >> a >> b;
    while(t--)
        solve();
}
