#include <fstream>
#include <iostream>

using namespace std;

int n, a, dp[262144][61], ans;

int main()
{
    ifstream infile("262144.in");
    ofstream outfile("262144.out");
    for(int i = 0; i<262144; i++)
    {
        for(int j = 0; j<61; j++)
        {
            dp[i][j] = -1;
        }
    }
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> a;
        dp[i][a-1] = i;
    }
    for(int i = 0; i<60; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if((dp[j][i]!=-1)&&(dp[j][i]<n-1))
            {
                dp[j][i+1] = dp[dp[j][i]+1][i];
            }
            if(dp[j][i]!=-1)
            {
                ans = max(ans,i+1);
            }
        }
    }
    outfile << ans << endl;
}
