#include <fstream>
#include <iostream>

using namespace std;

int n, in[248], dp[248][248], ans;

int main()
{
    ifstream infile("248.in");
    ofstream outfile("248.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
    }
    for(int len = 1; len<=n; len++)
    {
        for(int i = 0; i<=n-len; i++)
        {
            int j = i+len-1;
            if(i==j)
            {
                dp[i][j] = in[i];
            }
            for(int k = i; k<j; k++)
            {
                if((dp[i][k]==dp[k+1][j])&&(dp[i][k]>0))
                {
                    dp[i][j] = max(dp[i][j],dp[i][k]+1);
                }
            }
            ans = max(ans,dp[i][j]);
        }
    }
    outfile << ans << endl;
}
