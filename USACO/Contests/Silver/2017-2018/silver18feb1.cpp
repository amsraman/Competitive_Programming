#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream infile("reststops.in");
    ofstream outfile("reststops.out");
    int l, n, rf, rb;
    infile >> l >> n >> rf >> rb;
    pair<int,int> in[n];
    int maxi = 0;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i].second >> in[i].first;
        maxi = max(maxi,in[i].second);
    }
    sort(in,in+n);
    for(int i = 0; i<n; i++)
    {
        cout << in[i].first << " " << in[i].second << endl;
    }
    int c = 0;
    long long ans = 0;
    for(int i = n-1; i>=0; i--)
    {
        if(in[i].second>c)
        {
            ans+=long(in[i].second-c)*long(in[i].first);
            c = in[i].second;
        }
        if(in[i].second==maxi)
        {
            break;
        }
    }
    outfile << ans*(rf-rb) << endl;
}
