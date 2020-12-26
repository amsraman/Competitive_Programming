#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, xt, yt, xm, ym, dist[1000][1000][4], ans;
pair<int,int> dir[4] = {{-1,0},{0,1},{1,0},{0,-1}};
vector<pair<int,int>> g[1000][1000][4];
string grid[1000];
bool doors[1000][1000][4][4], vis[1000][1000][4];

bool ok(int x, int y, int d)
{
    return ((x+dir[d].f>=0)&&(x+dir[d].f<n)&&(y+dir[d].s>=0)&&(y+dir[d].s<m));
}

bool conn(int x, int y, int c, int d)
{
    return (doors[x][y][c][d]&&doors[x+dir[d].f][y+dir[d].s][c][(d+2)%4]);
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i<n; i++)
        cin >> grid[i];
    cin >> xt >> yt >> xm >> ym;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<m; j++)
        {
            if((grid[i][j]=='+')||(grid[i][j]=='|')||(grid[i][j]=='^')||(grid[i][j]=='L')||(grid[i][j]=='R')||(grid[i][j]=='D'))
                for(int k = 0; k<4; k++)
                    if(ok(i,j,k))
                        doors[i][j][k][k] = true;
            if((grid[i][j]=='+')||(grid[i][j]=='-')||(grid[i][j]=='>')||(grid[i][j]=='L')||(grid[i][j]=='U')||(grid[i][j]=='D'))
                for(int k = 0; k<4; k++)
                    if(ok(i,j,(k+1)%4))
                        doors[i][j][k][(k+1)%4] = true;
            if((grid[i][j]=='+')||(grid[i][j]=='|')||(grid[i][j]=='v')||(grid[i][j]=='L')||(grid[i][j]=='R')||(grid[i][j]=='U'))
                for(int k = 0; k<4; k++)
                    if(ok(i,j,(k+2)%4))
                        doors[i][j][k][(k+2)%4] = true;
            if((grid[i][j]=='+')||(grid[i][j]=='-')||(grid[i][j]=='<')||(grid[i][j]=='U')||(grid[i][j]=='R')||(grid[i][j]=='D'))
                for(int k = 0; k<4; k++)
                    if(ok(i,j,(k+3)%4))
                        doors[i][j][k][(k+3)%4] = true;
        }
    queue<pair<pair<int,int>,int>> q;
    q.push({{xt-1,yt-1},0}), vis[xt-1][yt-1][0] = true;
    while(!q.empty())
    {
        int x = q.front().f.f, y = q.front().f.s, z = q.front().s;
        q.pop();
        if(!vis[x][y][(z+1)%4])
        {
            q.push({{x,y},(z+1)%4});
            dist[x][y][(z+1)%4] = dist[x][y][z]+1;
            vis[x][y][(z+1)%4] = true;
        }
        for(int i = 0; i<4; i++)
            if(conn(x,y,z,i)&&!vis[x+dir[i].f][y+dir[i].s][z])
            {
                q.push({{x+dir[i].f,y+dir[i].s},z});
                dist[x+dir[i].f][y+dir[i].s][z] = dist[x][y][z]+1;
                vis[x+dir[i].f][y+dir[i].s][z] = true;
            }
    }
    ans = 0x3f3f3f3f;
    for(int i = 0; i<4; i++)
        if(vis[xm-1][ym-1][i])
            ans = min(ans,dist[xm-1][ym-1][i]);
    cout << (ans==0x3f3f3f3f?-1:ans) << endl;
}