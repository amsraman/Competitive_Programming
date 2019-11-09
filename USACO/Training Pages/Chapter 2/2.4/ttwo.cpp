/*
ID: adityasund1
TASK: ttwo
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

bool v[10][10][10][10][4][4] = {false};
pair<int,int> dir[4] = {{-1,0},{0,1},{1,0},{0,-1}};
string g[10];

int mov(int a1, int b1, int a2, int b2, int c, int d1, int d2)
{
    if(v[a1][b1][a2][b2][d1][d2])
    {
        return 0;
    }
    v[a1][b1][a2][b2][d1][d2] = true;
    if((a1+dir[d1].first==10)||(a1+dir[d1].first==-1)||(b1+dir[d1].second==10)||(b1+dir[d1].second==-1)||(g[a1+dir[d1].first][b1+dir[d1].second]=='*'))
    {
        d1 = (d1+1)%4;
    }
    else
    {
        a1+=dir[d1].first;
        b1+=dir[d1].second;
    }
    if((a2+dir[d2].first==10)||(a2+dir[d2].first==-1)||(b2+dir[d2].second==10)||(b2+dir[d2].second==-1)||(g[a2+dir[d2].first][b2+dir[d2].second]=='*'))
    {
        d2 = (d2+1)%4;
    }
    else
    {
        a2+=dir[d2].first;
        b2+=dir[d2].second;
    }
    if((a1==a2)&&(b1==b2))
    {
        return c+1;
    }
    return mov(a1,b1,a2,b2,c+1,d1,d2);
}

int main()
{
    ifstream infile("ttwo.in");
    ofstream outfile("ttwo.out");
    int x1, x2, y1, y2;
    for(int i = 0; i<10; i++)
    {
        infile >> g[i];
        for(int j = 0; j<10; j++)
        {
            if(g[i][j]=='C')
            {
                x1 = i;
                y1 = j;
            }
            if(g[i][j]=='F')
            {
                x2 = i;
                y2 = j;
            }
        }
    }
    outfile << mov(x1,y1,x2,y2,0,0,0) << endl;
}
