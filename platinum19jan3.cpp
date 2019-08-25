#include <fstream>
#include <iostream>
#include <deque>
#define MOD 1000000007

using namespace std;

int n, k, c, in[100000];
long long ans = 1;
bool pos[100000];
deque<int> dq;

long long modx(long long a){return ((a%MOD+MOD)%MOD);}

long long f(long long x, int r)
{
    long long dp[r+1], pow[min(k,r)], ret = 0;
    if(r<k)//None actually have to hit the specified minimum
    {
        ret = 1;
        for(int i = 0; i<r; i++)
        {
            ret = modx(ret*x);
        }
    }
    else
    {
        pow[0] = dp[0] = dp[1] = 1;
        for(int i = 1; i<k; i++)
        {
            pow[i] = modx(pow[i-1]*(x-1));
        }
        for(int i = 2; i<=r; i++)
        {
            dp[i] = dp[i-1];
            if(i>k)
            {
                dp[i] = modx(dp[i]-modx(dp[i-k-1]*pow[k-1]));
            }
            dp[i] = modx(dp[i]*(x-1)+dp[i-1]);
        }
        for(int i = 0; i<k; i++)
        {
            ret = modx(ret+modx(dp[r-i]*pow[i]));
        }
    }
    return ret;
}

int main()
{
    ifstream infile("tracking2.in");
    ofstream outfile("tracking2.out");
    infile >> n >> k;
    for(int i = 0; i<n-k+1; i++)
    {
        infile >> in[i];
    }
    for(int i = 0; i<n-k+1; i++)
    {
        if((in[i]<in[i+1])&&(i<n-k))
        {
            pos[i] = true;
        }
        else if((in[i]>in[i+1])&&(i<n-k))
        {
            pos[i+k] = true;
        }
    }
    for(int i = 0; i<n; i++)
    {
        while((dq.size()!=0)&&(dq[dq.size()-1]<in[i])&&(i<n-k+1)) dq.pop_back();
        if(i<n-k+1) dq.push_back(in[i]);
        if(!pos[i])
        {
            c++;
            if((pos[i+1])||(i==n-1)) ans = modx(ans*f((long long)(1000000001-dq[0]),c));
        }
        if(pos[i]) c = 0;
        if((i>k-2)&&(dq[0]==in[i-k+1])) dq.pop_front();
    }
    outfile << ans << endl;
}
