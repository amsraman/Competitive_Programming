#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, r, c, grid[1000][1000], hstreak[1000][1000][2], vstreak[1000][1000][2];
ll ans;

int num_L(int shorter_side, int longer_side)
{
    int biggest = min(shorter_side,longer_side/2);
    return max(0,biggest-1);
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> r >> c;
        for(int i = 0; i<r; i++)
            for(int j = 0; j<c; j++)
                cin >> grid[i][j];
        ans = 0;
        for(int i = 0; i<c; i++)
            vstreak[0][i][0] = (grid[0][i]==1), vstreak[r-1][i][1] = (grid[r-1][i]==1);
        for(int i = 1; i<r; i++)
            for(int j = 0; j<c; j++)
                vstreak[i][j][0] = (grid[i][j]==1?vstreak[i-1][j][0]+1:0);
        for(int i = r-2; i>=0; i--)
            for(int j = 0; j<c; j++)
                vstreak[i][j][1] = (grid[i][j]==1?vstreak[i+1][j][1]+1:0);
        for(int i = 0; i<r; i++)
            hstreak[i][0][0] = (grid[i][0]==1), hstreak[i][c-1][1] = (grid[i][c-1]==1);
        for(int i = 0; i<r; i++)
            for(int j = 1; j<c; j++)
                hstreak[i][j][0] = (grid[i][j]==1?hstreak[i][j-1][0]+1:0);
        for(int i = 0; i<r; i++)
            for(int j = c-2; j>=0; j--)
                hstreak[i][j][1] = (grid[i][j]==1?hstreak[i][j+1][1]+1:0);
        for(int i = 0; i<r; i++)
            for(int j = 0; j<c; j++)
            {
                //4 possible orientations of an L
                //2 possible choices of which is the longer side
                for(int o1 = 0; o1<2; o1++)
                    for(int o2 = 0; o2<2; o2++)
                        ans+=(num_L(hstreak[i][j][o1],vstreak[i][j][o2])+num_L(vstreak[i][j][o2],hstreak[i][j][o1]));
            }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}