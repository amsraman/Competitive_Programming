#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, k, parent[50000][17], val[50000], pre[50000], depth[50000], ans;
vector<int> g[50000];

void dfs(int prev, int a)
{
    for(int i = 1; (1<<i)<=depth[a]; i++)
    {
        parent[a][i] = parent[parent[a][i-1]][i-1];
    }
    for(int i = 0; i<g[a].size(); i++)
    {
        if(g[a][i]!=prev)
        {
            parent[g[a][i]][0] = a;
            depth[g[a][i]] = depth[a]+1;
            dfs(a,g[a][i]);
        }
    }
}

int lca(int a, int b)
{
    int k = 16;
    while(depth[a]>depth[b])
    {
        if(depth[a]-depth[b]>=(1<<k))
        {
            a = parent[a][k];
        }
        k--;
    }
    while(depth[b]>depth[a])
    {
        if(depth[b]-depth[a]>=(1<<k))
        {
            b = parent[b][k];
        }
        k--;
    }
    k = 16;
    while(a!=b)
    {
        if(k==-1){break;}
        if(parent[a][k]!=parent[b][k])
        {
            a = parent[a][k];
            b = parent[b][k];
        }
        k--;
    }
    if(a==b){return a;}
    return parent[a][0];
}

int dfs2(int a)
{
    pre[a] = val[a];
    for(int i = 0; i<g[a].size(); i++)
    {
        if(g[a][i]!=parent[a][0]){pre[a]+=dfs2(g[a][i]);}
    }
    ans = max(ans,pre[a]);
    return pre[a];
}

int main()
{
    ifstream infile("maxflow.in");
    ofstream outfile("maxflow.out");
    infile >> n >> k;
    int a, b;
    for(int i = 0; i<n-1; i++)
    {
        infile >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    dfs(0,0);
    for(int i = 0; i<k; i++)
    {
        infile >> a >> b;
        val[a-1]++;
        val[b-1]++;
        int k = lca(a-1,b-1);
        val[k]--;
        if(k!=0){val[parent[k][0]]--;}
    }
    dfs2(0);
    outfile << ans << endl;
}
