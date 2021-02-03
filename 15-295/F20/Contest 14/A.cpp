#include <bits/stdc++.h>

using namespace std;

int n, m, tot;
int b[100000];
vector<int> g[100000];
bool vis[100000], ans = true;

void dfs(int x)
{
    vis[x] = true, tot+=b[x];
    for(int i = 0; i<g[x].size(); i++)
        if(!vis[g[x][i]])
            dfs(g[x][i]);
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> b[i];
    cin >> m;
    for(int i = 0, l, r; i<m; i++)
    {
        cin >> l >> r;
        g[l-1].push_back(r-1);
        g[r-1].push_back(l-1);
    }
    for(int i = 0; i<n; i++)
        if(!vis[i])
        {
            tot = 0;
            dfs(i);
            ans&=(tot%2==0);
        }
    cout << (ans?"Yes":"No") << endl;
}