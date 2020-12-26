#include <bits/stdc++.h>

using namespace std;

int n, m, a[100000], ans;
vector<int> g[100000];

void dfs(int x, int y, int z)
{
    if((x!=0)&&(g[x].size()==1))
        ans++;
    for(int i = 0; i<g[x].size(); i++)
        if((g[x][i]!=y)&&((z+1)*a[g[x][i]]<=m))
            dfs(g[x][i],x,(z+1)*a[g[x][i]]);
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    for(int i = 0, x, y; i<n-1; i++)
    {
        cin >> x >> y;
        g[x-1].push_back(y-1);
        g[y-1].push_back(x-1);
    }
    dfs(0,0,a[0]);
    cout << ans << endl;
}