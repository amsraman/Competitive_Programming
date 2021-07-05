#include <bits/stdc++.h>

using namespace std;

int n, m, d[100000];
vector<int> g[100000];
bool vis[100000];

int main()
{
    cin >> n >> m;
    for(int i = 0, a, b; i<m; i++)
    {
        cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    queue<int> q;
    q.push(0), vis[0] = true;
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        for(int i: g[x])
            if(!vis[i])
                q.push(i), vis[i] = true, d[i] = d[x]+1;
    }
    cout << d[n-1]-1 << endl;
}