#include <bits/stdc++.h>
typedef long long ll;
#define MOD 1000000007
#define f first
#define s second

using namespace std;

int h, w, n, fact[200001], invfact[200001], dp[3000], ans;
pair<int,int> walls[3000];

int add(int a, int b)
{
    return (a+b)%MOD;
}

int mul(int a, int b)
{
    return ((ll)a*b)%MOD;
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

int ncr(int a, int b)
{
    return mul(fact[a],mul(invfact[a-b],invfact[b]));
}

int main()
{
    cin >> h >> w >> n;
    for(int i = 0; i<n; i++)
        cin >> walls[i].f >> walls[i].s;
    sort(walls,walls+n);
    fact[0] = invfact[0] = 1;
    for(int i = 1; i<=2e5; i++)
        fact[i] = mul(i,fact[i-1]), invfact[i] = pow(fact[i],MOD-2);
    for(int i = 0; i<n; i++)
        dp[i] = ncr(walls[i].f+walls[i].s-2,walls[i].f-1);
    ans = ncr(h+w-2,h-1);
    for(int i = 0; i<n; i++)
        for(int j = 0; j<i; j++)
            if(walls[j].f<=walls[i].f && walls[j].s<=walls[i].s)
                dp[i] = add(dp[i],MOD-mul(dp[j],ncr(walls[i].f+walls[i].s-walls[j].f-walls[j].s,walls[i].f-walls[j].f)));
    for(int i = 0; i<n; i++)
        ans = add(ans,MOD-mul(dp[i],ncr(h+w-walls[i].f-walls[i].s,h-walls[i].f)));
    cout << ans << endl;
}
