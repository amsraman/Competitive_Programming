#include <fstream>
#include <iostream>
#include <stdlib.h>
#define INF 0x3f3f3f3f

using namespace std;

int n, k;

int main()
{
    ifstream infile("marathon.in");
    ofstream outfile("marathon.out");
    infile >> n >> k;
    pair<int,int> p[n];
    for(int i = 0; i<n; i++)
    {
        infile >> p[i].first >> p[i].second;
    }
    int dp[n][k+1];
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<=k; j++)
        {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    for(int i = 1; i<n; i++)
    {
        for(int j = 0; j<=k; j++)
        {
            if(j<i)
            {
                for(int l = 0; l<=j; l++)
                {
                    dp[i][j] = min(dp[i][j],dp[i-l-1][j-l]+abs(p[i].first-p[i-l-1].first)+abs(p[i].second-p[i-l-1].second));
                }
            }
        }
    }
    int ans = INF;
    for(int i = 0; i<=k; i++)
    {
        ans = min(ans,dp[n-1][i]);
    }
    outfile << ans << endl;
}
