#include <bits/stdc++.h>
#define f first
#define s second
#define INF 1e12
typedef long long ll;

using namespace std;

int t, n, m, s, r;
ll d[300][300], ans;
vector<int> g[300], rec[300];
vector<pair<int,int>> gr[300];
bool vis[300][300];

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> m >> s >> r;
        for(int i = 0, u, v; i<m; i++)
        {
            cin >> u >> v;
            g[u-1].push_back(v-1);
            g[v-1].push_back(u-1);
        }
        memset(vis,false,sizeof(vis));
        for(int i = 0; i<n; i++)
            for(int j = 0; j<s; j++)
                d[i][j] = INF;
        ans = INF;
        priority_queue<pair<ll,pair<int,int>>> q;
        for(int i = 0, c, st; i<n; i++)
        {
            cin >> c;
            for(int j = 0; j<c; j++)
            {
                cin >> st;
                d[i][st-1] = 0, q.push({0,{i,st-1}});
            }
        }
        for(int i = 0, k, res; i<r; i++)
        {
            cin >> k;
            rec[i].resize(k);
            for(int j = 0; j<k; j++)
                cin >> rec[i][j];
            cin >> res;
            for(int j = 0; j<k; j++)
                gr[rec[i][j]-1].push_back({res-1,i});
        }
        while(!q.empty())
        {
            int x = q.top().s.f, y = q.top().s.s;
            q.pop();
            if(vis[x][y])
                continue;
            vis[x][y] = true;
            for(int i = 0; i<g[x].size(); i++)
                if(d[g[x][i]][y]>d[x][y]+1)
                    d[g[x][i]][y] = d[x][y]+1, q.push({-d[x][y]-1,{g[x][i],y}});
            for(int i = 0; i<gr[y].size(); i++)
            {
                ll mx = 0;
                for(int j = 0; j<rec[gr[y][i].s].size(); j++)
                    mx+=d[x][rec[gr[y][i].s][j]-1];
                if(d[x][gr[y][i].f]>mx)
                    d[x][gr[y][i].f] = mx, q.push({-mx,{x,gr[y][i].f}});
            }
        }
        for(int i = 0; i<n; i++)
            ans = min(ans,d[i][0]);
        cout << "Case #" << _ << ": " << (ans==INF?-1:ans) << endl;
        for(int i = 0; i<n; i++)
            g[i].clear();
        for(int i = 0; i<s; i++)
            gr[i].clear();
    }
}
