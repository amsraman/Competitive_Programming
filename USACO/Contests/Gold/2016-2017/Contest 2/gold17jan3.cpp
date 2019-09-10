#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

int main()
{
    ifstream infile("cownav.in");
    ofstream outfile("cownav.out");
    int n;
    infile >> n;
    int d[n][n][n][n][4];
    bool v[20][20][20][20][4] = {false};
    char up[n][n], ri[n][n];
    pair<int,int> x, y, direc[4] = {{-1,0},{0,1},{1,0},{0,-1}};
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            infile >> up[i][j];
        }
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            ri[i][j] = up[j][n-1-i];
        }
    }
    queue<pair<pair<pair<int,int>,pair<int,int> >,int> > q;
    d[n-1][n-1][n-1][0][0] = 0;
    v[n-1][n-1][n-1][0][0] = true;
    q.push({{{n-1,n-1},{n-1,0}},0});
    while(!q.empty())
    {
        x.first = q.front().first.first.first;
        x.second = q.front().first.first.second;
        y.first = q.front().first.second.first;
        y.second = q.front().first.second.second;
        int dir = q.front().second, k = d[x.first][x.second][y.first][y.second][dir];
        q.pop();
        if(!v[x.first][x.second][y.first][y.second][(dir+1)%4])
        {
            v[x.first][x.second][y.first][y.second][(dir+1)%4] = true;
            d[x.first][x.second][y.first][y.second][(dir+1)%4] = d[x.first][x.second][y.first][y.second][dir]+1;
            q.push({{{x.first,x.second},{y.first,y.second}},(dir+1)%4});
        }
        if(!v[x.first][x.second][y.first][y.second][(dir+3)%4])
        {
            v[x.first][x.second][y.first][y.second][(dir+3)%4] = true;
            d[x.first][x.second][y.first][y.second][(dir+3)%4] = d[x.first][x.second][y.first][y.second][dir]+1;
            q.push({{{x.first,x.second},{y.first,y.second}},(dir+3)%4});
        }
        x.first+=direc[dir].first;
        y.first+=direc[dir].first;
        x.second+=direc[dir].second;
        y.second+=direc[dir].second;
        if((x.first==-1)||(x.first==n)||(x.second==-1)||(x.second==n)||((x.first-direc[dir].first==0)&&(x.second-direc[dir].second==0)))
        {
            x.first-=direc[dir].first;
            x.second-=direc[dir].second;
        }
        if((y.first==-1)||(y.first==n)||(y.second==-1)||(y.second==n)||((y.first-direc[dir].first==0)&&(y.second-direc[dir].second==n-1)))
        {
            y.first-=direc[dir].first;
            y.second-=direc[dir].second;
        }
        if(ri[x.first][x.second]=='H')
        {
            x.first-=direc[dir].first;
            x.second-=direc[dir].second;
        }
        if(up[y.first][y.second]=='H')
        {
            y.first-=direc[dir].first;
            y.second-=direc[dir].second;
        }
        if(!v[x.first][x.second][y.first][y.second][dir])
        {
            v[x.first][x.second][y.first][y.second][dir] = true;
            d[x.first][x.second][y.first][y.second][dir] = k+1;
            q.push({{{x.first,x.second},{y.first,y.second}},dir});
        }
    }
    outfile << min(min(d[0][0][0][n-1][0],d[0][0][0][n-1][1]),min(d[0][0][0][n-1][2],d[0][0][0][n-1][3])) << endl;
}
