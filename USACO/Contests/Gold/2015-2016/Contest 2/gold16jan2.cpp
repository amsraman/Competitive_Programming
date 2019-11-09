#include <fstream>
#include <iostream>
#define INF 0x3f3f3f3f

using namespace std;

int main()
{
    ifstream infile("radio.in");
    ofstream outfile("radio.out");
    int n, m;
    infile >> n >> m;
    int dp[n+1][m+1];
    string s1, s2;
    pair<int,int> f[n+1], b[m+1];
    infile >> f[0].first >> f[0].second >> b[0].first >> b[0].second;
    infile >> s1 >> s2;
    for(int i = 0; i<n; i++)
    {
        if(s1[i]=='N')
        {
            f[i+1] = {f[i].first,f[i].second+1};
        }
        if(s1[i]=='E')
        {
            f[i+1] = {f[i].first+1,f[i].second};
        }
        if(s1[i]=='S')
        {
            f[i+1] = {f[i].first,f[i].second-1};
        }
        if(s1[i]=='W')
        {
            f[i+1] = {f[i].first-1,f[i].second};
        }
    }
    for(int i = 0; i<m; i++)
    {
        if(s2[i]=='N')
        {
            b[i+1] = {b[i].first,b[i].second+1};
        }
        if(s2[i]=='E')
        {
            b[i+1] = {b[i].first+1,b[i].second};
        }
        if(s2[i]=='S')
        {
            b[i+1] = {b[i].first,b[i].second-1};
        }
        if(s2[i]=='W')
        {
            b[i+1] = {b[i].first-1,b[i].second};
        }
    }
    for(int i = 0; i<=n; i++)
    {
        for(int j = 0; j<=m; j++)
        {
            dp[i][j] = INF;
            if(i>0)
            {
                dp[i][j] = min(dp[i][j],dp[i-1][j]);
            }
            if(j>0)
            {
                dp[i][j] = min(dp[i][j],dp[i][j-1]);
            }
            if((i>0)&&(j>0))
            {
                dp[i][j] = min(dp[i][j],dp[i-1][j-1]);
            }
            dp[i][j]+=((b[j].first-f[i].first)*(b[j].first-f[i].first)+(b[j].second-f[i].second)*(b[j].second-f[i].second));
            if((i==0)&&(j==0))
            {
                dp[i][j] = 0;
            }
        }
    }
    outfile << dp[n][m] << endl;
}
