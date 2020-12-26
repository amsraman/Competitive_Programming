#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, b1, b2, num, dist[3000];
pair<int,int> edges[3000];
vector<int> g[3000];
bool vis[3000], ring[3000];

void dfs(int x)
{
    vis[x] = true, num++;
    for(int i = 0; i<g[x].size(); i++)
        if(!vis[g[x][i]]&&(x!=b1||g[x][i]!=b2)&&(x!=b2||g[x][i]!=b1))
            dfs(g[x][i]);
}

bool red(int x)
{
    b1 = edges[x].f, b2 = edges[x].s, num = 0;
    dfs(0);
    for(int i = 0; i<n; i++)
        vis[i] = false;
    return(num==n);
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        cin >> edges[i].f >> edges[i].s;
        edges[i].f--, edges[i].s--;
        g[edges[i].f].push_back(edges[i].s);
        g[edges[i].s].push_back(edges[i].f);
    }
    for(int i = 0; i<n; i++)
        if(red(i))
            ring[edges[i].f] = ring[edges[i].s] = true;
    queue<int> q;
    for(int i = 0; i<n; i++)
        if(ring[i])
            q.push(i), vis[i] = true;
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        for(int i = 0; i<g[x].size(); i++)
            if(!vis[g[x][i]])
                q.push(g[x][i]), dist[g[x][i]] = dist[x]+1, vis[g[x][i]] = true;
    }
    for(int i = 0; i<n; i++)
        cout << dist[i] << " ";
    cout << endl;
}