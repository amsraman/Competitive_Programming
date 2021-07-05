#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int t, n, q, tc;
ll seg[(1<<19)], lazy[(1<<19)], ans[100000];
pair<int,int> in[50000];
vector<int> g[50000];
vector<pair<int,pair<int,int>>> qrs;
vector<pair<int,pair<pair<int,int>,ll>>> upds;

void dfs(int x, int p)
{
    in[x].f = tc++;
    for(int i: g[x])
        if(i!=p)
            dfs(i,x);
    in[x].s = tc-1;
}

ll pgcd(ll x, ll y)
{
    if(min(x,y)==0)
        return max(x,y);
    return __gcd(x,y);
}

void app(int pos, ll c)
{
    seg[pos] = pgcd(seg[pos],c);
    lazy[pos] = pgcd(lazy[pos],c);
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
    return pgcd(qry(a,mid,s,mid,2*l+1),qry(mid+1,b,mid+1,e,2*l+2));
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
    seg[l] = pgcd(seg[2*l+1],seg[2*l+2]);
}

void doit(int x, int y, ll num)
{
    if(in[x].f>in[y].f)
        swap(x,y);
    upd(in[y].f,in[y].s,num);
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        for(int i = 0; i<(1<<19); i++)
            seg[i] = lazy[i] = 0;
        tc = 0;
        cin >> n >> q;
        for(ll i = 0, x, y, l, a; i<n-1; i++)
        {
            cin >> x >> y >> l >> a;
            g[x-1].push_back(y-1);
            g[y-1].push_back(x-1);
            upds.push_back({l,{{x-1,y-1},a}});
        }
        dfs(0,0);
        for(int i = 0, c, w; i<q; i++)
        {
            cin >> c >> w;
            qrs.push_back({w,{c-1,i}});
        }
        sort(upds.begin(),upds.end());
        sort(qrs.begin(),qrs.end());
        for(int i = 0, j = 0; i<q; i++)
        {
            while(j<n-1&&upds[j].f<=qrs[i].f)
                doit(upds[j].s.f.f,upds[j].s.f.s,upds[j].s.s), j++;
            ans[qrs[i].s.s] = qry(in[qrs[i].s.f].f,in[qrs[i].s.f].f);
        }
        cout << "Case #" << _ << ": ";
        for(int i = 0; i<q; i++)
            cout << ans[i] << " ";
        cout << endl;
        for(int i = 0; i<n; i++)
            g[i].clear();
        upds.clear(), qrs.clear();
    }
}