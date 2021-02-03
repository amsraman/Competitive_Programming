#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, m, a[300000];

bool f(ll x)
{
    int cm = a[0];
    if(x>=m-a[0])
        cm = 0;
    for(int i = 1; i<n; i++)
    {
        if(x>=(cm-a[i]+m)%m)
            continue;
        if(a[i]>cm)
            cm = a[i];
        else
            return false;
    }
    return true;
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    ll lb = 0, ub = 1e14;
    while(lb<ub)
    {
        ll mid = (lb+ub)/2;
        if(f(mid))
            ub = mid;
        else
            lb = mid+1;
    }
    cout << ub << endl;
}