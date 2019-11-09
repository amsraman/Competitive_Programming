/*
ID: adityasund1
TASK: cowtour
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;

vector<pair<int,double> > g[150];
int n, group[150], c = 0;
double d[150][150], ans = INF, di[150];
bool v[150][150] = {false}, v2[150] = {false};

void dij(int a)
{
    di[a] = 0;
    priority_queue<pair<int,double> > q;
    q.push({0,a});
    for(int i = 0; i<n; i++)
    {
        d[a][i] = INF;
    }
    d[a][a] = 0;
    while(!q.empty())
    {
        int b = q.top().second;
        q.pop();
        if(!v[a][b])
        {
            v[a][b] = true;
            for(int i = 0; i<g[b].size(); i++)
            {
                if((d[a][b]+g[b][i].second<d[a][g[b][i].first])&&(!v[a][g[b][i].first]))
                {
                    d[a][g[b][i].first] = d[a][b]+g[b][i].second;
                    q.push({-d[a][g[b][i].first],g[b][i].first});
                }
            }
        }
    }
    for(int i = 0; i<n; i++)
    {
        if(d[a][i]!=INF)
        {
            di[a] = max(di[a],d[a][i]);
        }
    }
}

void dfs(int a, int c)
{
    if(v2[a])
    {
        return;
    }
    v2[a] = true;
    group[a] = c;
    for(int i = 0; i<g[a].size(); i++)
    {
        if(!v2[g[a][i].first])
        {
            dfs(g[a][i].first,c);
        }
    }
}

int main()
{
    ifstream infile("cowtour.in");
    ofstream outfile("cowtour.out");
    string a;
    infile >> n;
    pair<int,int> p[n];
    vector<double> sg;
    for(int i = 0; i<n; i++)
    {
        infile >> p[i].first >> p[i].second;
    }
    for(int i = 0; i<n; i++)
    {
        infile >> a;
        for(int j = 0; j<n; j++)
        {
            if(a[j]=='1')
            {
                int x = p[i].first-p[j].first, y = p[i].second-p[j].second;
                g[i].push_back({j,sqrt(double(x*x+y*y))});
            }
        }
    }
    for(int i = 0; i<n; i++)
    {
        dij(i);
        if(!v2[i])
        {
            dfs(i,c);
            sg.push_back(0);
            c++;
        }
    }
    for(int i = 0; i<n; i++)
    {
        sg[group[i]] = max(sg[group[i]],di[i]);
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(group[i]!=group[j])
            {
                int x = p[i].first-p[j].first, y = p[i].second-p[j].second;
                ans = min(ans,max(di[i]+di[j]+sqrt(double(x*x+y*y)),max(sg[group[i]],sg[group[j]])));
            }
        }
    }
    outfile << fixed << setprecision(6) << ans << endl;
}
