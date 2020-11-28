#include <bits/stdc++.h>

using namespace std;

int n, a, b, sz[100000], ct[100000];
vector<int> g[100000], sub[100000];

int dfs(int a, int p)
{
    sz[a] = 1;
    for(int i = 0; i<g[a].size(); i++)
        if(g[a][i]!=p)
            dfs(g[a][i],a), sz[a]+=sz[g[a][i]], sub[a].push_back(sz[g[a][i]]);
}

bool ok(int k)
{
    memset(ct,0,sizeof(ct));
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<sub[i].size(); j++)
            ct[sub[i][j]%k]++;
        ct[(sz[i]-1)%k]--;
        for(int j = 0; j<sub[i].size(); j++)
            if((ct[sub[i][j]%k])&&(ct[sub[i][j]%k]!=ct[(k-sub[i][j]%k)%k]))
                return false;
        for(int j = 0; j<sub[i].size(); j++)
            ct[sub[i][j]%k] = 0;
        ct[(sz[i]-1)%k] = 0;
    }
    return true;
}

int main()
{
    freopen("deleg.in","r",stdin);
    freopen("deleg.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n-1; i++)
    {
        cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    dfs(0,0);
    for(int i = 1; i<n; i++)
    {
        if((n-1)%i)
            cout << 0;
        else
            cout << ok(i);
    }
    cout << endl;
}
