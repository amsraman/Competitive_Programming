#include <bits/stdc++.h>

using namespace std;

int n, k, num[100000], ans;
vector<int> g[100000];
bool ap[100000];

void dfs(int x, int p)
{
    int tmp = 0;
    for(int i: g[x])
        if(i!=p)
            dfs(i,x), num[x]+=num[i], tmp+=(num[x]>0);
    tmp+=(k-num[x]>0);
    ans+=(tmp>1||ap[x]);
}

int main()
{
    cin >> n >> k;
    for(int i = 0, u, v, w; i<n-1; i++)
    {
        cin >> u >> v >> w;
        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }
    for(int i = 0, u; i<k; i++)
    {
        cin >> u;
        ap[u-1] = true, ++num[u-1];
    }
    dfs(0,0);
    cout << ans << endl;
}