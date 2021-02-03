#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;

using namespace std;

int k, a[(1<<18)], fact[(1<<18)+1], invfact[(1<<18)+1], ans;

int mul(int x, int y)
{
    return ((ll)x*y)%MOD;
}

int exp(int x, int y)
{
    int ret = 1;
    while(y)
    {
        if(y&1)
            ret = mul(ret,x);
        x = mul(x,x), y>>=1;
    }
    return ret;
}

int binom(int x, int y)
{
    if(y>x||x<0)
        return 0;
    return mul(fact[x],mul(invfact[y],invfact[x-y]));
}

int trinom(int x, int y, int z)
{
    if(y+z>x||x<0||y<0||z<0)
        return 0;
    return mul(fact[x],mul(mul(invfact[y],invfact[z]),invfact[x-y-z]));
}

int main()
{
    cin >> k;
    for(int i = 0; i<(1<<k); i++)
        cin >> a[i];
    reverse(a,a+(1<<k));
    fact[0] = invfact[0] = 1;
    for(int i = 1; i<=(1<<18); i++)
        fact[i] = mul(fact[i-1],i), invfact[i] = exp(fact[i],MOD-2);
    for(int r = 0; r<k; r++)
    {
        int tot = 0, cur = 0;
        for(int i = 0; i<(1<<k); i++)
            cur = (cur+mul(a[i],binom(i-(1<<r),(1<<r)-1)))%MOD;
        for(int i = 0; i<(1<<k); i++)
            cur = (cur+MOD-mul(a[i],binom(i-(1<<r),(1<<r)-1)))%MOD, tot = (tot+mul(mul(a[i],binom(i,(1<<r)-1)),cur))%MOD;
        ans = (ans+mul(tot,exp(trinom((1<<k)-1,(1<<r)-1,(1<<r)),MOD-2)))%MOD;
    }
    cout << ans << endl;
}