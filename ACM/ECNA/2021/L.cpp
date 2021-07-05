#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, apt[50][50][2], wst[50][50][2], mn = 0x3f3f3f3f, ind, dist[250], path[250], edge[250][250], cost[250][250], ans;
pair<int,pair<string,int>> assignment[200];
vector<int> g[250];

void addEdge(int x, int y, int z)
{
    g[x].push_back(y);
    g[y].push_back(x);
    edge[x][y] = 1, cost[x][y] = z, cost[y][x] = -z;
}

bool bellman_ford()
{
    for(int i = 1; i<4*n+2; i++)
        dist[i] = 0x3f3f3f3f;
    for(int i = 0; i<4*n+1; i++)
        for(int j = 0; j<4*n+1; j++)
            for(int k = 0; k<g[j].size(); k++)
                if(edge[j][g[j][k]]>0&&dist[j]+cost[j][g[j][k]]<dist[g[j][k]])
                    dist[g[j][k]] = dist[j]+cost[j][g[j][k]], path[g[j][k]] = j;
    return dist[4*n+1]!=0x3f3f3f3f;
}

int calc(int x)
{
    for(int i = 0; i<=4*n+1; i++)
        g[i].clear();
    for(int i = 0; i<=4*n+1; i++)
        for(int j = 0; j<=4*n+1; j++)
            edge[i][j] = cost[i][j] = 0;
    //construct graph
    for(int i = 0; i<n; i++)
        addEdge(n+i+1,2*n+i+1,0), addEdge(0,i+1,0), addEdge(3*n+i+1,4*n+1,0);
    for(int i = 0; i<x; i++)
        for(int j = 0; j<n; j++)
            addEdge(j+1,n+i+1,apt[j][i][0]), addEdge(2*n+i+1,3*n+j+1,wst[j][i][0]);
    for(int i = x; i<n; i++)
        for(int j = 0; j<n; j++)
            addEdge(j+1,n+i+1,apt[j][i][1]), addEdge(2*n+i+1,3*n+j+1,wst[j][i][1]);
    while(bellman_ford())
    {
        int a = 4*n+1;
        while(a!=0)
        {
            edge[path[a]][a]--;
            edge[a][path[a]]++;
            a = path[a];
        }
    }
    int ret = 0;
    for(int i = 1; i<=n; i++)
        for(int j = n+1; j<=2*n; j++)
            if(edge[j][i]==1)
                ret+=cost[i][j];
    for(int i = 2*n+1; i<=3*n; i++)
        for(int j = 3*n+1; j<=4*n; j++)
            if(edge[j][i]==1)
                ret+=cost[i][j];
    return ret;
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> apt[i][j][0] >> apt[i][j][1];
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> wst[i][j][0] >> wst[i][j][1];
    for(int i = 0; i<=n; i++)
    {
        int cur = calc(i);
        if(cur<mn)
            ind = i, mn = cur;
    }
    ans = calc(ind);
    //perform assignment
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
        {
            if(edge[n+i+1][j+1]==1)
                assignment[i].f = j+1;
            if(edge[3*n+j+1][2*n+i+1]==1)
                assignment[i].s.s = j+1;
        }
    for(int i = 0; i<n; i++)
    {
        if(i<ind)
            assignment[i].s.f = to_string(i+1)+'A';
        else
            assignment[i].s.f = to_string(i+1)+'B';
    }
    sort(assignment,assignment+n);
    cout << ans << endl;
    for(int i = 0; i<n; i++)
        cout << assignment[i].f << " " << assignment[i].s.f << " " << assignment[i].s.s << endl;
}