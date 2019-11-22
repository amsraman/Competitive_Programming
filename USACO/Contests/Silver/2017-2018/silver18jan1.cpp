#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream infile("lifeguards.in");
    ofstream outfile("lifeguards.out");
    int n;
    infile >> n;
    pair<int,int> in[n];
    for(int i = 0; i<n; i++)
    {
        infile >> in[i].first >> in[i].second;
    }
    sort(in,in+n);
    int mi = 0, ma = 0, tot = 0;
    int ov[n];
    for(int i = 0; i<n; i++)
    {
        if(in[i].first>ma)
        {
            tot+=(ma-mi);
            mi = in[i].first;
            ma = in[i].second;
            ov[i] = in[i].first;
        }
        else
        {
            ov[i] = min(ma,in[i].second);
            ma = max(ma,in[i].second);
        }
        if(i==n-1)
        {
            tot+=(ma-mi);
        }
    }
    ma++;
    mi = ma;
    int d[n], ans = 1000000001;
    for(int i = n-1; i>=0; i--)
    {
        if(in[i].second<mi)
        {
            d[i] = in[i].second-ov[i];
            ma = in[i].second;
            mi = in[i].first;
        }
        else if(in[i].second<ma)
        {
            d[i] = max(0,mi-ov[i]);
            mi = in[i].first;
        }
        else
        {
            if(ma<ov[i]){d[i]=in[i].second-ov[i];}
            else if(mi<ov[i]){d[i]=in[i].second-ma;}
            else{d[i]=in[i].second-ov[i]+mi-ma;}
            mi = in[i].first;
            ma = in[i].second;
        }
        ans=min(ans,d[i]);
    }
    outfile << tot-ans << endl;
}
