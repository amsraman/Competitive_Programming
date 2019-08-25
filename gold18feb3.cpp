#include <fstream>
#include <iostream>

using namespace std;

int n, in[100], dp[100][100][101];

int main()
{
    ifstream infile("taming.in");
    ofstream outfile("taming.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            for(int k = 0; k<=n; k++)
            {
                dp[i][j][k] = 1000;
            }
        }
    }
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
    }
    if(in[0]!=0)
    {
        dp[0][0][1] = 1;
    }
    else
    {
        dp[0][0][1] = 0;
    }
    for(int i = 1; i<n; i++)
    {
        for(int j = 0; j<=i; j++)
        {
            for(int k = 1; k<=i+1; k++)
            {
                if(j<i)
                {
                    dp[i][j][k] = dp[i-1][j][k];
                }
                else
                {
                    dp[i][j][k] = 1000;
                    for(int l = 0; l<j; l++)
                    {
                        dp[i][j][k] = min(dp[i][j][k],dp[i-1][l][k-1]);
                    }
                }
                if(in[i]!=i-j)
                {
                    dp[i][j][k]++;
                }
            }
        }
    }
    for(int i = 1; i<=n; i++)
    {
        int ans = 1000;
        for(int j = 0; j<n; j++)
        {
            ans = min(ans,dp[n-1][j][i]);
        }
        outfile << ans << endl;
    }
}
