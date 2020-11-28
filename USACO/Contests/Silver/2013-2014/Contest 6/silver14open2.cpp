#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#define INF 0xfffffffffffffff

using namespace std;

int n, m;
long long d[100000][3];
vector<pair<int,int> > g[10000][3];
bool v[10000][3];

void dij(int a)
{
    for(int i = 0; i<n; i++)
    {
        d[i][a] = INF;
    }
    priority_queue<pair<int,int> > q;
    q.push({0,n-1});
    d[n-1][a] = 0;
    while(!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if(!v[x][a])
        {
            v[x][a] = true;
            for(int i = 0; i<g[x][a].size(); i++)
            {
                if(d[x][a]+g[x][a][i].first<d[g[x][a][i].second][a])
                {
                    d[g[x][a][i].second][a] = d[x][a]+g[x][a][i].first;
                    q.push({-d[g[x][a][i].second][a],g[x][a][i].second});
                }
            }
        }
    }
}

int main()
{
    ifstream infile("gpsduel.in");
    ofstream outfile("gpsduel.out");
    infile >> n >> m;
    int a, b, p, q;
    for(int i = 0; i<m; i++)
    {
        infile >> a >> b >> p >> q;
        g[b-1][0].push_back({p,a-1});
        g[b-1][1].push_back({q,a-1});
        g[b-1][2].push_back({2,a-1});
    }
    dij(0);
    dij(1);
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<g[i][0].size(); j++)
        {
            if(d[g[i][0][j].second][0]-d[i][0]==g[i][0][j].first)
            {
                g[i][2][j].first--;
            }
            if(d[g[i][1][j].second][1]-d[i][1]==g[i][1][j].first)
            {
                g[i][2][j].first--;
            }
        }
    }
    dij(2);
    outfile << d[0][2] << endl;
}
