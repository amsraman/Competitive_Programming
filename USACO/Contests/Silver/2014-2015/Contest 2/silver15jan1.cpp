#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#define INF 0x3f3f3f3f

using namespace std;

int main()
{
    ifstream infile("stampede.in");
    ofstream outfile("stampede.out");
    int n, x, y, r, ans = 0;
    infile >> n;
    vector<pair<int,int> > t;
    int ex[n];
    bool v[n], open[n];
    for(int i = 0; i<n; i++)
    {
        v[i] = false;
        open[i] = false;
        infile >> x >> y >> r;
        ex[i] = y;
        t.push_back({-x*r,i});
        t.push_back({(-1-x)*r,i});
    }
    t.push_back({INF,0});
    sort(t.begin(),t.end());
    set<pair<int,int> > s;
    for(int i = 0; i<t.size()-1; i++)
    {
        if(!open[t[i].second])
        {
            s.insert({ex[t[i].second],t[i].second});
        }
        else
        {
            s.erase({ex[t[i].second],t[i].second});
        }
        open[t[i].second] = !open[t[i].second];
        if((s.size()!=0)&&(double(t[i].first)!=double(t[i+1].first)))
        {
            if(!v[(*(s.begin())).second])
            {
                ans++;
                v[(*(s.begin())).second] = true;
            }
        }
    }
    outfile << ans << endl;
}
