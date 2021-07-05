#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

int t, n, m, level[200002], ptr[200002], flow;
vector<int> g[200002];
map<pair<int,int>,int> edge;

void addEdge(int x, int y, int z)
{
    g[x].push_back(y);
    g[y].push_back(x);
    edge[{x,y}] = z;
}

int dfs(int a, int c, int t)
{
    if(a==t) return c;
    while(ptr[a]<g[a].size())
    {
        while((ptr[a]<g[a].size())&&((level[g[a][ptr[a]]]!=level[a]+1)||(edge[{a,g[a][ptr[a]]}]==0))) ptr[a]++;
        if(ptr[a]==g[a].size()) continue;
        int k = dfs(g[a][ptr[a]],min(c,edge[{a,g[a][ptr[a]]}]),t);
        if(k!=0)
        {
            edge[{a,g[a][ptr[a]]}]-=k;
            edge[{g[a][ptr[a]],a}]+=k;
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
        for(int i = 0; i<n+m+2; i++) level[i] = ptr[i] = 0;
        queue<int> q;
        q.push(a), level[a] = 1;
        while(!q.empty())
        {
            int z = q.front();
            q.pop();
            for(int i = 0; i<g[z].size(); i++)
                if((level[g[z][i]]==0)&&(edge[{z,g[z][i]}]!=0))
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
    cin >> t;
    while(t--)
    {
        cin >> n >> m;
        for(int i = 0, k; i<m; i++)
        {
            cin >> k;
            for(int j = 0, f; j<k; j++)
            {
                cin >> f;
                addEdge(f,i+n+1,1);
            }
        }
        for(int i = 0; i<n; i++)
            addEdge(0,i+1,(m+1)/2);
        for(int i = 0; i<m; i++)
            addEdge(n+i+1,n+m+1,1);
        if(dinic_flow(0,n+m+1)==m)
        {
            cout << "YES" << endl;
            for(int j = n+1; j<n+m+1; j++)
                for(int k: g[j])
                    if(edge[{j,k}]==1)
                        cout << k << " ";
            cout << endl;
        }
        else
            cout << "NO" << endl;
        for(int i = 0; i<n+m+2; i++)
            g[i].clear();
        edge.clear(), flow = 0;
    }
}