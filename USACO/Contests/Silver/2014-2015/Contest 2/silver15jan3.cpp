#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int co[100];
bool t[10001][100][2], v[100];
vector<int> ti[100][2];
vector<pair<int,int> > g[100][2];

int main()
{
    ifstream infile("meeting.in");
    ofstream outfile("meeting.out");
    int n, m, a, b, c, d;
    infile >> n >> m;
    priority_queue<pair<int,int> > q;
    for(int i = 0; i<m; i++)
    {
        infile >> a >> b >> c >> d;
        g[a-1][0].push_back({c,b-1});
        g[a-1][1].push_back({d,b-1});
        co[b-1]++;
    }
    for(int i = 0; i<n; i++)
    {
        q.push({-co[i],i});
    }
    t[0][0][0] = t[0][0][1] = true;
    ti[0][0].push_back(0);
    ti[0][1].push_back(0);
    while(!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if(!v[x])
        {
            v[x] = true;
            for(int i = 0; i<g[x][0].size(); i++)
            {
                for(int j = 0; j<ti[x][0].size(); j++)
                {
                    if(!t[ti[x][0][j]+g[x][0][i].first][g[x][0][i].second][0])
                    {
                        t[ti[x][0][j]+g[x][0][i].first][g[x][0][i].second][0] = true;
                        ti[g[x][0][i].second][0].push_back(ti[x][0][j]+g[x][0][i].first);
                    }
                }
                for(int j = 0; j<ti[x][1].size(); j++)
                {
                    if(!t[ti[x][1][j]+g[x][1][i].first][g[x][1][i].second][1])
                    {
                        t[ti[x][1][j]+g[x][1][i].first][g[x][1][i].second][1] = true;
                        ti[g[x][1][i].second][1].push_back(ti[x][1][j]+g[x][1][i].first);
                    }
                }
                co[g[x][0][i].second]--;
                q.push({-co[g[x][0][i].second],g[x][0][i].second});
            }
        }
    }
    for(int i = 0; i<10001; i++)
    {
        if((t[i][n-1][0])&&(t[i][n-1][1]))
        {
            outfile << i << endl;
            return 0;
        }
    }
    outfile << "IMPOSSIBLE" << endl;
}
