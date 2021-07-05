#include <bits/stdc++.h>
typedef long long ll;
#define MOD 998244353

using namespace std;

int n, p[200000], ps[200000], bit[200000], ans;

int add(int x, int y)
{
    return (x+y)%MOD;
}

int mul(int x, int y)
{
    return ((ll)x*y)%MOD;
}

int dvd(int x, int y)
{
    int cur = MOD-2;
    while(cur)
    {
        if(cur&1)
            x = mul(x,y);
        y = mul(y,y), cur>>=1;
    }
    return x;
}

int qry(int x)
{
    int ret = 0;
    for(x++; x>0; x-=(x&(-x)))
        ret+=bit[x-1];
    return ret;
}

void upd(int x)
{
    for(x++; x<=n; x+=(x&(-x)))
        ++bit[x-1];
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> p[i];
    for(int i = 0; i<n; i++)
        ++ps[i];
    for(int i = 0; i<n; i++)
        if(p[i]!=-1)
            --ps[p[i]-1];
    for(int i = 1; i<n; i++)
        ps[i]+=ps[i-1];
    for(int i = 0, blank = 0, fix = 0; i<n; i++)
    {
        if(p[i]==-1)
            ans = add(ans,add(dvd(blank,2),dvd(fix,ps[n-1]))), ++blank;
        else
            ans = add(ans,add(qry(n-1)-qry(p[i]-1),mul(blank,dvd(ps[n-1]-ps[p[i]-1],ps[n-1])))), upd(p[i]-1), fix = add(fix,ps[p[i]-1]);
    }
    cout << ans << endl;
}