/*
ID: adityasund1
TASK: comehome
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;

int main()
{
    ifstream infile("comehome.in");
    ofstream outfile("comehome.out");
    int n, x, y, e;
    vector<pair<int,int> > g[52];
    infile >> n;
    char a, b;
    for(int i = 0; i<n; i++)
    {
        infile >> a >> b >> e;
        if(a>'`')
        {
            x = 26+(a-'a');
        }
        else
        {
            x = a-'A';
        }
        if(b>'`')
        {
            y = 26+(b-'a');
        }
        else
        {
            y = b-'A';
        }
        g[x].push_back({y,e});
        g[y].push_back({x,e});
    }
    priority_queue<pair<int,int> > q;
    q.push({0,25});
    char w;
    int d[52], ans = INF;
    for(int i = 0; i<52; i++)
    {
        d[i] = INF;
    }
    d[25] = 0;
    bool v[52] = {false};
    while(!q.empty())
    {
        e = q.top().second;
        q.pop();
        if(!v[e])
        {
            v[e] = true;
            for(int i = 0; i<g[e].size(); i++)
            {
                if((d[e]+g[e][i].second<d[g[e][i].first])&&(!v[g[e][i].first]))
                {
                    d[g[e][i].first] = d[e]+g[e][i].second;
                    q.push({-d[g[e][i].first],g[e][i].first});
                }
            }
        }
    }
    for(int i = 0; i<25; i++)
    {
        if(ans>d[i])
        {
            w = 'A'+i;
            ans = d[i];
        }
    }
    outfile << w << " " << ans << endl;
}
