#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;

int t, n, h, x, a, b, edge[52][52], level[52], ptr[52], path[52], proj[100000], flow;
pair<int,pair<int,int> > in[50];
vector<int> g[52];

void add_edge(int y, int z, int c)
{
    edge[y][z]+=c, edge[z][y]+=c;
    if(edge[y][z]!=c) return;
    g[y].push_back(z);
    g[z].push_back(y);
}

int dfs(int cur, int m, int t)
{
    if(cur==t) return m;
    while(ptr[cur]<g[cur].size())
    {
        while((ptr[cur]<g[cur].size())&&((level[g[cur][ptr[cur]]]!=level[cur]+1)||(edge[cur][g[cur][ptr[cur]]]==0))) ptr[cur]++;
        if(ptr[cur]==g[cur].size()) continue;
        int k = dfs(g[cur][ptr[cur]],min(m,edge[cur][g[cur][ptr[cur]]]),t);
        if(k!=0)
        {
            edge[cur][g[cur][ptr[cur]]]-=k;
            edge[g[cur][ptr[cur]]][cur]+=k;
            return k;
        }
        else ptr[cur]++;
    }
    return 0;
}

void dinic_flow(int s, int t)
{
    bool lg = true;
    while(lg)
    {
        for(int i = 0; i<=n+1; i++) level[i] = ptr[i] = 0;
        level[s] = 1;
        queue<int> q;
        q.push(s);
        while(!q.empty())
        {
            int z = q.front();
            q.pop();
            for(int i = 0; i<g[z].size(); i++)
            {
                if((level[g[z][i]]==0)&&(edge[z][g[z][i]]!=0))
                {
                    level[g[z][i]] = level[z]+1;
                    q.push(g[z][i]);
                }
            }
        }
        lg = (level[t]!=0);
        if(!lg) continue;
        while(int p = dfs(s,INF,t)) flow+=p;
    }
}

int main()
{
    ifstream fin("ladders_and_snakes.txt");
    ofstream fout("output.txt");
    fin >> t;
    for(int z = 0; z<t; z++)
    {
        fin >> n >> h;
        for(int i = 0; i<n; i++)
        {
            fin >> x >> a >> b;
            in[i] = {x,{a,b}};
        }
        sort(in,in+n);
        for(int i = n-1; i>=0; i--)
        {
            int ctr = 0;
            if(in[i].second.first==0) add_edge(0,i+1,INF);
            if(in[i].second.second==h) add_edge(i+1,n+1,INF);
            for(int j = in[i].second.first; j<in[i].second.second; j++)
            {
                ctr++;
                if((j==in[i].second.second-1)||(proj[j]!=proj[j+1]))
                {
                    if(proj[j]!=0) add_edge(i+1,proj[j],ctr);
                    ctr = 0;
                }
                proj[j] = i+1;
            }
        }
        dinic_flow(0,n+1);
        fout << "Case #" << z+1 << ": " << ((flow>=INF)?(-1):(flow)) << endl;
        for(int i = 0; i<h; i++) proj[i] = 0;
        for(int i = 0; i<=n+1; i++) g[i].clear();
        for(int i = 0; i<=n+1; i++) for(int j = 0; j<=n+1; j++) flow = edge[i][j] = 0;
    }
}
