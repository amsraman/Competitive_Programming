#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;

using namespace std;

int k, pa, pb, p, q, dp[1000][1000];

int add(int a, int b)
{
    return (a+b)%MOD;
}

int mul(int a, int b)
{
    return (ll(a)*ll(b))%MOD;
}

int pow(int a, int b)
{
    int ret = 1;
    while(b)
    {
        if(b&1)
            ret = mul(ret,a);
        a = mul(a,a), b>>=1;
    }
    return ret;
}

int f(int a, int b)
{
    if(dp[a][b]!=-1)
        return dp[a][b];
    if(a>=k)
        return a;
    if(a+b>=k)
        return add(add(a,b),mul(p,pow(q,MOD-2)));
    dp[a][b] = add(mul(p,f(a,b+1)),mul(q,f(a+b,b)));
    return dp[a][b];
}

int main()
{
    cin >> k >> pa >> pb;
    p = mul(pa,pow(add(pa,pb),MOD-2));
    q = (MOD+1-p)%MOD;
    memset(dp,-1,sizeof(dp));
    cout << f(0,1) << endl;
}