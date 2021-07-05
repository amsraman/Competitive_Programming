#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int l, p, t, q, par[30000], dsu_link[30000], dsu_sz[30000], sz[30000], nxt[30000], in[30000], out[30000], seg[(1<<16)], lazy[(1<<16)];
pair<int,int> edges[100000];
vector<int> g[30000];
bool extra[100000];

int f(int v)
{
    return (v==dsu_link[v] ? v : dsu_link[v] = f(dsu_link[v]));
}

void unite(int u, int v)
{
    u = f(u), v = f(v);
    if(dsu_sz[u]<dsu_sz[v])
        swap(u,v);
    dsu_link[v] = u, dsu_sz[u]+=dsu_sz[v];
}

void app(int pos, int c, int len)
{
    seg[pos] = len*(c-1);
    lazy[pos] = c;
}
 
void psh(int pos, int s, int mid, int e)
{
    app(2*pos+1,lazy[pos],mid-s+1);
    app(2*pos+2,lazy[pos],e-mid);
    lazy[pos] = 0;
}
 
int qry(int a, int b, int s = 0, int e = l-1, int pos = 0)
{
    if((a==s)&&(b==e))
        return seg[pos];
    int mid = (s+e)/2;
    if(lazy[pos]!=0)
        psh(pos,s,mid,e);
    if(b<=mid)
        return qry(a,b,s,mid,2*pos+1);
    if(a>mid)
        return qry(a,b,mid+1,e,2*pos+2);
    return qry(a,mid,s,mid,2*pos+1)+qry(mid+1,b,mid+1,e,2*pos+2);
}
 
void upd(int a, int b, int c, int s = 0, int e = l-1, int pos = 0)
{
    if((a==s)&&(b==e))
    {
        app(pos,c,e-s+1);
        return;
    }
    int mid = (s+e)/2;
    if(lazy[pos]!=0)
        psh(pos,s,mid,e);
    if(a<=mid)
        upd(a,min(b,mid),c,s,mid,2*pos+1);
    if(b>mid)
        upd(max(a,mid+1),b,c,mid+1,e,2*pos+2);
    seg[pos] = seg[2*pos+1]+seg[2*pos+2];
}

void dfs_sz(int v = 0) 
{
    sz[v] = 1;
    for(int &u: g[v]) 
    {
        if(u == par[v])
            continue;
        par[u] = v, dfs_sz(u), sz[v] += sz[u];
        if(sz[u] > sz[g[v][0]])
            swap(u, g[v][0]);
    }
}

void dfs_hld(int v = 0) 
{
    in[v] = t++;
    for(int u: g[v])
        if(u != par[v])
            nxt[u] = (u == g[v][0] ? nxt[v] : u), dfs_hld(u);
    out[v] = t;
}

int path_qry(int u, int v)
{
    int ret = 0;
    while(nxt[u]!=nxt[v])
    {
        if(in[u]<in[v])
            swap(u,v);
        ret+=qry(in[nxt[u]],in[u]);
        u = par[nxt[u]];
    }
    if(in[u]>in[v])
        swap(u,v);
    return (u==v?ret:ret+qry(in[u]+1,in[v]));
}

void path_upd(int u, int v)
{
    while(nxt[u]!=nxt[v])
    {
        if(in[u]<in[v])
            swap(u,v);
        upd(in[nxt[u]],in[u],1);
        u = par[nxt[u]];
    }
    if(in[u]>in[v])
        swap(u,v);
    upd(in[u]+1,in[v],1);
}

int main()
{
    cin >> l >> p;
    for(int i = 0; i<l; i++)
        dsu_link[i] = i, dsu_sz[i] = 1;
    for(int i = 0; i<p; i++)
    {
        cin >> edges[i].f >> edges[i].s;
        if(f(edges[i].f-1)!=f(edges[i].s-1))
            unite(edges[i].f-1,edges[i].s-1), g[edges[i].f-1].push_back(edges[i].s-1), g[edges[i].s-1].push_back(edges[i].f-1);
        else
            extra[i] = true;
    }
    upd(1,l-1,2), dfs_sz(), dfs_hld();
    for(int i = 0; i<p; i++)
        if(extra[i])
            path_upd(edges[i].f-1,edges[i].s-1);
    cin >> q;
    for(int i = 0, c, l1, l2; i<q; i++)
    {
        cin >> c >> l1 >> l2;
        if(c==0)
            path_upd(l1-1,l2-1);
        else
            cout << path_qry(l1-1,l2-1) << endl;
    }
}