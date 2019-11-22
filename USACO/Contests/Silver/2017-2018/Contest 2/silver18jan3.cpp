#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n, k, ans;
vector< pair<int,int> > g[5000];
bool v[5000];

void dfs(int a)
{
    if(v[a])
    {
        return;
    }
    v[a] = true;
    ans++;
    for(int i = 0; i<g[a].size(); i++)
    {
        if(g[a][i].second>=k)
        {
            dfs(g[a][i].first);
        }
    }
}

int main()
{
    int q;
    int t1, t2, t3;
    ifstream infile("mootube.in");
    ofstream outfile("mootube.out");
    infile >> n >> q;
    for(int i = 0; i<n-1; i++)
    {
        infile >> t1 >> t2 >> t3;
        g[t1-1].push_back({t2-1,t3});
        g[t2-1].push_back({t1-1,t3});
    }
    int b;
    for(int i = 0; i<q; i++)
    {
        for(int j = 0; j<n; j++)
        {
            v[j] = false;
        }
        ans = 0;
        infile >> k >> b;
        dfs(b-1);
        outfile << ans-1 << endl;
    }
}
