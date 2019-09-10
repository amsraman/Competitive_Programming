#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream infile("hps.in");
    ofstream outfile("hps.out");
    int n, k;
    char a;
    infile >> n >> k;
    int pre[n+1][3], dp[n+1][k+1][3];
    pre[0][0] = pre[0][1] = pre[0][2] = 0;
    for(int i = 0; i<n; i++)
    {
        infile >> a;
        pre[i+1][0] = pre[i][0];
        pre[i+1][1] = pre[i][1];
        pre[i+1][2] = pre[i][2];
        if(a=='H')
        {
            pre[i+1][0]++;
        }
        else if(a=='P')
        {
            pre[i+1][1]++;
        }
        else
        {
            pre[i+1][2]++;
        }
    }
    for(int i = 0; i<=n; i++)
    {
        for(int j = 0; j<=k; j++)
        {
            for(int k = 0; k<3; k++)
            {
                if(i==0)
                {
                    dp[i][j][k] = 0;
                }
                else
                {
                    if(j==0)
                    {
                        dp[i][j][k] = pre[i][k];
                    }
                    else
                    {
                        dp[i][j][k] = max(dp[i-1][j][k]+pre[i][k]-pre[i-1][k],max(max(dp[i-1][j-1][0],dp[i-1][j-1][1]),dp[i-1][j-1][2])+pre[i][k]-pre[i-1][k]);
                    }
                }
            }
        }
    }
    outfile << max(max(dp[n][k][0],dp[n][k][1]),dp[n][k][2]);
}
