#include <bits/stdc++.h>
#define INF 0xfffffffffffffff
typedef long long ll;

using namespace std;

int t, n, m, a, b, par[1000000];
ll c[1000000], seg[(1<<21)], dp[1000000];
vector<int> g[1000000], path;

ll qmin(int low, int high)
{
    low+=(1<<20), high+=(1<<20);
    ll ret = INF;
    while(low<=high)
    {
        if(high%2==0) ret = min(ret,seg[high]), high--;
        if(low%2==1) ret = min(ret,seg[low]), low++;
        low/=2, high/=2;
    }
    return ret;
}

void upd(int k, ll x)
{
    k+=(1<<20), seg[k] = min(seg[k],x);
    while(k>1)
    {
        k/=2;
        seg[k] = min(seg[2*k],seg[2*k+1]);
    }
}

void dfs(int x, int p)
{
    //cout << x << " " << p << endl;
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=p)
            par[g[x][i]] = x, dfs(g[x][i],x);
}

void dfs2(int x, int lv, int d)
{
    if(c[x]!=0)
    {
        dp[x] = qmin(max(0,lv-m+d),lv)+c[x];
        if(lv-d>=0)
            upd(lv-d,dp[x]);
    }
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=par[x])
            dfs2(g[x][i],lv,d+1);
}

int main()
{
    freopen("running_on_fumes_chapter_2_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 0; _<t; _++)
    {
        cin >> n >> m >> a >> b;
        a--, b--;
        for(int i = 0, p; i<n; i++)
        {
            cin >> p >> c[i];
            if(i!=0)
                g[i].push_back(p-1), g[p-1].push_back(i);
        }
        par[a] = a, dfs(a,a);
        while(b!=a)
            path.push_back(b), b = par[b];
        reverse(path.begin(),path.end());
        for(int i = 0; i<(1<<21); i++)
            seg[i] = INF;
        upd(0,0);
        for(int i = 0; i<path.size()-1; i++)
        {
            for(int j = 0; j<g[path[i]].size(); j++)
                if((g[path[i]][j]!=path[i+1])&&(g[path[i]][j]!=par[path[i]]))
                    dfs2(g[path[i]][j],i+1,1);
            if(c[path[i]]!=0)
            {
                dp[path[i]] = qmin(max(0,i+1-m),i)+c[path[i]];
                upd(i+1,dp[path[i]]);
            }
        }
        ll ans = qmin(max(0,(int)path.size()-m),(int)path.size()-1);
        cout << "Case #" << _+1 << ": " << (ans==INF?-1:ans) << endl;
        for(int i = 0; i<n; i++)
            g[i].clear();
        path.clear();
    }
}
