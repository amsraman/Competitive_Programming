#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, a[500][500], b[500][500], r[500], c[500], link[1000], sz[1000];
ll ans;
vector<array<int,3>> edges;

int f(int x)
{
    return (x==link[x]?x:link[x] = f(link[x]));
}

void unite(int x, int y)
{
    x = f(x), y = f(y);
    if(sz[x]<sz[y])
        swap(x,y);
    link[y] = x, sz[x]+=sz[y];
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
                cin >> a[i][j];
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
                cin >> b[i][j];
        for(int i = 0; i<n; i++)
            cin >> r[i];
        for(int i = 0; i<n; i++)
            cin >> c[i];
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
                if(a[i][j]==-1)
                    edges.push_back({b[i][j],i,n+j}), ans+=b[i][j];
        sort(edges.begin(),edges.end());
        for(int i = 0; i<2*n; i++)
            link[i] = i, sz[i] = 1;
        for(int i = edges.size()-1; i>=0; i--)
            if(f(edges[i][1])!=f(edges[i][2]))
                unite(edges[i][1],edges[i][2]), ans-=edges[i][0];
        cout << "Case #" << _ << ": " << ans << endl;
        ans = 0, edges.clear();
    }
}