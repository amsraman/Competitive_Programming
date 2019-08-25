#include <fstream>
#include <iostream>
#include <vector>
#define INF 0x3f3f3f3f

using namespace std;

int n, k, ans = 0, edge[100000], d[100000][2];
vector<int> t[100000];
bool v[100000][2] = {false};

void dfs(int a)
{
    v[a][0] = true;
    if(edge[a]==1)
    {
        d[a][1] = 0;
        return;
    }
    d[a][1] = INF;
    for(int i = 0; i<t[a].size(); i++)
    {
        if(!v[t[a][i]][0])
        {
            d[t[a][i]][0] = d[a][0]+1;
            dfs(t[a][i]);
            d[a][1] = min(d[a][1],1+d[t[a][i]][1]);
        }
    }
}

void dfs2(int a)
{
    v[a][1] = true;
    if(d[a][0]>=d[a][1])
    {
        ans++;
        return;
    }
    else
    {
        for(int i = 0; i<t[a].size(); i++)
        {
            if(!v[t[a][i]][1])
            {
                dfs2(t[a][i]);
            }
        }
    }
}

int main()
{
    ifstream infile("atlarge.in");
    ofstream outfile("atlarge.out");
    int a, b;
    infile >> n >> k;
    for(int i = 0; i<n-1; i++)
    {
        infile >> a >> b;
        t[a-1].push_back(b-1);
        t[b-1].push_back(a-1);
        edge[a-1]++;
        edge[b-1]++;
    }
    d[k-1][0] = 0;
    dfs(k-1);
    dfs2(k-1);
    outfile << ans << endl;
}
