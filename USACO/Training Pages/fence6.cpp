/*
ID: adityasund1
TASK: fence6
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;

int n, d[100], node[100][100], nc = 0, ans = INF, s, l, n1, n2, node1, node2, ar1[9], ar2[9];
bool ee[100][100], v[100];
vector<pair<int,int> > g[100];

void dij(int a)
{
    priority_queue<pair<int,int> > q;
    for(int i = 0; i<g[a].size(); i++)
    {
        for(int j = 0; j<nc; j++){d[j] = INF;v[j] = false;}
        q.push({0,g[a][i].second});
        while(!q.empty())
        {
            int x = q.top().first, y = q.top().second;
            q.pop();
            if(!v[y])
            {
                v[y] = true;
                for(int j = 0; j<g[y].size(); j++)
                {
                    if((y!=g[a][i].second)||(g[y][j].second!=a))
                    {
                        d[g[y][j].second] = min(d[g[y][j].second],g[y][j].first-x);
                        q.push({x-g[y][j].first,g[y][j].second});
                    }
                }
            }
            ans = min(ans,d[a]+g[a][i].first);
        }
    }
}

int main()
{
    ifstream infile("fence6.in");
    ofstream outfile("fence6.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> s >> l >> n1 >> n2;
        node1 = node2 = -1;
        ar1[0] = ar2[0] = s;
        for(int j = 0; j<n1; j++)
        {
            infile >> ar1[j+1];
            if(ee[s-1][ar1[j+1]-1]){node1 = node[s-1][ar1[j+1]-1];}
            if((!ee[s-1][ar1[j+1]-1])&&(node1==-1))
            {
                node1 = nc;
                nc++;
            }
        }
        for(int j = 0; j<=n1; j++)
        {
            for(int k = j+1; k<=n1; k++)
            {
                ee[ar1[j]-1][ar1[k]-1] = ee[ar1[k]-1][ar1[j]-1] = true;
                node[ar1[j]-1][ar1[k]-1] = node[ar1[k]-1][ar1[j]-1] = node1;
            }
        }
        for(int j = 0; j<n2; j++)
        {
            infile >> ar2[j+1];
            if(ee[s-1][ar2[j+1]-1]){node2 = node[s-1][ar2[j+1]-1];}
            if((!ee[s-1][ar2[j+1]-1])&&(node2==-1))
            {
                node2 = nc;
                nc++;
            }
        }
        for(int j = 0; j<=n2; j++)
        {
            for(int k = j+1; k<=n2; k++)
            {
                ee[ar2[j]-1][ar2[k]-1] = ee[ar2[k]-1][ar2[j]-1] = true;
                node[ar2[j]-1][ar2[k]-1] = node[ar2[k]-1][ar2[j]-1] = node2;
            }
        }
        g[node1].push_back({l,node2});
        g[node2].push_back({l,node1});
    }
    for(int i = 0; i<nc; i++){dij(i);}
    outfile << ans << endl;
}
