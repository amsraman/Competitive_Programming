#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

int n;
ld a[300000], v, u;

bool ok(ld x)
{
    ld tot = 0, num = 0;
    for(int i = 0; i<n; i++)
        if(a[i]>v*x)
            tot+=a[i], num++;
    return ((u+num*v)*x>=tot);
}

int main()
{
    cin >> n >> v >> u;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    ld lb = 0, ub = 1e18, prevlb, prevub;
    while(lb!=ub)
    {
        if(lb==prevlb && ub==prevub)
            break;
        prevlb = lb, prevub = ub;
        ld mid = (lb+ub)/2;
        if(ok(mid/u))
            ub = mid;
        else
            lb = mid;
    }
    cout << fixed << setprecision(7) << ub << endl;
}