#include <fstream>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int n, b, qc, ans[100000];
pair<int,int> f[100000];
pair<pair<int,int>,int> q[100000];
set<int> loc;
multiset<int> maxd;

int main()
{
    ifstream infile("snowboots.in");
    ofstream outfile("snowboots.out");
    infile >> n >> b;
    loc.insert(0);
    loc.insert(n+1);
    maxd.insert(n+1);
    for(int i = 0; i<n; i++)
    {
        infile >> f[i].first;
        f[i].second = i+1;
    }
    for(int i = 0; i<b; i++)
    {
        infile >> q[i].first.first >> q[i].first.second;
        q[i].second = i;
    }
    sort(f,f+n);
    sort(q,q+b);
    for(int i = 0; i<n; i++)
    {
        loc.insert(f[i].second);
        set<int>::iterator it1, it2, it3;
        it1 = it2 = it3 = loc.find(f[i].second);
        it1--;
        it3++;
        maxd.erase(maxd.find((*it3)-(*it1)));
        maxd.insert((*it2)-(*it1));
        maxd.insert((*it3)-(*it2));
        if((i==n-1)||(f[i].first!=f[i+1].first))
        {
            int dmax = (*(--maxd.end()));
            while((qc<b)&&(q[qc].first.first>=f[i].first)&&((q[qc].first.first<f[i+1].first)||(i==n-1)))
            {
                if(q[qc].first.second>=dmax)
                {
                    ans[q[qc].second] = 1;
                }
                qc++;
            }
        }
    }
    for(int i = 0; i<b; i++)
    {
        outfile << ans[i] << endl;
    }
}
