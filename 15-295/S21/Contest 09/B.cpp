#include <bits/stdc++.h>
#define f first
#define s second
#define INF 0x3f3f3f3f

using namespace std;

int r, c, level[20002], ptr[20002], flow;
vector<int> g[20002];
map<pair<int,int>,int> edge;
pair<int,int> dir[4] = {{0,1},{1,0},{0,-1},{-1,0}};
string w, grid[10000];

bool ok(int x, int y, int dx, int dy)
{
    return ((x+dx>=0)&&(x+dx<r)&&(y+dy>=0)&&(y+dy<c));
}

void addEdge(int x, int y)
{
    g[x].push_back(y);
    g[y].push_back(x);
    edge[{x,y}] = 1;
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
    cin >> w >> r >> c;
    for(int i = 0; i<r; i++)
        cin >> grid[i];
    for(int i = 0; i<r; i++)
        for(int j = 0; j<c; j++)
            addEdge(c*i+j+1,r*c+c*i+j+1);
    for(int i = 0; i<r; i++)
        for(int j = 0; j<c; j++)
        {
            if(grid[i][j]==w[0])
                addEdge(0,c*i+j+1);
            for(int k = 0; k<w.length()-1; k++)
                if(grid[i][j]==w[k])
                    for(pair<int,int> d: dir)
                        if(ok(i,j,d.f,d.s)&&grid[i+d.f][j+d.s]==w[k+1])
                            addEdge(r*c+c*i+j+1,c*(i+d.f)+j+d.s+1);
            if(grid[i][j]==w[w.length()-1])
                addEdge(r*c+c*i+j+1,2*r*c+1);
            for(pair<int,int> d: dir)
                if(ok(i,j,d.f,d.s)&&grid[i+d.f][j+d.s]==grid[i][j])
                    addEdge(r*c+c*i+j+1,c*(i+d.f)+j+d.s+1);
        }
    cout << dinic_flow(0,2*r*c+1) << endl;
}