#include <bits/stdc++.h>

using namespace std;

int n, m, dist[20000];
bool vis[20000];

int main()
{
    cin >> n >> m;
    queue<int> q;
    q.push(n), vis[n-1] = true;
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        if((2*x<=20000)&&(!vis[2*x-1]))
            q.push(2*x), dist[2*x-1] = dist[x-1]+1, vis[2*x-1] = true;
        if((x>1)&&(!vis[x-2]))
            q.push(x-1), dist[x-2] = dist[x-1]+1, vis[x-2] = true;
        if((x<19999)&&(!vis[x]))
            q.push(x+1), dist[x] = dist[x-1]+1, vis[x] = true;
    }
    cout << dist[m-1] << endl;
}
