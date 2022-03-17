#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int r, c, k;
pair<int,int> dir[8] = {{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
char grid[10][10];
string word;
bool dp[100][10][10][8][99], ans;
//amount left, x_pos, y_pos, direction, kinks left

bool ok(int x, int y, int d)
{
    return (x+dir[d].f>=0&&x+dir[d].f<r&&y+dir[d].s>=0&&y+dir[d].s<c);
}

int main()
{
    cin >> r >> c;
    for(int i = 0; i<r; i++)
        for(int j = 0; j<c; j++)
            cin >> grid[i][j];
    cin >> k >> word;
    for(int p1 = 0; p1<r; p1++)
        for(int p2 = 0; p2<c; p2++)
            if(grid[p1][p2]==word[word.length()-1])
                for(int dr = 0; dr<8; dr++)
                    dp[0][p1][p2][dr][0] = true, ans|=(word.length()==1&&k==0);
    for(int i = 1; i<word.length(); i++)
        for(int p1 = 0; p1<r; p1++)
            for(int p2 = 0; p2<c; p2++)
                for(int dr = 0; dr<8; dr++)
                    for(int kl = min(k,(int)word.length()-2); kl>=0; kl--)
                    {
                        for(int dr2 = 0; dr2<8; dr2++)
                        {
                            if((dr==dr2||i==word.length()-1)&&ok(p1,p2,dr2))
                                dp[i][p1][p2][dr][kl]|=(grid[p1][p2]==word[word.length()-i-1]&&dp[i-1][p1+dir[dr2].f][p2+dir[dr2].s][dr2][kl]);
                            if((dr!=dr2&&i!=word.length()-1)&&ok(p1,p2,dr2)&&kl>0)
                                dp[i][p1][p2][dr][kl]|=(grid[p1][p2]==word[word.length()-i-1]&&dp[i-1][p1+dir[dr2].f][p2+dir[dr2].s][dr2][kl-1]);
                        }
                        if(i==word.length()-1&&kl==k)
                            ans|=dp[i][p1][p2][dr][kl];
                    }
    cout << (ans?"Yes":"No") << endl;
}