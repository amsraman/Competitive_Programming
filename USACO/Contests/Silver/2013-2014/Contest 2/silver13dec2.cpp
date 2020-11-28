#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#define INF 0xffffffffffffff

using namespace std;

int n, k;
long long dist[200][200];
vector<pair<int,int> > g[200];
bool v[200][200];

void dij(int a)
{
    for(int i = 0; i<n; i++){dist[a][i] = INF;}
    dist[a][a] = 0;
    priority_queue<pair<int,int> > q;
    q.push({0,a});
    while(!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if(!v[a][x])
        {
            v[a][x] = true;
            for(int i = 0; i<g[x].size(); i++)
            {
                dist[a][g[x][i].second] = min(dist[a][g[x][i].second],dist[a][x]+g[x][i].first);
                q.push({-dist[a][g[x][i].second],g[x][i].second});
            }
        }
    }
}

int main()
{
    ifstream infile("vacation.in");
    ofstream outfile("vacation.out");
    int m, q, ui, vi, d, a, b, ans1 = 0;
    long long ans2 = 0, minc;
    infile >> n >> m >> k >> q;
    for(int i = 0; i<m; i++)
    {
        infile >> ui >> vi >> d;
        g[ui-1].push_back({d,vi-1});
    }
    for(int i = 0; i<n; i++)
    {
        dij(i);
    }
    for(int i = 0; i<q; i++)
    {
        minc = INF;
        infile >> a >> b;
        for(int j = 0; j<k; j++)
        {
            if((v[a-1][j])&&(v[j][b-1]))
            {
                minc = min(minc,dist[a-1][j]+dist[j][b-1]);
            }
        }
        if(minc!=INF)
        {
            ans1++;
            ans2+=minc;
        }
    }
    outfile << ans1 << endl << ans2 << endl;
}
