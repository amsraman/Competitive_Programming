/*
ID: adityasund1
TASK: maze1
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

int main()
{
    ifstream infile("maze1.in");
    ofstream outfile("maze1.out");
    int w, h, c = 0, ans = 0;
    infile >> w >> h;
    int d[h][w][2];
    bool v[h][w][2];
    for(int i = 0; i<h; i++){for(int j = 0; j<w; j++){for(int k = 0; k<2; k++){v[i][j][k] = false;}}}
    string maze[2*h+1];
    pair<int,int> pos[2];
    infile.ignore();
    for(int i = 0; i<=2*h; i++)
    {
        getline(infile,maze[i]);
        for(int j = 0; j<maze[i].size(); j++)
        {
            if((i%2==1)&&(j==0)&&(maze[i][j]==' '))
            {
                pos[c] = {i/2,0};
                c++;
            }
            if((i%2==1)&&(j==maze[i].size()-1)&&(maze[i][j]==' '))
            {
                pos[c] = {i/2,w-1};
                c++;
            }
            if((i==0)&&(maze[i][j]==' '))
            {
                pos[c] = {0,j/2};
                c++;
            }
            if((i==2*h)&&(maze[i][j]==' '))
            {
                pos[c] = {h-1,j/2};
                c++;
            }
        }
    }
    for(int i = 0; i<2; i++)
    {
        queue<pair<int,int> > q;
        q.push({pos[i].first,pos[i].second});
        d[pos[i].first][pos[i].second][i] = 0;
        v[pos[i].first][pos[i].second][i] = true;
        while(!q.empty())
        {
            int a = q.front().first;
            int b = q.front().second;
            q.pop();
            if((a!=0)&&(maze[2*a][2*b+1]==' ')&&(!v[a-1][b][i]))
            {
                d[a-1][b][i] = d[a][b][i]+1;
                v[a-1][b][i] = true;
                q.push({a-1,b});
            }
            if((a!=h-1)&&(maze[2*a+2][2*b+1]==' ')&&(!v[a+1][b][i]))
            {
                d[a+1][b][i] = d[a][b][i]+1;
                v[a+1][b][i] = true;
                q.push({a+1,b});
            }
            if((b!=0)&&(maze[2*a+1][2*b]==' ')&&(!v[a][b-1][i]))
            {
                d[a][b-1][i] = d[a][b][i]+1;
                v[a][b-1][i] = true;
                q.push({a,b-1});
            }
            if((b!=w-1)&&(maze[2*a+1][2*b+2]==' ')&&(!v[a][b+1][i]))
            {
                d[a][b+1][i] = d[a][b][i]+1;
                v[a][b+1][i] = true;
                q.push({a,b+1});
            }
        }
    }
    for(int i = 0; i<h; i++)
    {
        for(int j = 0; j<w; j++)
        {
            ans = max(ans,min(d[i][j][0],d[i][j][1]));
        }
    }
    outfile << ans+1 << endl;
}
