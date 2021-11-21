#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, m, k, link[200000], sz[200000];
ll sum;
vector<array<int,3>> edges;

int f(int x)
{
    return (x==link[x]?x:link[x]=f(link[x]));
}

void unite(int x, int y)
{
    x = f(x), y = f(y);
    if(sz[x]<sz[y])
        swap(x,y);
    link[y] = x, sz[x]+=sz[y];
}

int mst()
{
    int ret = 0;
    sum = 0;
    for(int i = 0; i<n; i++)
        link[i] = i, sz[i] = 1;
    for(int i = 0; i<m; i++)
        if(f(edges[i][1])!=f(edges[i][2]))
            unite(edges[i][1],edges[i][2]), sum+=(ll)edges[i][0], ret = max(ret,edges[i][0]);
    return ret;
}

int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n >> m >> k;
        for(int i = 0, x, y, s; i<m; i++)
        {
            cin >> x >> y >> s;
            edges.push_back({s,x-1,y-1});
        }
        sort(edges.begin(),edges.end());
        int tmp = mst();
        if(tmp<=k)
        {
            int ans = 1e9;
            for(int i = 0; i<m; i++)
                ans = min(ans,abs(edges[i][0]-k));
            cout << ans << endl;
        }
        else
        {
            for(int i = 0; i<m; i++)
                edges[i][0] = max(0,edges[i][0]-k);
            sort(edges.begin(),edges.end());
            mst();
            cout << sum << endl;
        }
        edges.clear();
    }
}