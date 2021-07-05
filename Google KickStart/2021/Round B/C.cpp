#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t;
ll z, ans;

bool isPrime(ll x)
{
    if(x<2)
        return false;
    for(ll i = 2; i*i<=x; i++)
        if(x%i==0)
            return false;
    return true;
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> z;
        ll lb = 0, ub = 1e9;
        while(lb<ub)
        {
            ll mid = (lb+ub+1)/2;
            if(mid*mid<=z)
                lb = mid;
            else
                ub = mid-1;
        }
        ll p1 = ub-1, p2 = ub;
        ans = 0;
        while(p1>1&&!isPrime(p1))
            --p1;
        while(!isPrime(p2))
            ++p2;
        ll p0 = p1-1, p3 = p2+1;
        while(p0>1&&!isPrime(p0))
            --p0;
        while(!isPrime(p3))
            ++p3;
        if(p1>1&&p1*p2<=z)
            ans = p1*p2;
        if(p0>1&&p0*p1<=z)
            ans = max(ans,p0*p1);
        if(p2*p3<=z)
            ans = max(ans,p2*p3);
        cout << "Case #" << _ << ": " << ans << endl;
    }
}