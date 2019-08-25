#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int mod = 1000000007, n, k, dp[100000][3], c[100000], d[100000];
bool v[100000][2] = {false};
vector<int> g[100000];

int solve(int a, int b)
{
    long long ret = 1;
    if((v[a][1])&&(c[a]!=b))
    {
        return 0;
    }
    for(int i = 0; i<g[a].size(); i++)
    {
        if(d[g[a][i]]>d[a])
        {
            int r1 = 0;
            for(int j = 0; j<3; j++)
            {
                if(b!=j)
                {
                    r1+=dp[g[a][i]][j];
                }
            }
            ret*=r1;
            ret%=mod;
        }
    }
    return ret;
}

int main()
{
    ifstream infile("barnpainting.in");
    ofstream outfile("barnpainting.out");
    vector<int> qu;
    infile >> n >> k;
    int a, b;
    for(int i = 0; i<n-1; i++)
    {
        infile >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    for(int i = 0; i<k; i++)
    {
        infile >> a >> b;
        v[a-1][1] = true;
        c[a-1] = b-1;
    }
    queue<int> q;
    d[0] = 0;
    v[0][0] = true;
    q.push(0);
    while(!q.empty())
    {
        int a = q.front();
        qu.push_back(a);
        q.pop();
        for(int i = 0; i<g[a].size(); i++)
        {
            if(!v[g[a][i]][0])
            {
                q.push(g[a][i]);
                d[g[a][i]] = d[a]+1;
                v[g[a][i]][0] = true;
            }
        }
    }
    for(int i = n-1; i>=0; i--)
    {
        dp[qu[i]][0] = solve(qu[i],0);
        dp[qu[i]][1] = solve(qu[i],1);
        dp[qu[i]][2] = solve(qu[i],2);
    }
    outfile << (dp[0][0]+dp[0][1]+dp[0][2])%mod << endl;
}
