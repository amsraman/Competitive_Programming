#include <fstream>
#include <iostream>
#include <algorithm>
typedef long long ll;
typedef long double ld;

using namespace std;

int n, cur = 1;
long double f[100002];
pair<long double,long double> hull[100000];

int main()
{
    ifstream infile("balance.in");
    ofstream outfile("balance.out");
    infile >> n;
    f[0] = f[n+1] = 0;
    for(int i = 0; i<n; i++)
    {
        infile >> f[i+1];
    }
    hull[0] = {0,f[0]};
    hull[1] = {1,f[1]};
    for(int i = 2; i<n+2; i++)
    {
        while((cur>0)&&((hull[cur].first-hull[cur-1].first)*(f[i]-hull[cur].second)-(hull[cur].second-hull[cur-1].second)*(i-hull[cur].first)>0))
        {
            cur--;
        }
        cur++;
        hull[cur] = {i,f[i]};
    }
    for(int i = 1; i<hull[1].first; i++)
    {
        outfile << ll(100000*hull[1].second*i/hull[1].first) << endl;
    }
    for(int i = 1; i<cur; i++)
    {
        outfile << ll(100000*hull[i].second) << endl;
        for(int j = hull[i].first+1; j<hull[i+1].first; j++)
        {
            outfile << ll(100000*hull[i].second+100000*(ld(j)-hull[i].first)*(hull[i+1].second-hull[i].second)/(hull[i+1].first-hull[i].first)) << endl;
        }
    }
}
