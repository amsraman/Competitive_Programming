#include <fstream>
#include <iostream>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;

int n, m, d[500][500][2], ans = INF;
bool ar[500][500], v[500][500][2];

int main()
{
    ifstream infile("gravity.in");
    ofstream outfile("gravity.out");
    char a;
    pair<int,int> init, fin;
    infile >> n >> m;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<m; j++)
        {
            infile >> a;
            if(a=='#')
            {
                ar[i][j] = false;
            }
            else
            {
                ar[i][j] = true;
            }
            if(a=='C')
            {
                init = {i,j};
            }
            if(a=='D')
            {
                fin = {i,j};
            }
            d[i][j][0] = d[i][j][1] = INF;
        }
    }
    priority_queue<pair<pair<int,int>,pair<int,int> > > q;
    q.push({{0,1},{init.first,init.second}});
    d[init.first][init.second][1] = 0;
    while(!q.empty())
    {
        int x = q.top().first.second, y = q.top().second.first, z = q.top().second.second;
        q.pop();
        if(!v[y][z][x])
        {
            v[y][z][x] = true;
            if((y+2*x>0)&&(y+2*x<=n)&&(!ar[y+2*x-1][z]))
            {
                if((!v[y][z][(x+1)%2])&&(d[y][z][x]+1<d[y][z][(x+1)%2]))
                {
                    d[y][z][(x+1)%2] = min(d[y][z][(x+1)%2],d[y][z][x]+1);
                    q.push({{-d[y][z][(x+1)%2],(x+1)%2},{y,z}});
                }
                if((z+1<m)&&(d[y][z][x]<d[y][z+1][x])&&(ar[y][z+1]))
                {
                    d[y][z+1][x] = d[y][z][x];
                    q.push({{-d[y][z+1][x],x},{y,z+1}});
                }
                if((z>0)&&(d[y][z][x]<d[y][z-1][x])&&(ar[y][z-1]))
                {
                    d[y][z-1][x] = d[y][z][x];
                    q.push({{-d[y][z-1][x],x},{y,z-1}});
                }
            }
            else if(((y+2*x>0)&&(y+2*x<=n))&&(d[y][z][x]<d[y+2*x-1][z][x]))
            {
                d[y+2*x-1][z][x] = d[y][z][x];
                q.push({{-d[y+2*x-1][z][x],x},{y+2*x-1,z}});
            }
        }
    }
    ans = min(ans,d[fin.first][fin.second][0]);
    ans = min(ans,d[fin.first][fin.second][1]);
    if(ans==INF)
    {
        outfile << -1 << endl;
    }
    else
    {
        outfile << ans << endl;
    }
}
