#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;

int n, m, t, c[10000], x, y, z;
long long d[10000], traf[10000], ans;
bool v[10000];
vector<pair<int,int> > g[10000];
vector<int> g2[10000];

void dfs(int a)
{
    traf[a]+=c[a];
    for(int i = 0; i<g2[a].size(); i++)
    {
        dfs(g2[a][i]);
        traf[a]+=traf[g2[a][i]];
    }
}

int main()
{
    ifstream infile("shortcut.in");
    ofstream outfile("shortcut.out");
    infile >> n >> m >> t;
    for(int i = 0; i<n; i++)
    {
        infile >> c[i];
        d[i] = INF;
    }
    for(int i = 0; i<m; i++)
    {
        infile >> x >> y >> z;
        g[x-1].push_back(make_pair(y-1,z));
        g[y-1].push_back(make_pair(x-1,z));
    }
    priority_queue<pair<int,int> > q;
    q.push(make_pair(0,0));
    d[0] = 0;
    while(!q.empty())
    {
        int a = q.top().second;
        q.pop();
        if(!v[a])
        {
            v[a] = true;
            for(int i = 0; i<g[a].size(); i++)
            {
                if(d[a]+g[a][i].second<d[g[a][i].first])
                {
                    d[g[a][i].first] = d[a]+g[a][i].second;
                    q.push(make_pair(-d[g[a][i].first],g[a][i].first));
                }
            }
        }
    }
    for(int i = 1; i<n; i++)
    {
        int next = 100000;
        for(int j = 0; j<g[i].size(); j++)
        {
            if(d[g[i][j].first]+g[i][j].second==d[i])
            {
                next = min(next,g[i][j].first);
            }
        }
        g2[next].push_back(i);
    }
    dfs(0);
    for(int i = 0; i<n; i++)
    {
        ans = max(ans,(d[i]-t)*traf[i]);
    }
    outfile << ans << endl;
}
