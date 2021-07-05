#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

int n, edge[502][502], level[502], ptr[502];
vector<int> g[502];
string words[500];

void addEdge(int x, int y, int z)
{
    g[x].push_back(y);
    g[y].push_back(x);
    edge[x][y] = z;
}

int dfs(int a, int c, int t)
{
    if(a==t) return c;
    while(ptr[a]<g[a].size())
    {
        while((ptr[a]<g[a].size())&&((level[g[a][ptr[a]]]!=level[a]+1)||(edge[a][g[a][ptr[a]]]==0))) ptr[a]++;
        if(ptr[a]==g[a].size()) continue;
        int k = dfs(g[a][ptr[a]],min(c,edge[a][g[a][ptr[a]]]),t);
        if(k!=0)
        {
            edge[a][g[a][ptr[a]]]-=k;
            edge[g[a][ptr[a]]][a]+=k;
            return k;
        }
        else ptr[a]++;
    }
    return 0;
}
 
int dinic_flow(int a, int b, int flow)
{
    bool lg = true;
    while(lg)
    {
        for(int i = 0; i<n+2; i++) level[i] = ptr[i] = 0;
        queue<int> q;
        q.push(a), level[a] = 1;
        while(!q.empty())
        {
            int z = q.front();
            q.pop();
            for(int i = 0; i<g[z].size(); i++)
                if((level[g[z][i]]==0)&&(edge[z][g[z][i]]!=0))
                    level[g[z][i]] = level[z]+1, q.push(g[z][i]);
        }
        lg = (level[b]!=0);
        if(!lg) continue;
        while(int p = dfs(a,INF,b)) flow+=p;
    }
    return flow;
}

bool swap_adj(int ind1, int ind2)
{
    int diff = 0;
    for(int i = 0; i<words[ind1].length(); i++)
        if(words[ind1][i]!=words[ind2][i])
            ++diff;
    return diff==2;
}

int inv_parity(int ind)
{
    int ret = 0;
    for(int i = 0; i<words[ind].length(); i++)
        for(int j = 0; j<i; j++)
            if(words[ind][j]>words[ind][i])
                ++ret;
    return ret&1;
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> words[i];
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            if(swap_adj(i,j)&&inv_parity(i))
                addEdge(i+1,j+1,INF);
    for(int i = 0; i<n; i++)
    {
        if(inv_parity(i))
            addEdge(0,i+1,1);
        else
            addEdge(i+1,n+1,1);
    }
    cout << n-dinic_flow(0,n+1,0) << endl;
}