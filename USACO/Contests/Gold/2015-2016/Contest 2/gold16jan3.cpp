#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <set>
#include <vector>

using namespace std;

int main()
{
    ifstream infile("lightsout.in");
    ofstream outfile("lightsout.out");
    int n, dr, ans = 0;
    infile >> n;
    int d[n], tot;
    double ang[n];
    pair<int,int> p[n];
    multiset<vector<double> > ms;
    for(int i = 0; i<n; i++)
    {
        infile >> p[i].first >> p[i].second;
    }
    d[0] = 0;
    tot = abs(p[n-1].first-p[0].first)+abs(p[n-1].second-p[0].second);
    ang[0] = double(((p[0].first-p[n-1].first)*(p[1].second-p[0].second)-(p[0].second-p[n-1].second)*(p[1].first-p[0].first))/abs((p[0].first-p[n-1].first)*(p[1].second-p[0].second)-(p[0].second-p[n-1].second)*(p[1].first-p[0].first)))/2;
    for(int i = 1; i<n; i++)
    {
        d[i] = d[i-1]+abs(p[i].first-p[i-1].first)+abs(p[i].second-p[i-1].second);
        tot+=(d[i]-d[i-1]);
        int det = (p[(i+n)%n].first-p[(i+n-1)%n].first)*(p[(i+n+1)%n].second-p[(i+n)%n].second)-(p[(i+n)%n].second-p[(i+n-1)%n].second)*(p[(i+n+1)%n].first-p[(i+n)%n].first);
        ang[i] = double(det/abs(det))/2;
    }
    for(int i = 0; i<n; i++)
    {
        vector<double> temp;
        temp.push_back(ang[i]);
        ms.insert(temp);
        for(int j = 1; j<=n; j++)
        {
            temp.push_back(abs(p[(i+j+n)%n].first-p[(i+j+n-1)%n].first)+abs(p[(i+j+n)%n].second-p[(i+j+n-1)%n].second));
            temp.push_back(ang[(i+j)%n]);
            ms.insert(temp);
        }
        while(temp.size()>0)
        {
            temp.pop_back();
        }
    }
    for(int i = 1; i<n; i++)
    {
        int j = 1;
        vector<double> temp;
        dr = 0;
        temp.push_back(ang[i]);
        while(ms.count(temp)>1)
        {
            dr+=(abs(p[(i+j)%n].first-p[(i+j+n-1)%n].first)+abs(p[(i+j)%n].second-p[(i+j+n-1)%n].second));
            temp.push_back(abs(p[(i+j)%n].first-p[(i+j+n-1)%n].first)+abs(p[(i+j)%n].second-p[(i+j+n-1)%n].second));
            temp.push_back(ang[(i+j)%n]);
            j++;
        }
        ans = max(ans,min(2*dr+d[i],tot-d[i])-min(d[i],tot-d[i]));
        while(temp.size()>0)
        {
            temp.pop_back();
        }
    }
    outfile << ans << endl;
}
