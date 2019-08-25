#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int n, in[100000], par[100001], mx;
long long ans;
pair<int,int> s[100000];

int main()
{
    ifstream infile("sort.in");
    ofstream outfile("sort.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
        s[i] = make_pair(in[i],i);
    }
    sort(s,s+n);
    for(int i = 0; i<n; i++)
    {
        par[i] = max(mx-i+1,1);
        mx = max(mx,s[i].second);
    }
    par[n] = 1;
    for(int i = 0; i<n; i++)
    {
        ans+=max(par[i],par[i+1]);
    }
    outfile << ans << endl;
}
