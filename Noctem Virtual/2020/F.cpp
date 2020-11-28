#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, p[1000000], bit[1000000], best[1000000], ans = 0;
pair<int,int> pi[1000000];

int qry(int x)
{
    int ret = 0;
    for(x++; x>0; x-=(x&(-x)))
        ret+=bit[x-1];
    return ret;
}

void upd(int x, int k)
{
    for(x++; x<=n; x+=(x&(-x)))
        bit[x-1]+=k;
}

int main()
{
    freopen("stonks.in","r",stdin);
    freopen("stonks.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> p[i];
    for(int i = 0; i<n; i++)
        upd(i,1);
    for(int i = 0; i<n; i++)
        pi[i] = {p[i],i};
    sort(pi,pi+n);
    for(int i = 0; i<n; i++)
    {
        best[pi[i].s] = n-qry(pi[i].s)-i;
        if(best[pi[i].s]>best[ans])
            ans = pi[i].s;
        upd(pi[i].s,-1);
    }
    cout << ans+1 << endl;
}
