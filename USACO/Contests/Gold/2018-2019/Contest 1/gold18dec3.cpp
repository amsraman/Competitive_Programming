#include <fstream>
#include <iostream>

using namespace std;

int n, k, in[10000], dp[10000][1000], val[10000][1000], maxdp[10000], ans;

int main()
{
    ifstream infile("teamwork.in");
    ofstream outfile("teamwork.out");
    infile >> n >> k;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<k; j++)
        {
            if(j==0)
            {
                val[i][j] = in[i];
                if(i!=0)
                {
                    for(int k = 0; k<i; k++)
                    {
                        dp[i][j] = max(dp[i][j],maxdp[k]);
                    }
                }
                dp[i][j]+=val[i][j];
            }
            else if(j<=i)
            {
                val[i][j] = max(val[i-1][j-1],in[i]);
                dp[i][j] = dp[i-1][j-1]-j*val[i-1][j-1]+(j+1)*val[i][j];
            }
            maxdp[i] = max(maxdp[i],dp[i][j]);
        }
    }
    outfile << maxdp[n-1] << endl;
}
