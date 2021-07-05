#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int t, m, p[95];
ll n[95], sum, ans;
map<ll,ll> pc;
bool doable[50001];

bool ok(ll x)
{
    ll ox = x;
    bool good = true;
    vector<pair<ll,ll>> fact;
    for(ll i = 2; i*i<=x&&i<500; i++)
        if(x%i==0)
        {
            ll exp = 0;
            while(x%i==0)
                ++exp, x/=i;
            fact.push_back({i,exp});
            good&=(exp<=pc[i]);
        }
    if(x!=1)
        fact.push_back({x,1}), good&=(1<=pc[x]);
    for(pair<ll,ll> i: fact)
        ox+=i.f*i.s;
    return (ox==sum&&good);
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> m;
        for(int i = 0; i<m; i++)
            cin >> p[i] >> n[i];
        for(int i = 0; i<m; i++)
            pc[p[i]] = n[i];
        sum = 0;
        for(int i = 0; i<m; i++)
            sum+=p[i]*n[i];
        for(int i = 0; i<=50000; i++)
            doable[i] = false;
        doable[0] = true;
        for(int i = 0; i<m; i++)
        {
            ll lg = 0;
            for(ll j = sum; j>0; j/=(ll)p[i])
                ++lg;
            for(int j = 0; j<min(lg+1,n[i]); j++)
                for(int k = 50000; k>=0; k--)
                    if(doable[k]&&k+p[i]<=50000)
                        doable[k+p[i]] = true;
        }
        ans = 0;
        for(int i = 1; i<=50000; i++)
            if(doable[i]&&ok(sum-i))
                ans = max(ans,sum-i);
        cout << "Case #" << _ << ": " << ans << endl;
        pc.clear();
    }
}