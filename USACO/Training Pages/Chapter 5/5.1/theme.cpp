/*
ID: adityasund1
TASK: theme
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

int n, in[5000], dp[2][5000], ans;

int main()
{
    ifstream infile("theme.in");
    ofstream outfile("theme.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
        dp[0][i] = 1;
    }
    for(int i = 1; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            dp[1][j] = 1;
            if((in[j]-in[j-1])==(in[i]-in[i-1]))
            {
                dp[1][j] = min(dp[0][j-1]+1,j-i);
            }
            ans = max(ans,dp[1][j]);
        }
        for(int j = 0; j<n; j++)
        {
            dp[0][j] = dp[1][j];
            dp[1][j] = 0;
        }
    }
    if(ans<5)
    {
        outfile << 0 << endl;
    }
    else
    {
        outfile << ans << endl;
    }
}
