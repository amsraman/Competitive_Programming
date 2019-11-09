/*
ID: adityasund1
TASK: inflate
LANG: C++
*/
#include <fstream>
#include <iostream>
#define INF 0x3f3f3f3f

using namespace std;

int main()
{
    ifstream infile("inflate.in");
    ofstream outfile("inflate.out");
    int m, n, p, t;
    infile >> m >> n;
    int dp[10001] = {0};
    for(int i = 0; i<n; i++)
    {
        infile >> p >> t;
        for(int j = 0; j<=m-t; j++)
        {
            dp[j+t] = max(dp[j+t],dp[j]+p);
        }
    }
    outfile << dp[m] << endl;
}
