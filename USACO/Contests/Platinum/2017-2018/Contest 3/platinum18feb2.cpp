#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, q, x, depth[100000], par[100000][17], comp[100000], cur = -1;
pair<int,int> v[100000];
char qt;

int lca(int a, int b)
{
    if(depth[a]<depth[b])
        swap(a,b);
    for(int i = 0; i<17; i++)
        if((1<<i)&(depth[a]-depth[b]))
            a = par[a][i];
    for(int i = 16; i>=0; i--)
        if(par[a][i]!=par[b][i])
            a = par[a][i], b = par[b][i];
    return (a==b?a:par[a][0]);
}

int dist(int a, int b)
{
    return (depth[a]+depth[b]-2*depth[lca(a,b)]);
}

int main()
{
    freopen("newbarn.in","r",stdin);
    freopen("newbarn.out","w",stdout);
    cin >> q;
    for(int i = 0; i<q; i++)
    {
        cin >> qt >> x;
        if(qt=='B')
        {
            ++cur;
            if(x==-1)
                comp[cur] = cur, v[cur] = {cur,cur};
            else
            {
                depth[cur] = depth[x-1]+1, par[cur][0] = x-1, comp[cur] = comp[x-1];
                for(int i = 0; i<16; i++)
                    par[cur][i+1] = par[par[cur][i]][i];
                int d = dist(v[comp[cur]].f,v[comp[cur]].s);
                if(dist(cur,v[comp[cur]].f)>d)
                    v[comp[cur]].s = cur;
                else if(dist(cur,v[comp[cur]].s)>d)
                    v[comp[cur]].f = cur;
            }
        }
        else
            cout << max(dist(x-1,v[comp[x-1]].f),dist(x-1,v[comp[x-1]].s)) << endl;
    }
}
