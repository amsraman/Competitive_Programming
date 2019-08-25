#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

int n;
long long k, in[100000];
long double ans;

int main()
{
    ifstream infile("tallbarn.in");
    ofstream outfile("tallbarn.out");
    infile >> n >> k;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
    }
    long double l = 0, g = 1000000000000;
    while(g-l>0.00000000000001)
    {
        long double mid = (l+g)/2;
        long long tot = 0;
        for(int i = 0; i<n; i++)
        {
            tot+=max((long long)(1),(long long)((1+sqrt(1+4*in[i]/mid))/2));
        }
        if(tot<=k)
        {
            g = mid;
        }
        else
        {
            l = mid;
        }
    }
    for(int i = 0; i<n; i++)
    {
        long long a = max((long long)(1),(long long)((1+sqrt(1+4*in[i]/g))/2));
        ans+=(((long double)(in[i]))/((long double)(a)));
    }
    outfile << (long long)(ans+0.5) << endl;
}
