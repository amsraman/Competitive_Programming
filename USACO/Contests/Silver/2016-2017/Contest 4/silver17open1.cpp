#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream infile("pairup.in");
    ofstream outfile("pairup.out");
    int n, c1 = 0, c2, ans = 0;
    infile >> n;
    pair<int,int> in[n];
    for(int i = 0; i<n; i++)
    {
        infile >> in[i].second >> in[i].first;
    }
    c2 = n-1;
    sort(in,in+n);
    while(c1!=c2)
    {
        ans = max(ans,in[c1].first+in[c2].first);
        int k = min(in[c1].second,in[c2].second);
        in[c1].second-=k;
        in[c2].second-=k;
        if(in[c1].second==0)
        {
            c1++;
        }
        if(in[c2].second==0)
        {
            c2--;
        }
    }
    outfile << max(ans,2*in[c1].second) << endl;
}
