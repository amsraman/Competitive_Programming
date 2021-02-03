#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

int n, m, bruh1[100], bruh2[100], edge[500][500], level[500], ptr[500], flow;
vector<int> g[500];

void addEdge(int x, int y, int z)
{
    g[x].push_back(y);
    g[y].push_back(x);
    edge[x][y] = z;
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

int dinic_flow(int a, int b)
{
    bool lg = true;
    while(lg)
    {
        for(int i = 0; i<2*n+2; i++) level[i] = ptr[i] = 0;
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
    cin >> n >> m;
    for(int i = 0; i<n; i++)
        cin >> bruh1[i];
    for(int i = 0; i<n; i++)
        cin >> bruh2[i];
    for(int i = 0; i<n; i++)
        addEdge(0,i+1,bruh1[i]), addEdge(i+n+1,2*n+1,bruh2[i]);
    for(int i = 0, p, q; i<m; i++)
    {
        cin >> p >> q;
        addEdge(p,q+n,INF);
        addEdge(q,p+n,INF);
    }
    for(int i = 0; i<n; i++)
        addEdge(i+1,i+n+1,INF);
    dinic_flow(0,2*n+1);
    int sum1 = 0, sum2 = 0;
    for(int i = 0; i<n; i++)
        sum1+=bruh1[i], sum2+=bruh2[i];
    cout << (sum1==sum2&&flow==sum2?"YES":"NO") << endl;
    if(flow==sum2&&sum1==sum2)
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<n; j++)
                cout << edge[j+n+1][i+1] << " ";
            cout << endl;
        }
}
