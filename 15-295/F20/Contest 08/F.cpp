#include <bits/stdc++.h>
#define f first
#define s second
#define INF 0x3f3f3f3f

using namespace std;

int n, k, edge[106][106], cost[106][106], path[106], dist[106], flow, ans;
string s1, s2, key;
vector<int> g[106];

int ctoi(char x)
{
    return (x>='a'?x-'a':x-'A'+26);
}

char itoc(int x)
{
    return (x>=26?x-26+'A':x+'a');
}

void addEdge(int x, int y)
{
    g[x].push_back(y);
    g[y].push_back(x);
    edge[x][y] = 1, cost[x][y] = 2000000, cost[y][x] = -2000000;
}

bool bellman_ford()
{
    for(int i = 1; i<106; i++)
        dist[i] = 0x3f3f3f3f;
    for(int i = 0; i<105; i++)
        for(int j = 0; j<106; j++)
            for(int k = 0; k<g[j].size(); k++)
                if(edge[j][g[j][k]]>0&&dist[j]+cost[j][g[j][k]]<dist[g[j][k]])
                    dist[g[j][k]] = dist[j]+cost[j][g[j][k]], path[g[j][k]] = j;
    return dist[105]!=0x3f3f3f3f;
}

int main()
{
    cin >> n >> k >> s1 >> s2;
    for(int i = 1; i<53; i++)
        addEdge(0,i);
    for(int i = 1; i<53; i++)
        for(int j = 53; j<105; j++)
            addEdge(i,j);
    for(int i = 53; i<105; i++)
        addEdge(i,105);
    for(int i = 0; i<n; i++)
    {
        int l1 = ctoi(s1[i]), l2 = ctoi(s2[i]);
        cost[l1+1][l2+53]--, cost[l2+53][l1+1]++;
    }
    while(bellman_ford())
    {
        int a = 105;
        while(a!=0)
        {
            edge[path[a]][a]--;
            edge[a][path[a]]++;
            a = path[a];
        }
    }
    for(int i = 1; i<53; i++)
        for(int j = 53; j<105; j++)
            if(edge[j][i]==1)
                ans+=(2000000-cost[i][j]), key+=itoc(j-53);
    cout << ans << endl;
    for(int i = 0; i<k; i++)
        cout << key[i];
    cout << endl;
}