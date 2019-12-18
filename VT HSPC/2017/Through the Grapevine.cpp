#include <bits/stdc++.h>

using namespace std;

int n, m, d, t[100000], con[100000], ans;
string s, u, v, r;
vector<int> g[100000];
map<string,int> ms;
bool heard[100000], vis[100000];

int main()
{
    cin >> n >> m >> d;
    for(int i = 0; i<n; i++)
    {
        cin >> s >> t[i];
        ms[s] = i;
    }
    for(int i = 0; i<m; i++)
    {
        cin >> u >> v;
        g[ms[u]].push_back(ms[v]);
        g[ms[v]].push_back(ms[u]);
    }
    cin >> r;
    queue<pair<int,int> > q;
    q.push({ms[r],0});
    heard[ms[r]] = vis[ms[r]] = true;
    while(!q.empty())
    {
        int x = q.front().first, y = q.front().second;
        for(int i = 0; i<g[x].size(); i++)
        {
            con[g[x][i]]++;
            if((!heard[g[x][i]])&&(y<d))
            {
                heard[g[x][i]] = true;
                ans++;
            }
            if((!vis[g[x][i]])&&(con[g[x][i]]==t[g[x][i]]))
            {
                q.push({g[x][i],y+1});
                vis[g[x][i]] = true;
            }
        }
        q.pop();
    }
    cout << ans << endl;
}
