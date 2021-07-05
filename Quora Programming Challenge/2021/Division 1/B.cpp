#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, k, dist[1000][1000];
pair<int,int> dir[4] = {{0,-1},{-1,0},{0,1},{1,0}}, start, finish;
string grid[1000];
bool vis[1000][1000], blocked[1000][1000];

int main()
{
    cin >> n >> m >> k;
    for(int i = 0; i<n; i++)
        cin >> grid[i];
    priority_queue<pair<int,pair<int,int>>> pq;
    for(int i = 0, r, c, d; i<k; i++)
    {
        cin >> r >> c >> d;
        pq.push({d,{r-1,c-1}});
    }

    while(!pq.empty())
    {
        int x = pq.top().s.f, y = pq.top().s.s, z = pq.top().f;
        pq.pop();
        if(blocked[x][y])
            continue;
        blocked[x][y] = true;
        for(pair<int,int> d: dir)
            if(x+d.f>=0&&x+d.f<n&&y+d.s>=0&&y+d.s<m&&!blocked[x+d.f][y+d.s]&&z>0)
                pq.push({z-1,{x+d.f,y+d.s}});
    }
    queue<pair<int,int>> q;
    q.push(start), vis[start.f][start.s] = true;
    while(!q.empty())
    {
        int x = q.front().f, y = q.front().s;
        q.pop();
        if(blocked[x][y])
            break;
        for(pair<int,int> d: dir)
            if(x+d.f>=0&&x+d.f<n&&y+d.s>=0&&y+d.s<m&&!blocked[x+d.f][y+d.s]&&!vis[x+d.f][y+d.s])
                q.push({x+d.f,y+d.s}), dist[x+d.f][y+d.s] = dist[x][y]+1, vis[x+d.f][y+d.s] = true;
    }
    if(dist[finish.f][finish.s]==0)
        cout << "IMPOSSIBLE" << endl;
    else
        cout << dist[finish.f][finish.s] << endl;
}