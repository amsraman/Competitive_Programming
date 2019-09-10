/*
ID: adityasund1
TASK: bigbrn
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

int n, t, a, b, h[1000][1000], v[1000][1000], dp[2][1000], ans;
bool tr[1000][1000];

int main()
{
    ifstream infile("bigbrn.in");
    ofstream outfile("bigbrn.out");
    infile >> n >> t;
    for(int i = 0; i<t; i++)
    {
        infile >> a >> b;
        tr[a-1][b-1] = true;
    }
    for(int i = 0; i<n; i++)
    {
        dp[0][i] = int(!tr[0][i]);
        ans = max(ans,dp[0][i]);
        int r1 = -1, r2 = -1;
        for(int j = 0; j<n; j++)
        {
            if(tr[i][j])
            {
                r1 = j;
            }
            if(tr[j][i])
            {
                r2 = j;
            }
            h[i][j] = r1;
            v[j][i] = r2;
        }
    }
    for(int i = 1; i<n; i++)
    {
        dp[1][0] = int(!tr[i][0]);
        ans = max(ans,dp[1][0]);
        for(int j = 1; j<n; j++)
        {
            dp[1][j] = min(dp[0][j-1]+1,min(i-v[i][j],j-h[i][j]));
            ans = max(ans,dp[1][j]);
        }
        for(int j = 0; j<n; j++)
        {
            dp[0][j] = dp[1][j];
        }
    }
    outfile << ans << endl;
}
