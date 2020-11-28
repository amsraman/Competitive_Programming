#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;

using namespace std;

ll n, ans, nm;
vector<ll> fact;

ll add(ll x, ll y)
{
    return (x%MOD+y%MOD+MOD)%MOD;
}

ll mul(ll x, ll y)
{
    return (x%MOD*y%MOD)%MOD;
}

ll exp(ll x, ll y)
{
    ll ret = 1;
    while(y!=0)
    {
        if(y%2==1)
            ret = mul(ret,x);
        x = mul(x,x), y/=2;
    }
    return ret;
}

void init(ll x)
{
    for(ll i = 2; i*i<=x; i++)
    {
        if(x%i==0)
            fact.push_back(i);
        while(x%i==0)
            x/=i;
    }
    if(x!=1)
        fact.push_back(x);
}

void gen(ll num, ll ml, int ind, bool in)
{
    if(in||(ind==0))
        ans = add(ans,mul(exp(2,n/num),mul(num,ml))), nm++;
    if((ind<fact.size()-1)&&(n%(num*fact[ind+1])==0))
        gen(num,ml,ind+1,0);
    if(!in&&(n%(num*fact[ind])==0))
        gen(num*fact[ind],mul(ml,add(1,-exp(fact[ind]%MOD,MOD-2))),ind,1);
    else if(n%(num*fact[ind])==0)
        gen(num*fact[ind],ml,ind,1);
}

int main()
{
    freopen("gymnasts.in","r",stdin);
    freopen("gymnasts.out","w",stdout);
    cin >> n;
    init(n), gen(1,1,0,0);
    ans = add(add(ans,-n),add(2,-exp(2,n)));
    cout << ans << endl;
}
