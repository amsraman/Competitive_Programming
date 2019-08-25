#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#define INF 0xfffffffffffffff

using namespace std;

int n, m, k;
long long d1[50000], d2[50000], maxt[50000];
vector<pair<long long,int> > g[50000];
bool v[50000];

int main()
{
    ifstream infile("dining.in");
    ofstream outfile("dining.out");
    infile >> n >> m >> k;
    long long a, b, t;
    for(int i = 0; i<m; i++)
    {
        infile >> a >> b >> t;
        g[a-1].push_back({t,b-1});
        g[b-1].push_back({t,a-1});
    }
    for(int i = 0; i<k; i++)
    {
        infile >> a >> b;
        maxt[a-1] = max(maxt[a-1],b);
    }
    priority_queue<pair<int,int> > q;
    q.push({0,n-1});
    for(int i = 0; i<n; i++)
    {
        d1[i] = d2[i] = INF;
    }
    d1[n-1] = 0;
    while(!q.empty())
    {
        int a = q.top().second;
        q.pop();
        if(!v[a])
        {
            v[a] = true;
            for(int i = 0; i<g[a].size(); i++)
            {
                if(d1[a]+g[a][i].first<d1[g[a][i].second])
                {
                    d1[g[a][i].second] = d1[a]+g[a][i].first;
                    q.push({-d1[g[a][i].second],g[a][i].second});
                }
            }
        }
    }
    for(int i = 0; i<n; i++)
    {
        v[i] = false;
        if(maxt[i]!=0)
        {
            q.push({maxt[i]-d1[i],i});
            d2[i] = d1[i]-maxt[i];
        }
    }
    while(!q.empty())
    {
        int a = q.top().second;
        q.pop();
        if(!v[a])
        {
            v[a] = true;
            for(int i = 0; i<g[a].size(); i++)
            {
                if(d2[a]+g[a][i].first<d2[g[a][i].second])
                {
                    d2[g[a][i].second] = d2[a]+g[a][i].first;
                    q.push({-d2[g[a][i].second],g[a][i].second});
                }
            }
        }
    }
    for(int i = 0; i<n-1; i++)
    {
        outfile << (d2[i]<=d1[i]) << endl;
    }
}
