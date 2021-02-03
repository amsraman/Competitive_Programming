#include <bits/stdc++.h>
#define f first
#define s second
#define INF 0x3f3f3f3f

using namespace std;

int r, c, level[20002], ptr[20002], flow;
pair<int,int> dir[4] = {{0,1},{1,0},{0,-1},{-1,0}};
string grid[20002];
vector<int> g[20002];
map<pair<int,int>,int> edge;

bool ok(int x, int y, int z)
{
    return (x+dir[z].f>=0&&x+dir[z].f<r&&y+dir[z].s>=0&&y+dir[z].s<c);
}

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
        for(int i = 0; i<2*r*c+2; i++) level[i] = ptr[i] = 0;
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
    cin >> r >> c;
    for(int i = 0; i<r; i++)
        cin >> grid[i];
    for(int i = 0; i<r; i++)
        for(int j = 0; j<c; j++)
        {
            if(grid[i][j]=='b')
                addEdge(0,c*i+j+1,1);
            if(grid[i][j]=='e')
                addEdge(c*i+j+1,r*c+c*i+j+1,1);
            if(grid[i][j]=='r')
                addEdge(c*i+j+1,2*r*c+1,1);
        }
    for(int i = 0; i<r; i++)
        for(int j = 0; j<c; j++)
            for(int k = 0; k<4; k++)
                if(ok(i,j,k))
                {
                    if(grid[i][j]=='b'&&grid[i+dir[k].f][j+dir[k].s]=='e')
                        addEdge(c*i+j+1,c*(i+dir[k].f)+j+dir[k].s+1,1);
                    if(grid[i][j]=='e'&&grid[i+dir[k].f][j+dir[k].s]=='e')
                        addEdge(r*c+c*i+j+1,c*(i+dir[k].f)+j+dir[k].s+1,1);
                    if(grid[i][j]=='e'&&grid[i+dir[k].f][j+dir[k].s]=='r')
                        addEdge(r*c+c*i+j+1,c*(i+dir[k].f)+j+dir[k].s+1,1);
                }
    cout << dinic_flow(0,2*r*c+1) << endl;
}