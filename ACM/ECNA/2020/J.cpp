#include <bits/stdc++.h>

using namespace std;

int num_empty;
char grid[9][9];
bool keep_going = true, row[9][9], col[9][9], block[9][9];

void place(int x, int y, int num)
{
    grid[x][y] = char('0'+num+1), --num_empty;
    row[x][num] = col[y][num] = block[3*(x/3)+(y/3)][num] = true;
}

bool check()
{
    for(int i = 0; i<9; i++)
        for(int j = 0; j<9; j++)
            if(grid[i][j]=='.')
            {
                 int tot = 0, rec;
                 for(int num = 0; num<9; num++)
                    if(!row[i][num]&&!col[j][num]&&!block[3*(i/3)+(j/3)][num])
                        ++tot, rec = num;
                if(tot==1)
                {
                    place(i,j,rec);
                    return true;
                }
            }
    for(int i = 0; i<9; i++)
        for(int num = 0; num<9; num++)
        {
            int tot = 0, pos;
            for(int j = 0; j<9; j++)
                if(grid[i][j]=='.'&&!row[i][num]&&!col[j][num]&&!block[3*(i/3)+(j/3)][num])
                    ++tot, pos = j;
            if(tot==1)
            {
                place(i,pos,num);
                return true;
            }
        }
    for(int i = 0; i<9; i++)
        for(int num = 0; num<9; num++)
        {
            int tot = 0, pos;
            for(int j = 0; j<9; j++)
                if(grid[j][i]=='.'&&!row[j][num]&&!col[i][num]&&!block[3*(j/3)+(i/3)][num])
                    ++tot, pos = j;
            if(tot==1)
            {
                place(pos,i,num);
                return true;
            }
        }
    for(int i = 0; i<9; i+=3)
        for(int j = 0; j<9; j+=3)
            for(int num = 0; num<9; num++)
            {
                int tot = 0, pos1, pos2;
                for(int k = 0; k<3; k++)
                    for(int l = 0; l<3; l++)
                        if(grid[i+k][j+l]=='.'&&!row[i+k][num]&&!col[j+l][num]&&!block[i+(j/3)][num])
                            ++tot, pos1 = i+k, pos2 = j+l;
                if(tot==1)
                {
                    place(pos1,pos2,num);
                    return true;
                }
            }
    return false;
}

int main()
{
    for(int i = 0; i<9; i++)
        for(int j = 0; j<9; j++)
            cin >> grid[i][j];
    for(int i = 0; i<9; i++)
        for(int j = 0; j<9; j++)
        {
            if(grid[i][j]=='0')
                grid[i][j] = '.';
            else
                row[i][(grid[i][j]-'0')-1] = col[j][(grid[i][j]-'0')-1] = block[3*(i/3)+(j/3)][(grid[i][j]-'0')-1] = true;
            num_empty+=(grid[i][j]=='.');
        }
    while(keep_going)
        keep_going = (check());
    cout << (num_empty==0?"Easy":"Not easy") << endl;
    for(int i = 0; i<9; i++)
    {
        for(int j = 0; j<9; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}