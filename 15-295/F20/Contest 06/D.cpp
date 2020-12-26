#include <bits/stdc++.h>
#define f first
#define s second
 
using namespace std;
 
int n, m, danger[700][700], dist1[700][700], dist2[700][700];
pair<int,int> dir[4] = {{-1,0},{0,-1},{1,0},{0,1}}, st, vik, en;
string grid[700];
bool hdone[700][700], vdone[700][700], vis1[700][700], vis2[700][700];
 
bool ok(int x, int y, int d)
{
    return (x+dir[d].f>=0&&x+dir[d].f<n&&y+dir[d].s>=0&&y+dir[d].s<m);
}
 
int main()
{
    cin >> n >> m;
    for(int i = 0; i<n; i++)
        cin >> grid[i];
    for(int i = 0; i<n; i++)
        for(int j = 0; j<m; j++)
        {
            if(grid[i][j]=='Y')
                st = {i,j};
            if(grid[i][j]=='V')
                vik = {i,j};
            if(grid[i][j]=='T')
                en = {i,j};
        }
    queue<pair<int,int>> q1, q2;
    q1.push(vik);
    memset(danger,0x3f3f3f3f,sizeof(danger));
    while(!q1.empty())
    {
        int x = q1.front().f, y = q1.front().s;
        q1.pop();
        //do some checking thing :)
        if(!hdone[x][y])
        {
            for(int i = y; ((i<m)&&(grid[x][i]!='I')); i++)
                danger[x][i] = min(danger[x][i],dist1[x][y]), hdone[x][y] = true;
            for(int i = y; ((i>=0)&&(grid[x][i]!='I')); i--)
                danger[x][i] = min(danger[x][i],dist1[x][y]), hdone[x][y] = true;
        }
        if(!vdone[x][y])
        {
            for(int i = x; ((i<n)&&(grid[i][y]!='I')); i++)
                danger[i][y] = min(danger[i][y],dist1[x][y]), vdone[x][y] = true;
            for(int i = x; ((i>=0)&&(grid[i][y]!='I')); i--)
                danger[i][y] = min(danger[i][y],dist1[x][y]), vdone[x][y] = true;
        }
        for(int i = 0; i<4; i++)
            if(ok(x,y,i)&&!vis1[x+dir[i].f][y+dir[i].s]&&grid[x+dir[i].f][y+dir[i].s]!='I')
                dist1[x+dir[i].f][y+dir[i].s] = dist1[x][y]+1, vis1[x+dir[i].f][y+dir[i].s] = true, q1.push({x+dir[i].f,y+dir[i].s});
    }
    q2.push(st);
    while(!q2.empty())
    {
        int x = q2.front().f, y = q2.front().s;
        q2.pop();
        for(int i = 0; i<4; i++)
            if(ok(x,y,i)&&!vis2[x+dir[i].f][y+dir[i].s]&&grid[x+dir[i].f][y+dir[i].s]!='I'&&danger[x+dir[i].f][y+dir[i].s]>dist2[x][y]+1)
                dist2[x+dir[i].f][y+dir[i].s] = dist2[x][y]+1, vis2[x+dir[i].f][y+dir[i].s] = true, q2.push({x+dir[i].f,y+dir[i].s});
    }
    cout << (vis2[en.f][en.s]?"YES":"NO") << endl;
}