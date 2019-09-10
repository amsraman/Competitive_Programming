#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#define INF 0x3f3f3f3f

using namespace std;

int main()
{
    ifstream infile("visitfj.in");
    ofstream outfile("visitfj.out");
    int n, t;
    infile >> n >> t;
    int ti[n][n], d[n][n];
    bool v[n][n];
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            infile >> ti[i][j];
            ti[i][j]+=3*t;
            d[i][j] = INF;
            v[i][j] = false;
        }
    }
    vector<pair<int,int> > g[n][n];
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(i>0){g[i][j].push_back({i-1,j});}
            if(i<n-1){g[i][j].push_back({i+1,j});}
            if(j>0){g[i][j].push_back({i,j-1});}
            if(j<n-1){g[i][j].push_back({i,j+1});}
            if(i>2){g[i][j].push_back({i-3,j});}
            if(i<n-3){g[i][j].push_back({i+3,j});}
            if(j>2){g[i][j].push_back({i,j-3});}
            if(j<n-3){g[i][j].push_back({i,j+3});}
            if((i>0)&&(j>1)){g[i][j].push_back({i-1,j-2});}
            if((i>1)&&(j>0)){g[i][j].push_back({i-2,j-1});}
            if((i>0)&&(j<n-2)){g[i][j].push_back({i-1,j+2});}
            if((i>1)&&(j<n-1)){g[i][j].push_back({i-2,j+1});}
            if((i<n-1)&&(j>1)){g[i][j].push_back({i+1,j-2});}
            if((i<n-2)&&(j>0)){g[i][j].push_back({i+2,j-1});}
            if((i<n-1)&&(j<n-2)){g[i][j].push_back({i+1,j+2});}
            if((i<n-2)&&(j<n-1)){g[i][j].push_back({i+2,j+1});}
        }
    }
    d[0][0] = 0;
    priority_queue<pair<int,pair<int,int> > > q;
    q.push({0,{0,0}});
    while(!q.empty())
    {
        pair<int,int> a;
        a = {q.top().second.first,q.top().second.second};
        q.pop();
        if(!v[a.first][a.second])
        {
            v[a.first][a.second] = true;
            for(int i = 0; i<g[a.first][a.second].size(); i++)
            {
                if(d[a.first][a.second]+ti[g[a.first][a.second][i].first][g[a.first][a.second][i].second]<d[g[a.first][a.second][i].first][g[a.first][a.second][i].second])
                {
                    d[g[a.first][a.second][i].first][g[a.first][a.second][i].second] = d[a.first][a.second]+ti[g[a.first][a.second][i].first][g[a.first][a.second][i].second];
                    q.push({-d[g[a.first][a.second][i].first][g[a.first][a.second][i].second],{g[a.first][a.second][i].first,g[a.first][a.second][i].second}});
                }
            }
        }
    }
    int ans = min(min(min(min(d[n-3][n-1],d[n-1][n-3]),d[n-2][n-2])+2*t,min(d[n-2][n-1],d[n-1][n-2])+t),d[n-1][n-1]);
    outfile << ans << endl;
}
