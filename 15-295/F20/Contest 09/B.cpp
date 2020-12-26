#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;

using namespace std;

int k, c[1000], dp[1001][1001], fact[10001], invfact[10001];

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
        a = mul(a,a), b/=2;
    }
    return ret;
}

int main()
{
    cin >> k;
    for(int i = 0; i<k; i++)
        cin >> c[i];
    fact[0] = invfact[0] = 1;
    for(int i = 1; i<=10000; i++)
        fact[i] = mul(fact[i-1],i), invfact[i] = pow(fact[i],MOD-2);
    reverse(c,c+k);
    for(int i = 1; i<k; i++)
        c[i]+=c[i-1];
    dp[0][0] = 1;
    for(int i = 0; i<c[k-1]; i++)
        for(int j = 0; j<min(k,i+1); j++)
            dp[i+1][j+1] = add(mul(dp[i][j+1],(c[j]-i)),dp[i][j]);
    dp[c[k-1]][k] = mul(dp[c[k-1]][k],invfact[c[0]-1]);
    for(int i = 1; i<k; i++)
        dp[c[k-1]][k] = mul(dp[c[k-1]][k],invfact[c[i]-c[i-1]-1]);
    cout << dp[c[k-1]][k] << endl;
}