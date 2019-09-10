/*
ID: adityasund1
TASK: fc
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#define PI 4*atan(1)

using namespace std;

int main()
{
    ifstream infile("fc.in");
    ofstream outfile("fc.out");
    int n, curh = 1, begh = 0;
    infile >> n;
    double ans = 0;
    pair<double,pair<double,double> > p[n];
    pair<double,double> center, hull[n];
    center.first = center.second = 0;
    for(int i = 0; i<n; i++)
    {
        infile >> p[i].second.first >> p[i].second.second;
        center.first+=p[i].second.first;
        center.second+=p[i].second.second;
    }
    center.first/=double(n);
    center.second/=double(n);
    for(int i = 0; i<n; i++)
    {
        p[i].first = (atan2(p[i].second.second-center.second,p[i].second.first-center.first)<0)?atan2(p[i].second.second-center.second,p[i].second.first-center.first)+2*PI:atan2(p[i].second.second-center.second,p[i].second.first-center.first);
    }
    sort(p,p+n);
    hull[0] = {p[0].second.first,p[0].second.second};
    hull[1] = {p[1].second.first,p[1].second.second};
    for(int i = 2; i<n; i++)
    {
        while((curh>0)&&((p[i%n].second.first-hull[curh].first)*(hull[curh].second-hull[curh-1].second)-(p[i%n].second.second-hull[curh].second)*(hull[curh].first-hull[curh-1].first)>0))
        {
            curh--;
        }
        curh++;
        hull[curh] = {p[i%n].second.first,p[i%n].second.second};
    }
    while(((hull[begh+1].first-hull[begh].first)*(hull[begh].second-hull[curh].second)-(hull[begh+1].second-hull[begh].second)*(hull[begh].first-hull[curh].first)>0)||((hull[begh].first-hull[curh].first)*(hull[curh].second-hull[curh-1].second)-(hull[begh].second-hull[curh].second)*(hull[curh].first-hull[curh-1].first)>0))
    {
        if((hull[begh+1].first-hull[begh].first)*(hull[begh].second-hull[curh].second)-(hull[begh+1].second-hull[begh].second)*(hull[begh].first-hull[curh].first)>0)
        {
            begh++;
        }
        else
        {
            curh--;
        }
    }
    ans = sqrt((hull[begh].first-hull[curh].first)*(hull[begh].first-hull[curh].first)+(hull[begh].second-hull[curh].second)*(hull[begh].second-hull[curh].second));
    for(int i = begh; i<curh; i++)
    {
        ans+=sqrt((hull[i+1].first-hull[i].first)*(hull[i+1].first-hull[i].first)+(hull[i+1].second-hull[i].second)*(hull[i+1].second-hull[i].second));
    }
    outfile << fixed << setprecision(2) << ans << endl;
}
