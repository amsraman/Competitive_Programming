/*
ID: adityasund1
TASK: butter
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;

int n, p, c, d[800][800];
vector<pair<int,int> > g[800];
bool v[800][800] = {false};

void dij(int a)
{
    for(int i = 0; i<p; i++){d[a][i] = INF;}
    priority_queue<pair<int,int> > q;
    d[a][a] = 0;
    q.push({0,a});
    while(!q.empty())
    {
        int z = q.top().second;
        q.pop();
        if(!v[a][z])
        {
            v[a][z] = true;
            for(int i = 0; i<g[z].size(); i++)
            {
                if(d[a][z]+g[z][i].second<d[a][g[z][i].first])
                {
                    d[a][g[z][i].first] = d[a][z]+g[z][i].second;
                    q.push({-d[a][g[z][i].first],g[z][i].first});
                }
            }
        }
    }
}

using namespace std;

int main()
{
    ifstream infile("butter.in");
    ofstream outfile("butter.out");
    infile >> n >> p >> c;
    int a, b, e, ans = INF;
    vector<int> cow;
    for(int i = 0; i<n; i++)
    {
        infile >> a;
        cow.push_back(a-1);
    }
    for(int i = 0; i<c; i++)
    {
        infile >> a >> b >> e;
        g[a-1].push_back({b-1,e});
        g[b-1].push_back({a-1,e});
    }
    for(int i = 0; i<p; i++)
    {
        dij(i);
    }
    for(int i = 0; i<p; i++)
    {
        int tot = 0;
        for(int j = 0; j<n; j++)
        {
            tot+=d[cow[j]][i];
        }
        ans = min(ans,tot);
    }
    outfile << ans << endl;
}
