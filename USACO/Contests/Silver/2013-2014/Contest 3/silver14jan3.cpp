#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int n, dp[152][152] = {-1};
pair<int,int> pr[151];

int solve(int a, int b)
{
    int k = max(a,b);
    for(int i = k+1; i<=n; i++)
    {
        if(pr[i].first>=pr[a].second)
        {
            dp[i][b] = max(dp[i][b],dp[a][b]+1);
        }
        if(pr[i].first>=pr[b].second)
        {
            dp[a][i] = max(dp[a][i],dp[a][b]+1);
        }
    }
}

int main()
{
    ifstream infile("recording.in");
    ofstream outfile("recording.out");
    int ans = 0;
    infile >> n;
    pr[0] = {0,0};
    for(int i = 1; i<=n; i++)
    {
        infile >> pr[i].first >> pr[i].second;
    }
    n++;
    sort(pr,pr+n);
    dp[0][0] = 0;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(dp[i][j]!=-1)
            {
                solve(i,j);
                ans = max(ans,dp[i][j]);
            }
        }
    }
    outfile << ans << endl;
}
