#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, t[100000], x, y, a[100000], b[100000], c[100000], depth[100000], ct;
pair<int,int> range[100000];
vector<int> g[100000], st, lst[100000], tst[100000];
bool ans[100000];

bool anc(int u, int v)
{
    return ((range[u].f<=range[v].f)&&(range[u].s>=range[v].s));
}

void dfs1(int u, int v)
{
    range[u].f = ++ct;
    for(int i = 0; i<g[u].size(); i++)
        if(g[u][i]!=v)
            depth[g[u][i]] = depth[u]+1, dfs1(g[u][i],u);
    range[u].s = ++ct;
}

void dfs2(int u, int v)
{
    st.push_back(u);
    tst[t[u]-1].push_back(u);
    for(int i = 0; i<lst[u].size(); i++)
    {
        if(!tst[c[lst[u][i]]].size())
            continue;
        int c1 = tst[c[lst[u][i]]][tst[c[lst[u][i]]].size()-1], c2 = u^a[lst[u][i]]^b[lst[u][i]];
        ans[lst[u][i]]|=((!anc(c1,c2))||(u==c1));
        if(depth[c1]+1<st.size())
            ans[lst[u][i]]|=(anc(c1,c2)&&!anc(st[depth[c1]+1],c2));
    }
    for(int i = 0; i<g[u].size(); i++)
        if(g[u][i]!=v)
            dfs2(g[u][i],u);
    st.pop_back();
    tst[t[u]-1].pop_back();
}

int main()
{
    freopen("milkvisits.in","r",stdin);
    freopen("milkvisits.out","w",stdout);
    cin >> n >> m;
    for(int i = 0; i<n; i++)
        cin >> t[i];
    for(int i = 0; i<n-1; i++)
    {
        cin >> x >> y;
        g[x-1].push_back(y-1);
        g[y-1].push_back(x-1);
    }
    for(int i = 0; i<m; i++)
    {
        cin >> a[i] >> b[i] >> c[i];
        a[i]--, b[i]--, c[i]--;
        lst[a[i]].push_back(i), lst[b[i]].push_back(i);
    }
    dfs1(0,0), dfs2(0,0);
    for(int i = 0; i<m; i++)
        cout << ans[i];
    cout << endl;
}
