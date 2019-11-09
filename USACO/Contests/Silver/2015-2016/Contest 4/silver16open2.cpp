#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int n, k, ar[50000], lo[50000], pre[50000], ans;

int main()
{
    ifstream infile("diamond.in");
    ofstream outfile("diamond.out");
    infile >> n >> k;
    for(int i = 0; i<n; i++)
    {
        infile >> ar[i];
    }
    sort(ar,ar+n);
    int c1 = 0;
    for(int i = 0; i<n; i++)
    {
        while(ar[c1]<ar[i]-k)
        {
            c1++;
        }
        lo[i] = c1;
    }
    pre[0] = 1;
    for(int i = 1; i<n; i++)
    {
        pre[i] = max(pre[i-1],i-lo[i]+1);
    }
    for(int i = n-1; i>=0; i--)
    {
        if(lo[i]!=0)
        {
            ans = max(ans,i-lo[i]+1+pre[lo[i]-1]);
        }
    }
    outfile << ans << endl;
}
