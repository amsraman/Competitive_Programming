#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#define INF 0x3f3f3f3f

using namespace std;

int n, m, ar[1000][1000], di[1000][1000][4][2], a, b, c, d, ans = INF;
pair<int,int> dir[4] = {{0,1},{1,0},{0,-1},{-1,0}};
bool v[1000][1000][4][2];

int main()
{
    ifstream infile("dream.in");
    ofstream outfile("dream.out");
    infile >> n >> m;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<m; j++)
        {
            infile >> ar[i][j];
        }
    }
    queue<pair<pair<int,int>,pair<int,int> > > q;
    q.push({{0,0},{0,0}});
    q.push({{0,0},{1,0}});
    di[0][0][0][0] = di[0][0][1][0] = 0;
    v[0][0][0][0] = v[0][0][1][0] = true;
    while(!q.empty())
    {
        a = q.front().first.first;
        b = q.front().first.second;
        c = q.front().second.first;
        d = q.front().second.second;
        q.pop();
        if((a==n-1)&&(b==m-1)){ans = min(ans,di[a][b][c][d]);}
        if((ar[a][b]==4)&&(a+dir[c].first>=0)&&(a+dir[c].first<n)&&(b+dir[c].second>=0)&&(b+dir[c].second<m)&&(ar[a+dir[c].first][b+dir[c].second]!=0)&&(ar[a+dir[c].first][b+dir[c].second]!=3)&&(!v[a+dir[c].first][b+dir[c].second][c][d]))
        {
            di[a+dir[c].first][b+dir[c].second][c][d] = di[a][b][c][d]+1;
            v[a+dir[c].first][b+dir[c].second][c][d] = true;
            q.push({{a+dir[c].first,b+dir[c].second},{c,d}});
        }
        else
        {
            if((b<m-1)&&(ar[a][b+1]!=0)&&(((ar[a][b+1]==3)&&(d==1))||(ar[a][b+1]!=3)))//right
            {
                int k = d;
                if(ar[a][b+1]==2){k = 1;}
                if(ar[a][b+1]==4){k = 0;}
                if(!v[a][b+1][0][k])
                {
                    di[a][b+1][0][k] = di[a][b][c][d]+1;
                    v[a][b+1][0][k] = true;
                    q.push({{a,b+1},{0,k}});
                }
            }
            if((a<n-1)&&(ar[a+1][b]!=0)&&(((ar[a+1][b]==3)&&(d==1))||(ar[a+1][b]!=3)))//down
            {
                int k = d;
                if(ar[a+1][b]==2){k = 1;}
                if(ar[a+1][b]==4){k = 0;}
                if(!v[a+1][b][1][k])
                {
                    di[a+1][b][1][k] = di[a][b][c][d]+1;
                    v[a+1][b][1][k] = true;
                    q.push({{a+1,b},{1,k}});
                }
            }
            if((b>0)&&(ar[a][b-1]!=0)&&(((ar[a][b-1]==3)&&(d==1))||(ar[a][b-1]!=3)))//left
            {
                int k = d;
                if(ar[a][b-1]==2){k = 1;}
                if(ar[a][b-1]==4){k = 0;}
                if(!v[a][b-1][2][k])
                {
                    di[a][b-1][2][k] = di[a][b][c][d]+1;
                    v[a][b-1][2][k] = true;
                    q.push({{a,b-1},{2,k}});
                }
            }
            if((a>0)&&(ar[a-1][b]!=0)&&(((ar[a-1][b]==3)&&(d==1))||(ar[a-1][b]!=3)))//up
            {
                int k = d;
                if(ar[a-1][b]==2){k = 1;}
                if(ar[a-1][b]==4){k = 0;}
                if(!v[a-1][b][3][k])
                {
                    di[a-1][b][3][k] = di[a][b][c][d]+1;
                    v[a-1][b][3][k] = true;
                    q.push({{a-1,b},{3,k}});
                }
            }
        }
    }
    if(ans==INF){outfile << -1 << endl;}
    else{outfile << ans << endl;}
}
