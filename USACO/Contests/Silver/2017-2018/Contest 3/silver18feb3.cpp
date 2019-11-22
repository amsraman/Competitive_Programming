#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ifstream infile("teleport.in");
    ofstream outfile("teleport.out");
    int n, s = 0;
    long long a, b, cy = 0, ans;
    vector<pair<long long,int> > p;
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> a >> b;
        cy+=(max(a,b)-min(a,b));
        if((max(a,b)>=0)&&(min(a,b)<=0))
        {
            p.push_back({0,-1});
            p.push_back({b,2});
            p.push_back({2*b,-1});
        }
        else if((min(a,b)>=0)&&(b>2*a))
        {
            p.push_back({2*a,-1});
            p.push_back({b,2});
            p.push_back({2*b-2*a,-1});
        }
        else if((max(a,b)<=0)&&(b<2*a))
        {
            p.push_back({2*b-2*a,-1});
            p.push_back({b,2});
            p.push_back({2*a,-1});
        }
    }
    sort(p.begin(),p.end());
    ans = cy;
    s = p[0].second;
    for(int i = 1; i<p.size(); i++)
    {
        if(p[i].first!=p[i-1].first)
        {
            cy+=s*(p[i].first-p[i-1].first);
            ans = min(ans,cy);
        }
        s+=p[i].second;
    }
    outfile << ans << endl;
}
