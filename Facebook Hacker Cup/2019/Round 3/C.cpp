#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;

using namespace std;

int t, n, k, a, b, c, p[6000], num, ans;

int add(int x, int y)
{
    return (x+y)%MOD;
}

int mul(int x, int y)
{
    return (ll(x)*ll(y))%MOD;
}

int exp(int x, int y)
{
    int ret = 1;
    while(y>0)
    {
        if(y&1)
            ret = mul(ret,x);
        x = mul(x,x), y/=2;
    }
    return ret;
}

int lca(int x, int y)
{
    vector<int> p1, p2;
    while(x!=0)
        p1.push_back(x), x = p[x];
    while(y!=0)
        p2.push_back(y), y = p[y];
    p1.push_back(0), p2.push_back(0);
    int ind1 = p1.size()-1, ind2 = p2.size()-1;
    while(p1[ind1]==p2[ind2])
        ind1--, ind2--;
    return p1[ind1+1];
}

int ev(int x, int sub)
{
    int ret = 0;
    for(int i = 0; x!=0; x = p[x], i++)
    {
        ret = add(ret,mul(i+1,exp(n-i-sub,k)));
        if(p[x]!=0)
            ret = add(ret,mul(i+1,MOD-exp(n-i-sub-1,k)));
    }
    return mul(ret,exp(exp(n-1,k),MOD-2));
}

int main()
{
    freopen("renovations_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> k >> a >> b;
        a--, b--;
        for(int i = 1; i<n; i++)
        {
            cin >> p[i];
            p[i]--;
        }
        ans = add(ev(a,1),ev(b,1)), c = lca(a,b), num = 0;
        while(a!=c)
            num++, a = p[a];
        while(b!=c)
            num++, b = p[b];
        ans = add(ans,mul(2,MOD-ev(c,num+1)));
        cout << "Case #" << _ << ": " << ans << endl;
    }
}
