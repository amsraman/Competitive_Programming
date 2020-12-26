#include <bits/stdc++.h>
 
using namespace std;
 
int n, h, l, mov[1000], dist[1000], mx;
vector<int> g[1000];
bool vis[1000];
 
int main()
{
    cin >> n >> h >> l;
    for(int i = 0; i<h; i++)
        cin >> mov[i];
    for(int i = 0, x, y; i<l; i++)
    {
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    queue<int> q;
    memset(dist,0x3f3f3f3f,sizeof(dist));
    for(int i = 0; i<h; i++)
        q.push(mov[i]), vis[mov[i]] = true, dist[mov[i]] = 0;
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        for(int i = 0; i<g[x].size(); i++)
            if(!vis[g[x][i]])
                dist[g[x][i]] = dist[x]+1, q.push(g[x][i]), vis[g[x][i]] = true;
    }
    for(int i = 0; i<n; i++)
        mx = max(mx,dist[i]);
    for(int i = 0; i<n; i++)
        if(dist[i]==mx)
        {
            cout << i << endl;
            break;
        }
}