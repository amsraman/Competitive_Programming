#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define f first
#define s second

using namespace std;

int n, m, a, b, cc, ans = INF;
pair<int,int> points[100000], mi[100000], ma[100000];
bool v[100000];
vector<int> g[100000];

void dfs(int x)
{
    v[x] = true;
    mi[cc].f = min(mi[cc].f,points[x].f), mi[cc].s = min(mi[cc].s,points[x].s);
    ma[cc].f = max(ma[cc].f,points[x].f), ma[cc].s = max(ma[cc].s,points[x].s);
    for(int i = 0; i<g[x].size(); i++)
        if(!v[g[x][i]])
            dfs(g[x][i]);
}

int main()
{
    freopen("fenceplan.in","r",stdin);
    freopen("fenceplan.out","w",stdout);
    cin >> n >> m;
    for(int i = 0; i<n; i++)
        cin >> points[i].f >> points[i].s;
    for(int i = 0; i<m; i++)
    {
        cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    for(int i = 0; i<n; i++)
        mi[i] = {INF,INF};
    for(int i = 0; i<n; i++)
        if(!v[i])
            dfs(i), cc++;
    for(int i = 0; i<cc; i++)
        ans = min(ans,2*(ma[i].f+ma[i].s-mi[i].f-mi[i].s));
    cout << ans << endl;
}
