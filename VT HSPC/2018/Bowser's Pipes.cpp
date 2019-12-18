#include <bits/stdc++.h>

using namespace std;

int n, f, a, d, type[100000], cc, id[100000], dist[100000], best[100000];
vector<int> g[100000];

void dfs(int x, int y)
{
    id[x] = cc;
    dist[x] = y;
    if((!type[x])&&((best[cc]==0x3f3f3f3f)||(dist[best[cc]]>y))) best[cc] = x;
    if((!type[x])&&((best[cc]==0x3f3f3f3f)||(dist[best[cc]]==y))) best[cc] = min(best[cc],x);
    for(int i = 0; i<g[x].size(); i++)
    {
        dfs(g[x][i],y+1);
    }
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        cin >> f;
        if(f==-1)
        {
            type[i] = 2;
        }
        else
        {
            type[f] = max(type[f],1);
            g[f].push_back(i);
        }
    }
    memset(best,0x3f3f3f3f,sizeof(best));
    for(int i = 0; i<n; i++)
    {
        if(type[i]==2)
        {
            dfs(i,0);
            cc++;
        }
    }
    cin >> a;
    for(int i = 0; i<a; i++)
    {
        cin >> d;
        cout << best[id[d]] << endl;
    }
}
