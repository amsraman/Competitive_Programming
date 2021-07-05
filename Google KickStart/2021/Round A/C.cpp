#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int t, r, c, g[300][300];
pair<int,int> dir[4] = {{0,1},{0,-1},{1,0},{-1,0}};
bool vis[300][300];
ll ans;

bool ok(int x, int y, int d1, int d2)
{
    return (x+d1>=0&&x+d1<r&&y+d2>=0&&y+d2<c);
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> r >> c;
        for(int i = 0; i<r; i++)
            for(int j = 0; j<c; j++)
                cin >> g[i][j];
        priority_queue<array<int,3>> q;
        for(int i = 0; i<r; i++)
            for(int j = 0; j<c; j++)
                q.push({g[i][j],i,j}), vis[i][j] = false;
        ans = 0;
        while(!q.empty())
        {
            int x = q.top()[1], y = q.top()[2];
            q.pop();
            if(vis[x][y])
                continue;
            vis[x][y] = true;
            for(pair<int,int> d: dir)
                if(ok(x,y,d.f,d.s)&&g[x+d.f][y+d.s]<g[x][y]-1)
                    ans+=(g[x][y]-1-g[x+d.f][y+d.s]), g[x+d.f][y+d.s] = g[x][y]-1, q.push({g[x+d.f][y+d.s],x+d.f,y+d.s});
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}