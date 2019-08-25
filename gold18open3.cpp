#include <fstream>
#include <iostream>
#define INF 0xfffffffffffffff
typedef long long ll;

using namespace std;

int n, w;
ll wt[250], ta[250], dp[1001];

bool valid(ll a)
{
    for(int i = 1; i<=w; i++)
    {
        dp[i] = -INF;
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = w; j>=0; j--)
        {
            dp[min(w,int(j+wt[i]))] = max(dp[min(w,int(j+wt[i]))],dp[j]+1000*ta[i]-a*wt[i]);
        }
    }
    return (dp[w]>0);
}

int main()
{
    ifstream infile("talent.in");
    ofstream outfile("talent.out");
    infile >> n >> w;
    for(int i = 0; i<n; i++)
    {
        infile >> wt[i] >> ta[i];
    }
    ll l = 0, g = 250000000000;
    while(l<g)
    {
        ll mid = (l+g+1)/2;
        if(valid(mid))
        {
            l = mid;
        }
        else
        {
            g = mid-1;
        }
    }
    outfile << l << endl;
}
