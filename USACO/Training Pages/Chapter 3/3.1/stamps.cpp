/*
ID: adityasund1
TASK: stamps
LANG: C++
*/
#include <fstream>
#include <iostream>
#define INF 0x3f3f3f3f

using namespace std;

int main()
{
    ifstream infile("stamps.in");
    ofstream outfile("stamps.out");
    int k, n, ans, maxs = 0;
    infile >> k >> n;
    int s[n], dp[2000001];
    for(int i = 0; i<2000001; i++){dp[i] = INF;}
    dp[0] = 0;
    for(int i = 0; i<n; i++)
    {
        infile >> s[i];
        maxs = max(maxs,s[i]);
    }
    for(int i = 0; i<=k*maxs; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(s[j]<=i)
            {
                dp[i] = min(dp[i],dp[i-s[j]]+1);
            }
        }
        if(dp[i]>k)
        {
            ans = i;
            break;
        }
    }
    outfile << ans-1 << endl;
}
