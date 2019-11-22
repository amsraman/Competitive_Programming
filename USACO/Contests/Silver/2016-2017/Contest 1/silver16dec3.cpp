#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> g[200];
bool v[200];

void dfs(int a, int &c)
{
    if(v[a])
    {
        return;
    }
    v[a] = true;
    c++;
    for(int i = 0; i<g[a].size(); i++)
    {
        dfs(g[a][i],c);
    }
}

int main()
{
    ifstream infile("moocast.in");
    ofstream outfile("moocast.out");
    int n;
    infile >> n;
    int in[n][3];
    for(int i = 0; i<n; i++)
    {
        infile >> in[i][0] >> in[i][1] >> in[i][2];
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if((in[j][0]-in[i][0])*(in[j][0]-in[i][0])+(in[j][1]-in[i][1])*(in[j][1]-in[i][1])<=in[i][2]*in[i][2])
            {
                g[i].push_back(j);
            }
        }
    }
    int z, ans = 0;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            v[j] = false;
        }
        z = 0;
        dfs(i,z);
        ans = max(ans,z);
    }
    outfile << ans;
}
