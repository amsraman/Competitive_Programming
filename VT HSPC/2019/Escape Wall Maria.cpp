#include <bits/stdc++.h>

using namespace std;

int t, n, m, d[100][100], ans = 0x3f3f3f3f;
char arr[100][100];
queue<pair<int,int> > q;

int main()
{
    memset(d,0x3f3f3f3f,sizeof(d));
    cin >> t >> n >> m;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<m; j++)
        {
            cin >> arr[i][j];
            if(arr[i][j]=='S') q.push({i,j}), d[i][j] = 0;
        }
    }
    while(!q.empty())
    {
        int x = q.front().first, y = q.front().second;
        q.pop();
        if((x>0)&&((arr[x-1][y]=='0')||(arr[x-1][y]=='D'))&&(d[x-1][y]==0x3f3f3f3f))
        {
            q.push({x-1,y});
            d[x-1][y] = d[x][y]+1;
        }
        if((x<n-1)&&((arr[x+1][y]=='0')||(arr[x+1][y]=='U'))&&(d[x+1][y]==0x3f3f3f3f))
        {
            q.push({x+1,y});
            d[x+1][y] = d[x][y]+1;
        }
        if((y>0)&&((arr[x][y-1]=='0')||(arr[x][y-1]=='R'))&&(d[x][y-1]==0x3f3f3f3f))
        {
            q.push({x,y-1});
            d[x][y-1] = d[x][y]+1;
        }
        if((y<m-1)&&((arr[x][y+1]=='0')||(arr[x][y+1]=='L'))&&(d[x][y+1]==0x3f3f3f3f))
        {
            q.push({x,y+1});
            d[x][y+1] = d[x][y]+1;
        }
    }
    for(int i = 0; i<n; i++) ans = min(ans,d[i][0]), ans = min(ans,d[i][m-1]);
    for(int i = 0; i<m; i++) ans = min(ans,d[0][i]), ans = min(ans,d[n-1][i]);
    if(ans>t) cout << "NOT POSSIBLE" << endl;
    else cout << ans << endl;
}
