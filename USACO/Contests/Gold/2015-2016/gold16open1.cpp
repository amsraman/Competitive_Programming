#include <fstream>
#include <iostream>
#include <algorithm>
#define INF 0xfffffffffffffff

using namespace std;

int n;
long long a1, a2 = INF;
pair<long long,long long> p1[50000], p2[50000], minx1[50000], miny1[50000], maxx1[50000], maxy1[50000], minx2[50000], miny2[50000], maxx2[50000], maxy2[50000];

int main()
{
    ifstream infile("split.in");
    ofstream outfile("split.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> p1[i].first >> p1[i].second;
        p2[i] = {p1[i].second,p1[i].first};
    }
    sort(p1,p1+n);
    sort(p2,p2+n);
    for(int i = 0; i<n; i++)
    {
        if(i==0)
        {
            minx1[i].first = maxx1[i].first = p1[i].first;
            minx2[i].first = maxx2[i].first = p2[i].first;
            miny1[i].first = maxy1[i].first = p1[i].second;
            miny2[i].first = maxy2[i].first = p2[i].second;
        }
        else
        {
            minx1[i].first = min(minx1[i-1].first,p1[i].first);
            minx2[i].first = min(minx2[i-1].first,p2[i].first);
            maxx1[i].first = max(maxx1[i-1].first,p1[i].first);
            maxx2[i].first = max(maxx2[i-1].first,p2[i].first);
            miny1[i].first = min(miny1[i-1].first,p1[i].second);
            miny2[i].first = min(miny2[i-1].first,p2[i].second);
            maxy1[i].first = max(maxy1[i-1].first,p1[i].second);
            maxy2[i].first = max(maxy2[i-1].first,p2[i].second);
        }
    }
    a1 = (maxx1[n-1].first-minx1[n-1].first)*(maxy1[n-1].first-miny1[n-1].first);
    for(int i = n-1; i>=0; i--)
    {
        if(i==n-1)
        {
            minx1[i].second = maxx1[i].second = p1[i].first;
            minx2[i].second = maxx2[i].second = p2[i].first;
            miny1[i].second = maxy1[i].second = p1[i].second;
            miny2[i].second = maxy2[i].second = p2[i].second;
        }
        else
        {
            minx1[i].second = min(minx1[i+1].second,p1[i].first);
            minx2[i].second = min(minx2[i+1].second,p2[i].first);
            maxx1[i].second = max(maxx1[i+1].second,p1[i].first);
            maxx2[i].second = max(maxx2[i+1].second,p2[i].first);
            miny1[i].second = min(miny1[i+1].second,p1[i].second);
            miny2[i].second = min(miny2[i+1].second,p2[i].second);
            maxy1[i].second = max(maxy1[i+1].second,p1[i].second);
            maxy2[i].second = max(maxy2[i+1].second,p2[i].second);
        }
    }
    for(int i = 0; i<n-1; i++)
    {
        if(p1[i].first!=p1[i+1].first)
        {
            a2 = min(a2,(maxx1[i].first-minx1[i].first)*(maxy1[i].first-miny1[i].first)+(maxx1[i+1].second-minx1[i+1].second)*(maxy1[i+1].second-miny1[i+1].second));
        }
        if(p2[i].first!=p2[i+1].first)
        {
            a2 = min(a2,(maxx2[i].first-minx2[i].first)*(maxy2[i].first-miny2[i].first)+(maxx2[i+1].second-minx2[i+1].second)*(maxy2[i+1].second-miny2[i+1].second));
        }
    }
    outfile << a1-a2 << endl;
}
