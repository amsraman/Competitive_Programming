#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;

int d[40000][2];
bool v[40000][3];
vector<int> g[40000];

void bfs(int a)
{
    queue<pair<int,int> > q;
    q.push({0,a});
    d[a][a] = 0;
    v[a][a] = true;
    while(!q.empty())
    {
        int z = q.front().second;
        q.pop();
        for(int i = 0; i<g[z].size(); i++)
        {
            if(!v[g[z][i]][a])
            {
                v[g[z][i]][a] = true;
                d[g[z][i]][a] = d[z][a]+1;
                q.push({d[z][a]+1,g[z][i]});
            }
        }
    }
}

int main()
{
    ifstream infile("piggyback.in");
    ofstream outfile("piggyback.out");
    int b, e, p, n, m;
    infile >> b >> e >> p >> n >> m;
    int y, z;
    int ans = INF;
    for(int i = 0; i<m; i++)
    {
        infile >> y >> z;
        g[y-1].push_back(z-1);
        g[z-1].push_back(y-1);
    }
    bfs(0);
    bfs(1);
    queue<pair<int,int> > q;
    q.push({0,n-1});
    ans = min(ans,b*d[n-1][0]+e*d[n-1][1]);
    v[n-1][2] = true;
    while(!q.empty())
    {
        y = q.front().first;
        z = q.front().second;
        q.pop();
        for(int i = 0; i<g[z].size(); i++)
        {
            if(!v[g[z][i]][2])
            {
                v[g[z][i]][2] = true;
                ans = min(ans,b*d[g[z][i]][0]+e*d[g[z][i]][1]+p*(y+1));
                q.push({y+1,g[z][i]});
            }
        }
    }
    outfile << ans << endl;
}
