#include <bits/stdc++.h>

using namespace std;

int t, r, c, f, s, edge[202][202], cost[202][202], dist[202], path[202], ans;
string bad[10], good[10];
vector<int> g[202];

void addEdge(int x, int y, int z)
{
    g[x].push_back(y);
    g[y].push_back(x);
    edge[x][y] = 1, cost[x][y] = z, cost[y][x] = -z;
}

bool bellman_ford()
{
    for(int i = 1; i<2*r*c+2; i++)
        dist[i] = 0x3f3f3f3f;
    for(int i = 0; i<2*r*c+2; i++)
        for(int j = 0; j<2*r*c+2; j++)
            for(int k = 0; k<g[j].size(); k++)
                if(edge[j][g[j][k]]>0&&dist[j]+cost[j][g[j][k]]<dist[g[j][k]])
                    dist[g[j][k]] = dist[j]+cost[j][g[j][k]], path[g[j][k]] = j;
    return dist[2*r*c+1]!=0x3f3f3f3f;
}


int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> r >> c >> f >> s;
        for(int i = 0; i<r; i++)
            cin >> bad[i];
        for(int i = 0; i<r; i++)
            cin >> good[i];
        for(int i = 0; i<r; i++)
            for(int j = 0; j<c; j++)
            {
                addEdge(0,c*i+j+1,0);
                addEdge(0,r*c+c*i+j+1,2*f);
                addEdge(r*c+c*i+j+1,2*r*c+1,0);
                for(int x = 0; x<r; x++)
                    for(int y = 0; y<c; y++)
                        if(bad[i][j]==good[x][y])
                            addEdge(c*i+j+1,r*c+c*x+y+1,(abs(i-x)+abs(j-y))*s);
            }
        ans = 0;
        while(bellman_ford())
        {
            ans+=dist[2*r*c+1];
            int a = 2*r*c+1;
            while(a!=0)
            {
                edge[path[a]][a]--;
                edge[a][path[a]]++;
                a = path[a];
            }
        }
        cout << "Case #" << _ << ": " << ans/2 << endl;
        for(int i = 0; i<2*r*c+2; i++)
            g[i].clear();
        for(int i = 0; i<2*r*c+2; i++)
            for(int j = 0; j<2*r*c+2; j++)
                cost[i][j] = edge[i][j] = 0;
    }
}