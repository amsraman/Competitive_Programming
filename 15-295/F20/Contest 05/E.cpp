#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n, m, c[200], ind[200];
pair<int,int> edges[10000];
bool vis[600], clr[600], ans;
vector<int> g[600];

void dfs(int x)
{
    vis[x] = true;
    for(int i = 0; i<g[x].size(); i++)
    {
        if(vis[g[x][i]]&&(clr[x]==clr[g[x][i]]))
            ans = false;
        if(!vis[g[x][i]])
            clr[g[x][i]] = clr[x]^1, dfs(g[x][i]);
    }
}

int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n >> m;
        for(int i = 0; i<m; i++)
            cin >> edges[i].f >> edges[i].s;
        for(int i = 0; i<n; i++)
            cin >> c[i];
        for(int i = 0; i<n; i++)
            ind[c[i]-1] = i;
        for(int i = 0; i<m; i++)
        {
            edges[i].f = ind[edges[i].f-1], edges[i].s = ind[edges[i].s-1];
            if(edges[i].f>edges[i].s)
                swap(edges[i].f,edges[i].s);
        }
        if(m>3*(n-2))
            cout << "NO" << endl;
        else
        {
            ans = true;
            memset(vis,false,sizeof(vis));
            memset(clr,false,sizeof(clr));
            sort(edges,edges+m);
            for(int i = 0; i<m; i++)
                for(int j = i+1; j<m; j++)
                {
                    if(edges[i].f==edges[j].f||edges[i].f==edges[j].s||edges[i].s==edges[j].f||edges[i].s==edges[j].s)
                        continue;
                    if((edges[i].f<edges[j].f&&edges[j].f<edges[i].s)^(edges[i].f<edges[j].s&&edges[j].s<edges[i].s))
                        g[i].push_back(j), g[j].push_back(i);
                }
            for(int i = 0; i<m; i++)
                if(!vis[i])
                    dfs(i);
            cout << (ans?"YES":"NO") << endl;
            for(int i = 0; i<m; i++)
                g[i].clear();
        }
    }
}