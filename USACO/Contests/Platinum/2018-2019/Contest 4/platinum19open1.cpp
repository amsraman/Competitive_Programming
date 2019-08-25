#include "grader.h"
#include <vector>

using namespace std;

vector<int> g[100000];
int depth[100000], parent[100000][17], c1, c2;
pair<int,int> poin[100000];

void dfs1(int prev, int a)
{
    poin[a].first = ++c1;
    for(int i = 1; i<17; i++) parent[a][i] = parent[parent[a][i-1]][i-1];
    for(int i = 0; i<g[a].size(); i++)
    {
        if(g[a][i]!=prev)
        {
            depth[g[a][i]] = depth[a]+1;
            parent[g[a][i]][0] = a;
            dfs1(a,g[a][i]);
        }
    }
}

int lca(int a, int b)
{
    int i = 16, j = 16;
    while(depth[a]>depth[b])
    {
        if(depth[a]-depth[b]>=(1<<i)) a = parent[a][i];
        i--;
    }
    while(depth[b]>depth[a])
    {
        if(depth[b]-depth[a]>=(1<<i)) b = parent[b][i];
        i--;
    }
    while(a!=b)
    {
        if(j==-1){break;}
        if(parent[a][j]!=parent[b][j]) a = parent[a][j], b = parent[b][j];
        j--;
    }
    if(a==b) return a;
    return parent[a][0];
}


void dfs2(int a, int prev)
{
    poin[a].second = ++c2;
    for(int i = g[a].size()-1; i>=0; i--)
    {
        if(g[a][i]!=prev) dfs2(g[a][i],a);
    }
}

void addRoad(int a, int b)
{
    g[a].push_back(b);
    g[b].push_back(a);
}

void buildFarms()
{
    int n = getN();
    parent[0][0] = depth[0] = 0;
    dfs1(0,0);
    dfs2(0,0);
    for(int i = 0; i<n; i++) setFarmLocation(i,poin[i].first,poin[i].second);
}

void notifyFJ(int a, int b)
{
    int k = lca(a,b);
    if((a==k)||(b==k))
    {
        if(a!=k) addBox(poin[k].first,poin[k].second,poin[a].first,poin[a].second);
        else addBox(poin[k].first,poin[k].second,poin[b].first,poin[b].second);
    }
    else
    {
        addBox(poin[k].first,poin[k].second,poin[a].first,poin[a].second);
        if(poin[b].first>poin[a].first) addBox(poin[a].first,poin[k].second,poin[b].first,poin[b].second);
        if(poin[a].first>poin[b].first) addBox(poin[k].first,poin[a].second,poin[b].first,poin[b].second);
    }
}
