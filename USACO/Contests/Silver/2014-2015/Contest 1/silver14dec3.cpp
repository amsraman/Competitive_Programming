#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream infile("cowjog.in");
    ofstream outfile("cowjog.out");
    int n, t;
    infile >> n >> t;
    long long a, b, d[n], ans = 1;
    for(int i = 0; i<n; i++)
    {
        infile >> a >> b;
        d[i] = a+t*b;
    }
    for(int i = n-2; i>=0; i--)
    {
        if(d[i]>=d[i+1])
        {
            d[i] = d[i+1];
        }
        else
        {
            ans++;
        }
    }
    outfile << ans << endl;
}
