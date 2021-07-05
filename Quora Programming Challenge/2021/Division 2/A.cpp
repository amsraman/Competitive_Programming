#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int moves[42], board[7][6], ctr[7];
pair<int,int> dir[4] = {{0,1},{1,0},{1,1},{1,-1}};

int row_check(int player, int xpos, int ypos, int d)
{
    for(int i = 0; i<4; i++)
    {
        if(xpos<0||xpos>6||ypos<0||ypos>5||board[xpos][ypos]!=player)
            return false;
        xpos+=dir[d].f, ypos+=dir[d].s;
    }
    return true;
}

bool chk(int player, int xpos, int ypos)
{
    for(int d = 0; d<4; d++)
    {
        int tmp1 = xpos, tmp2 = ypos;
        for(int i = 0; i<4; i++)
        {
            if(row_check(player,tmp1,tmp2,d))
                return true;
            tmp1-=dir[d].f, tmp2-=dir[d].s;
        }
    }
    return false;
}

void solve()
{
    for(int i = 0; i<42; i++)
    {
        board[moves[i]-1][ctr[moves[i]-1]++] = 1+i%2;
        if(chk(1,moves[i]-1,ctr[moves[i]-1]-1))
        {
            cout << "RED " << i+1 << endl;
            return;
        }
        else if(chk(2,moves[i]-1,ctr[moves[i]-1]-1))
        {
            cout << "YELLOW " << i+1 << endl;
            return;
        }
    }
    cout << "DRAW" << endl;
}

int main()
{
    for(int i = 0; i<42; i++)   
        cin >> moves[i];
    solve();
}