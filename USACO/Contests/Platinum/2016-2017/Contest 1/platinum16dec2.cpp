#include <fstream>
#include <iostream>
#define MOD 1000000009

using namespace std;

int n, m, k, fj[1000], fp[1000];
long long dp[10][1000][1000], pre[10][1000][1000];

int main()
{
    ifstream infile("team.in");
    ofstream outfile("team.out");
    infile >> n >> m >> k;
    for(int i = 0; i<n; i++)
    {
        infile >> fj[i];
    }
    for(int i = 0; i<m; i++)
    {
        infile >> fp[i];
    }
    for(int i = 0; i<k; i++)
    {
        for(int j = 0; j<m; j++)
        {
            for(int l = 0; l<n; l++)
            {
                if(i==0)
                {
                    dp[i][j][l] = (long long)(fj[l]>fp[j]);
                }
                else if(fj[l]>fp[j])
                {
                    if((j>=i)&&(l>=i))
                    {
                        dp[i][j][l] = pre[i-1][j-1][l-1];
                    }
                }
                pre[i][j][l] = dp[i][j][l];
                if(j>0)
                {
                    pre[i][j][l]+=pre[i][j-1][l];
                }
                if(l>0)
                {
                    pre[i][j][l]+=pre[i][j][l-1];
                }
                if((j>0)&&(l>0))
                {
                    pre[i][j][l]-=pre[i][j-1][l-1];
                }
                pre[i][j][l] = (pre[i][j][l]%MOD+MOD)%MOD;
            }
        }
    }
    outfile << pre[k-1][m-1][n-1] << endl;
}
