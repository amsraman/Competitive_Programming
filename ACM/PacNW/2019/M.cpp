#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, ans = -1;
pair<int,int> dir[4] = {{0,-1},{-1,0},{0,1},{1,0}};
string maze[1000];
bool blocked[2002][2002];

bool ok(int x, int y, int z)
{
    return (x+dir[z].f>=0&&x+dir[z].f<2*n+2&&y+dir[z].s>=0&&y+dir[z].s<2*m+2);
}

void dfs(int x, int y)
{
    blocked[x][y] = true;
    for(int i = 0; i<4; i++)
        if(ok(x,y,i)&&!blocked[x+dir[i].f][y+dir[i].s])
            dfs(x+dir[i].f,y+dir[i].s);
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i<n; i++)
        cin >> maze[i];
    for(int i = 0; i<n; i++)
        for(int j = 0; j<m; j++)
        {
            if(maze[i][j]=='/')
                blocked[2*i+2][2*j+1] = blocked[2*i+1][2*j+2] = true;
            if(maze[i][j]=='\\')
                blocked[2*i+1][2*j+1] = blocked[2*i+2][2*j+2] = true;
        }
    for(int i = 0; i<2*n+2; i++)
        for(int j = 0; j<2*m+2; j++)  
            if(!blocked[i][j])
                dfs(i,j), ++ans;
    cout << ans << endl;
}