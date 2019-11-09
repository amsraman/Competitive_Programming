#include <fstream>
#include <iostream>
#define INF 0xfffffffffffffff

using namespace std;

int n, k;
long long in[100], dp[8][101], ans = INF;

int main()
{
    ifstream infile("cbarn2.in");
    ofstream outfile("cbarn2.out");
    infile >> n >> k;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<=k; j++)
        {
            for(int l = 0; l<=n; l++)
            {
                dp[j][l] = INF;
            }
        }
        dp[0][0] = 0;
        for(int j = 0; j<k; j++)
        {
            for(int l = 0; l<n; l++)
            {
                long long val = 0;
                for(int m = l+1; m<=n; m++)
                {
                    val+=((m-l-1)*in[(i+m-1)%n]);
                    dp[j+1][m] = min(dp[j+1][m],dp[j][l]+val);
                }
            }
        }
        ans = min(ans,dp[k][n]);
    }
    outfile << ans << endl;
}
