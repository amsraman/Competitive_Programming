#include <fstream>
#include <iostream>

using namespace std;

int n, h, he[20], w[20], s[20], totw[(1<<20)], toth[(1<<20)], dp[(1<<20)], ans;
bool v;

int main()
{
    ifstream infile("guard.in");
    ofstream outfile("guard.out");
    infile >> n >> h;
    for(int i = 0; i<n; i++)
    {
        infile >> he[i] >> w[i] >> s[i];
    }
    dp[0] = 0x3f3f3f3f;
    for(int i = 1; i<(1<<n); i++)
    {
        dp[i] = -1;
        for(int j = 0; j<n; j++)
        {
            if(i&(1<<j))
            {
                totw[i]+=w[j];
                toth[i]+=he[j];
                dp[i] = max(dp[i],min(s[j]-totw[i-(1<<j)],dp[i-(1<<j)]));
            }
        }
        if((toth[i]>=h)&&(dp[i]>=0))
        {
            v = true;
            ans = max(ans,dp[i]);
        }
    }
    if(v) outfile << ans << endl;
    else outfile << "Mark is too tall" << endl;
}
