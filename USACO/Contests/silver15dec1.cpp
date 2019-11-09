#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector< pair<int,int> > in[100][100];
bool l[100][100];
bool v[100][100];

void dfs(int a, int b)
{
    if(v[a][b])
    {
        return;
    }
    v[a][b] = true;
    for(int i = 0; i<in[a][b].size(); i++)
    {
        int p1 = in[a][b][i].first, p2 = in[a][b][i].second;
        l[p1][p2] = true;
        if(((p1>0)&&(v[p1-1][p2]))||((p1<n-1)&&(v[p1+1][p2]))||((p2>0)&&(v[p1][p2-1]))||((p2<n-1)&&(v[p1][p2+1])))
        {
            dfs(p1,p2);
        }
    }
    if((a>0)&&(l[a-1][b]))
    {
        dfs(a-1,b);
    }
    if((a<n-1)&&(l[a+1][b]))
    {
        dfs(a+1,b);
    }
    if((b>0)&&(l[a][b-1]))
    {
        dfs(a,b-1);
    }
    if((b<n-1)&&(l[a][b+1]))
    {
        dfs(a,b+1);
    }
}

int main()
{
    l[0][0] = true;
    ifstream infile("lightson.in");
    ofstream outfile("lightson.out");
    int m;
    infile >> n >> m;
    int x, y, a, b;
    for(int i = 0; i<m; i++)
    {
        infile >> x >> y >> a >> b;
        in[x-1][y-1].push_back({a-1,b-1});
    }
    dfs(0,0);
    int ans = 0;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(l[i][j])
            {
                ans++;
            }
        }
    }
    outfile << ans << endl;
}
