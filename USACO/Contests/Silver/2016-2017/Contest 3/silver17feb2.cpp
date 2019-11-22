#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream infile("maxcross.in");
    ofstream outfile("maxcross.out");
    int n, k, b;
    infile >> n >> k >> b;
    int pre[n+1], in[b];
    for(int i = 0; i<b; i++)
    {
        infile >> in[i];
    }
    sort(in,in+b);
    pre[0] = 0;
    int c = 0;
    for(int i = 1; i<=n; i++)
    {
        pre[i] = pre[i-1];
        if(i==in[c])
        {
            pre[i]++;
            c++;
        }
    }
    int ans = n+2;
    for(int i = 0; i<n+1-k; i++)
    {
        ans=min(ans,pre[i+k]-pre[i]);
    }
    outfile << ans << endl;
}
