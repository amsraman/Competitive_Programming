#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

int n, in;
long long ans;
vector<int> a, b;

int main()
{
    ifstream infile("cbarn.in");
    ofstream outfile("cbarn.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        a.push_back(i);
        infile >> in;
        for(int j = 0; j<in; j++)
        {
            b.push_back(i);
        }
    }
    in = 0;
    for(int i = 0; i<n; i++)
    {
        in = max(in,b[i]-a[i]);
    }
    for(int i = 0; i<n; i++)
    {
        a[i]+=in;
        ans+=(b[i]-a[i])*(b[i]-a[i]);
    }
    outfile << ans << endl;
}
