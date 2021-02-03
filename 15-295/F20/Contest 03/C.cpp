#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

ll n;
pair<ll,ll> pos1, pos2, delta;
string s;

bool ok(ll x)
{
    pair<ll,ll> tmp = {pos2.f-pos1.f,pos2.s-pos1.s};
    tmp.f-=(x/n)*delta.f, tmp.s-=(x/n)*delta.s;
    for(int i = 0; i<x%n; i++)
    {
        if(s[i]=='L')
            tmp.f++;
        if(s[i]=='R')
            tmp.f--;
        if(s[i]=='U')
            tmp.s--;
        if(s[i]=='D')
            tmp.s++;
    }
    return (abs(tmp.f)+abs(tmp.s)<=x);
}

int main()
{
    cin >> pos1.f >> pos1.s >> pos2.f >> pos2.s >> n >> s;
    for(int i = 0; i<n; i++)
    {
        if(s[i]=='L')
            delta.f--;
        if(s[i]=='R')
            delta.f++;
        if(s[i]=='U')
            delta.s++;
        if(s[i]=='D')
            delta.s--;
    }
    ll lb = 0, ub = 1e15;
    while(lb<ub)
    {
        ll mid = (lb+ub)/2;
        if(ok(mid))
            ub = mid;
        else
            lb = mid+1;
    }
    cout << (ub==1e15?-1:ub) << endl;
}