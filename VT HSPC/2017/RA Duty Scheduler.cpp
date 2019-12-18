#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

int m, n, d, day, edge[930][930], curedge[930][930], level[930], ptr[930], flow;
string names[60];
vector<int> g[930];

int dfs(int a, int c, int t)
{
    if(a==t) return c;
    while(ptr[a]<g[a].size())
    {
        while((ptr[a]<g[a].size())&&((level[g[a][ptr[a]]]!=level[a]+1)||(curedge[a][g[a][ptr[a]]]==0))) ptr[a]++;
        if(ptr[a]==g[a].size()) continue;
        int k = dfs(g[a][ptr[a]],min(c,curedge[a][g[a][ptr[a]]]),t);
        if(k!=0)
        {
            curedge[a][g[a][ptr[a]]]-=k;
            curedge[g[a][ptr[a]]][a]+=k;
            return k;
        }
        else ptr[a]++;
    }
    return 0;
}

int dinic_flow(int a, int b)
{
    bool lg = true;
    while(lg)
    {
        for(int i = 0; i<m+n+2; i++) level[i] = ptr[i] = 0;
        queue<int> q;
        q.push(a), level[a] = 1;
        while(!q.empty())
        {
            int z = q.front();
            q.pop();
            for(int i = 0; i<g[z].size(); i++)
                if((level[g[z][i]]==0)&&(curedge[z][g[z][i]]!=0))
                    level[g[z][i]] = level[z]+1, q.push(g[z][i]);
        }
        lg = (level[b]!=0);
        if(!lg) continue;
        while(int p = dfs(a,INF,b)) flow+=p;
    }
    return flow;
}

int main()
{
    cin >> m >> n;
    for(int i = 0; i<m; i++)
    {
        cin >> names[i] >> d;
        g[0].push_back(i+1);
        g[i+1].push_back(0);
        for(int j = 0; j<d; j++)
        {
            cin >> day;
            g[i+1].push_back(day+m);
            g[day+m].push_back(i+1);
            edge[i+1][day+m] = 1;
        }
    }
    for(int i = 0; i<n; i++)
    {
        g[i+m+1].push_back(m+n+1);
        g[m+n+1].push_back(i+m+1);
        edge[i+m+1][m+n+1] = 2;
    }
    int l = 0, g = 2*n;
    while(l<=g)
    {
        int mid = (l+g)/2;
        if(l==g) l++;
        for(int i = 0; i<m+n+2; i++)
            for(int j = 0; j<m+n+2; j++)
                curedge[i][j] = edge[i][j];
        for(int i = 1; i<m+1; i++)
            curedge[0][i] = mid, flow = 0;
        if(dinic_flow(0,m+n+1)>=2*n) g = mid;
        else l = mid+1;
    }
    cout << g << endl;
    for(int i = 0; i<n; i++)
    {
        cout << "Day " << i+1 << ":";
        for(int j = 1; j<m+1; j++)
            if(curedge[i+m+1][j]&&edge[j][i+m+1])
                cout << " " << names[j-1];
        cout << endl;
    }
}
