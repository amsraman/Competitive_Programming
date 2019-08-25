#include <fstream>
#include <iostream>
#define MOD 1000000007

using namespace std;

int main()
{
    ifstream infile("spainting.in");
    ofstream outfile("spainting.out");
    long long n, m, k, ans = 1;
    infile >> n >> m >> k;
    long long dp[n+1], tot = 1;
    dp[0] = 1;
    for(int i = 1; i<k; i++)
    {
        dp[i] = (m*dp[i-1])%MOD;
        tot = (tot+dp[i])%MOD;
    }
    for(int i = k; i<=n; i++)
    {
        tot = (tot-dp[i-k])%MOD;
        dp[i] = ((m-1)*tot)%MOD;
        tot = (tot+dp[i])%MOD;
    }
    for(int i = 0; i<n; i++)
    {
        ans = (ans*m)%MOD;
    }
    ans = (ans-dp[n])%MOD;
    if(ans<0){ans+=MOD;}
    outfile << ans << endl;
}
