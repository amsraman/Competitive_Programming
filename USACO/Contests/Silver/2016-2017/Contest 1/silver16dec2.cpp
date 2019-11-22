#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    ifstream infile("citystate.in");
    ofstream outfile("citystate.out");
    int n;
    infile >> n;
    pair<string,int> in[n];
    string a, b;
    for(int i = 0; i<n; i++)
    {
        infile >> a >> b;
        a = a.substr(0,2);
        if(a<b)
        {
            in[i].first = a+b;
            in[i].second = 0;
        }
        else
        {
            in[i].first = b+a;
            in[i].second = 1;
        }
    }
    sort(in,in+n);
    pair<int,int> c1[n];
    int c2 = 0;
    if(in[0].second==0)
    {
        c1[0] = {1,0};
    }
    else
    {
        c1[0] = {0,1};
    }
    for(int i = 1; i<n; i++)
    {
        if(in[i].first!=in[i-1].first)
        {
            c2++;
            c1[c2] = {0,0};
        }
        if(in[i].first.substr(0,2)==in[i].first.substr(2,2))
        {
            c1[c2].first = -1;
            c1[c2].first++;
        }
        if(in[i].second==0)
        {
            c1[c2].first++;
        }
        else
        {
            c1[c2].second++;
        }
    }
    c2++;
    int ans = 0;
    for(int i = 0; i<c2; i++)
    {
        if(c1[i].first==-1)
        {
            ans+=c1[i].second*(c1[i].second-1)/2;
        }
        else
        {
            ans+=c1[i].first*c1[i].second;
        }
    }
    outfile << ans << endl;
}
