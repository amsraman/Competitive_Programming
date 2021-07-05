#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

int n, a[3], b[3], level[8], ptr[8], flow;
vector<int> g[8];
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
        for(int i = 0; i<8; i++) level[i] = ptr[i] = 0;
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
    cin >> n;
    for(int i = 0; i<3; i++)
        cin >> a[i];
    for(int i = 0; i<3; i++)
        cin >> b[i];
    for(int i = 0; i<3; i++)
        addEdge(0,i+1,a[i]), addEdge(i+4,7,b[i]), addEdge(i+1,i%3+4,INF), addEdge(i+1,(i+2)%3+4,INF);
    cout << n-dinic_flow(0,7) << " " << min(a[0],b[1])+min(a[1],b[2])+min(a[2],b[0]) << endl;
}