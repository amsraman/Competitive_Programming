#include <iostream>
#include <fstream>
#include <vector>
#define INF 0x3f3f3f3f

using namespace std;

int t, n, m, x, y, z, d[50][50];
pair<pair<int,int>,int> in[1000];
bool pos;
vector<pair<int,int> > g[50];

int main()
{
    ifstream fin("graphs_as_a_service.txt");
    ofstream fout("output.txt");
    fin >> t;
    for(int cz = 0; cz<t; cz++)
    {
        fin >> n >> m;
        pos = true;
        for(int i = 0; i<m; i++)
        {
            fin >> x >> y >> z;
            in[i] = {{x-1,y-1},z};
            g[x-1].push_back({y-1,z});
            g[y-1].push_back({x-1,z});
        }
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<n; j++)
            {
                d[i][j] = INF;
            }
            d[i][i] = 0;
        }
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<g[i].size(); j++)
            {
                d[i][g[i][j].first] = g[i][j].second;
            }
        }
        for(int k = 0; k<n; k++)
        {
            for(int i = 0; i<n; i++)
            {
                for(int j = 0; j<n; j++)
                {
                    d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
                }
            }
        }
        for(int i = 0; i<m; i++)
        {
            if(d[in[i].first.first][in[i].first.second]!=in[i].second) pos = false;
        }
        fout << "Case #" << cz+1 << ": ";
        if(pos)
        {
            fout << m << endl;
            for(int i = 0; i<m; i++)
            {
                fout << in[i].first.first+1 << " " << in[i].first.second+1 << " " << in[i].second << endl;
            }
        }
        else
        {
            fout << "Impossible" << endl;
        }
        for(int i = 0; i<n; i++) g[i].clear();
    }
}
