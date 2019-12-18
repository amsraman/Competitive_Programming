#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

int r, c, n, edge[50][50], dp[(1<<15)][15], ans = INF;
pair<int,int> st[15], dir[4] = {{-1,0},{0,1},{1,0},{0,-1}};
char grid[50][50];
bool v[50][50];

bool ok(int a, int b)
{
    return ((a>=0)&&(a<r)&&(b>=0)&&(b<c)&&(!v[a][b]));
}

void dfs(int a, int b)
{
    grid[a][b] = ('a'+n);
    if((a>0)&&(grid[a-1][b]=='X')) dfs(a-1,b);
    if((b>0)&&(grid[a][b-1]=='X')) dfs(a,b-1);
    if((a<r-1)&&(grid[a+1][b]=='X')) dfs(a+1,b);
    if((b<c-1)&&(grid[a][b+1]=='X')) dfs(a,b+1);
}

void bfs(int a)
{
    for(int i = 0; i<r; i++) for(int j = 0; j<c; j++) v[i][j] = false;
    priority_queue<pair<int,pair<int,int> > > q;
    q.push({0,st[a]});
    v[st[a].first][st[a].second] = true;
    while(!q.empty())
    {
        int w = q.top().first, x = q.top().second.first, y = q.top().second.second, g = int(grid[x][y]-'a');
        if((edge[a][g]==0)&&(grid[x][y]!='S')&&(g!=a)) edge[a][g] = -w;
        q.pop();
        for(int i = 0; i<4; i++)
        {
            int nx = x+dir[i].first, ny = y+dir[i].second;
            if(ok(nx,ny)&&((grid[x][y]=='S')||(g==a))&&(grid[nx][ny]=='S')) q.push({w-1,{nx,ny}}), v[nx][ny] = true;
            else if(ok(nx,ny)&&((grid[x][y]=='S')||(g==a))&&(grid[nx][ny]!='.')) q.push({w,{nx,ny}}), v[nx][ny] = true;
        }
    }
}

int main()
{
    freopen("island.in","r",stdin);
    freopen("island.out","w",stdout);
    cin >> r >> c;
    for(int i = 0; i<r; i++)
    {
        for(int j = 0; j<c; j++)
        {
            cin >> grid[i][j];
        }
    }
    for(int i = 0; i<r; i++)
    {
        for(int j = 0; j<c; j++)
        {
            if(grid[i][j]=='X')
            {
                st[n] = {i,j};
                dfs(i,j);
                n++;
            }
        }
    }
    for(int i = 0; i<n; i++) bfs(i);
    for(int i = 0; i<(1<<n); i++) for(int j = 0; j<n; j++) dp[i][j] = INF;
    for(int i = 0; i<(1<<n); i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(i&(1<<j))
            {
                if(i==(1<<j)) dp[i][j] = 0;
                for(int k = 0; k<n; k++)
                {
                    if(edge[j][k]!=0) dp[i|(1<<k)][k] = min(dp[i|(1<<k)][k],dp[i][j]+edge[j][k]);
                }
            }
        }
    }
    for(int i = 0; i<n; i++) ans = min(ans,dp[(1<<n)-1][i]);
    cout << ans << endl;
}
