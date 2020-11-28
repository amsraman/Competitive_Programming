#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

int n, m;
ll seg[(1<<19)], lazy[(1<<19)], score[200001], dp[200000], ans;
vector<pair<int,ll>> in[200000];

void app(int pos, ll c)
{
    seg[pos]+=c;
    lazy[pos]+=c;
}

void psh(int pos)
{
    app(2*pos+1,lazy[pos]);
    app(2*pos+2,lazy[pos]);
    lazy[pos] = 0;
}

ll qry(int a, int b, int s = 0, int e = n-1, int l = 0)
{
    if((a==s)&&(b==e))
        return seg[l];
    int mid = (s+e)/2;
    psh(l);
    if(b<=mid)
        return qry(a,b,s,mid,2*l+1);
    if(a>mid)
        return qry(a,b,mid+1,e,2*l+2);
    return max(qry(a,mid,s,mid,2*l+1),qry(mid+1,b,mid+1,e,2*l+2));
}

void upd(int a, int b, ll c, int s = 0, int e = n-1, int l = 0)
{
    if((a==s)&&(b==e))
    {
        app(l,c);
        return;
    }
    int mid = (s+e)/2;
    psh(l);
    if(a<=mid)
        upd(a,min(b,mid),c,s,mid,2*l+1);
    if(b>mid)
        upd(max(a,mid+1),b,c,mid+1,e,2*l+2);
    seg[l] = max(seg[2*l+1],seg[2*l+2]);
}

int main()
{
    cin >> n >> m;
    for(int i = 0, l, r, a; i<m; i++)
    {
        cin >> l >> r >> a;
        in[r-1].push_back({l-1,a});
        upd(l-1,r-1,-a);
        score[l-1]+=a, score[r]-=a;
    }
    for(int i = 1; i<n; i++)
        score[i]+=score[i-1];
    for(int i = 0; i<n; i++)
    {
        dp[i] = (i==0?0:max(0LL,qry(0,i-1)))+score[i];
        upd(i,i,dp[i]);
        for(pair<int,ll> x: in[i])
            upd(x.f,i,x.s);
        ans = max(ans,dp[i]);
    }
    cout << ans << endl;
}
