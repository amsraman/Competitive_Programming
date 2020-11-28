#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#define INF 0xfffffffffffffff

using namespace std;

int n;
long long a, b, in[5000], dp[5000];

int main()
{
    ifstream infile("wifi.in");
    ofstream outfile("wifi.out");
    infile >> n >> a >> b;
    a*=2;
    b*=2;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
    }
    sort(in,in+n);
    dp[n-1] = a;
    for(int i = n-2; i>=0; i--)
    {
        dp[i] = INF;
        for(int j = n-2; j>=i; j--)
        {
            dp[i] = min(dp[i],min(dp[j+1]+a+b*(in[j]-in[i])/2,dp[j+1]+b*(in[j+1]-in[i])/2));
        }
    }
    if(dp[0]%2==0)
    {
        outfile << dp[0]/2 << endl;
    }
    else
    {
        outfile << dp[0]/2 << ".5" << endl;
    }
}
