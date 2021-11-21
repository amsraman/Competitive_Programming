#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

int l, h, n, m, orig[1000][1000], edge[1000][1000], level[1000], ptr[1000], ctr, ans[1000];
vector<int> g[1000], divs[1000], primes;
set<int> pset;
bool matched[1000];

void chk(int x)
{
    for(int i = 2; i*i<=x; i++)
    {
        if(x%i==0)
            pset.insert(i);
        while(x%i==0)
            x/=i;
    }
    if(x!=1)
        pset.insert(x);
}

void addEdge(int x, int y, int z)
{
    g[x].push_back(y);
    g[y].push_back(x);
    orig[x][y] = z;
}

int dfs(int a, int c, int t)
{
    if(a==t) return c;
    while(ptr[a]<g[a].size())
    {
        while((ptr[a]<g[a].size())&&((level[g[a][ptr[a]]]!=level[a]+1)||(edge[a][g[a][ptr[a]]]==0))) ptr[a]++;
        if(ptr[a]==g[a].size()) continue;
        int k = dfs(g[a][ptr[a]],min(c,edge[a][g[a][ptr[a]]]),t);
        if(k!=0)
        {
            edge[a][g[a][ptr[a]]]-=k;
            edge[g[a][ptr[a]]][a]+=k;
            return k;
        }
        else ptr[a]++;
    }
    return 0;
}

int dinic_flow(int a, int b, int flow)
{
    bool lg = true;
    while(lg)
    {
        for(int i = 0; i<m+n+2; i++) level[i] = ptr[i] = 0;
        queue<int> q;
        q.push(a), level[a] = 1;
        while(!q.empty())
        {
            int z = q.front();
            q.pop();
            for(int i = 0; i<g[z].size(); i++)
                if((level[g[z][i]]==0)&&(edge[z][g[z][i]]!=0))
                    level[g[z][i]] = level[z]+1, q.push(g[z][i]);
        }
        lg = (level[b]!=0);
        if(!lg) continue;
        while(int p = dfs(a,INF,b)) flow+=p;
    }
    return flow;
}

int main()
{
    cin >> l >> h;
    while(l+h>0)
    {
        for(int i = l; i<=h; i++)
            chk(i);
        for(auto x: pset)
            primes.push_back(x);
        m = primes.size(), n = h-l+1;
        for(int i = 0; i<m; i++)
            for(int j = l; j<=h; j++)
                if(j%primes[i]==0)
                   addEdge(i+1,j-l+m+1,1000-(++ctr)), divs[j-l].push_back(i);
        for(int i = 0; i<m; i++)
            addEdge(0,i+1,1);
        for(int i = 0; i<n; i++)
            addEdge(i+m+1,m+n+1,1);
        for(int i = 0; i<n; i++)
            for(int j: divs[i])
            {
                if(matched[j])
                    continue;
                orig[0][j+1] = orig[j+1][i+m+1] = orig[i+m+1][m+n+1] = 0;
                for(int i = 0; i<m+n+2; i++)
                    for(int j = 0; j<m+n+2; j++)
                        edge[i][j] = orig[i][j];
                if(dinic_flow(0,m+n+1,0)==n-i-1)
                {
                    ans[i] = primes[j], matched[j] = true;
                    break;
                }
                orig[0][j+1] = orig[j+1][i+m+1] = orig[i+m+1][m+n+1] = 1;
            }
        for(int i = 0; i<n; i++)
            cout << ans[i] << " ";
        cout << endl;
        cin >> l >> h;
        memset(orig,0,sizeof(orig)), memset(matched,false,sizeof(matched));
        for(int i = 0; i<=m+n+1; i++)
            g[i].clear();
        primes.clear(), pset.clear(), ctr = 0;
        for(int i = 0; i<n; i++)
            divs[i].clear();
    }
}
