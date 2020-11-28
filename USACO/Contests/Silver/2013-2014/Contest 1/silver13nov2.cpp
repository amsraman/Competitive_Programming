#include <fstream>
#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

int n, d, l[50000], r[50000], ans;
pair<int,int> in[50000];
deque<pair<int,int> > dq;

int main()
{
    ifstream infile("crowded.in");
    ofstream outfile("crowded.out");
    infile >> n >> d;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i].first >> in[i].second;
    }
    sort(in,in+n);
    l[0] = in[0].second;
    dq.push_back(in[0]);
    for(int i = 1; i<n; i++)
    {
        while((dq.size()>0)&&(dq[dq.size()-1].second<=in[i].second))
        {
            dq.pop_back();
        }
        dq.push_back(in[i]);
        while((dq.size()>0)&&(dq[0].first<in[i].first-d))
        {
            dq.pop_front();
        }
        l[i] = (dq.size()>0)?dq[0].second:0;
    }
    dq.clear();
    dq.push_back(in[n-1]);
    r[n-1] = in[n-1].second;
    for(int i = n-2; i>=0; i--)
    {
        while((dq.size()>0)&&(dq[dq.size()-1].second<=in[i].second))
        {
            dq.pop_back();
        }
        dq.push_back(in[i]);
        while((dq.size()>0)&&(dq[0].first>in[i].first+d))
        {
            dq.pop_front();
        }
        r[i] = (dq.size()>0)?dq[0].second:0;
    }
    for(int i = 0; i<n; i++)
    {
        if((l[i]>=2*in[i].second)&&(r[i]>=2*in[i].second))
        {
            ans++;
        }
    }
    outfile << ans << endl;
}
