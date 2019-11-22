#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int main()
{
    ifstream infile("measurement.in");
    ofstream outfile("measurement.out");
    int n, g;
    infile >> n >> g;
    map<int,int> cnt, id;
    cnt[g] = 0;
    pair<int,pair<int,int> > in[n];
    for(int i = 0; i<n; i++)
    {
        infile >> in[i].first >> in[i].second.first >> in[i].second.second;
        if(!cnt.count(in[i].second.first))
        {
            id[in[i].second.first] = g;
            cnt[g]++;
        }
    }
    sort(in,in+n);
    int ans = 0, nw = cnt[g], ma = g;
    for(int i = 0; i<n; i++)
    {
        cnt[id[in[i].second.first]]--;
        if(cnt[id[in[i].second.first]]==0)
        {
            cnt.erase(id[in[i].second.first]);
        }
        id[in[i].second.first]+=in[i].second.second;
        if(!cnt.count(id[in[i].second.first]))
        {
            cnt[id[in[i].second.first]] = 1;
        }
        else
        {
            cnt[id[in[i].second.first]]++;
        }
        map<int,int>::iterator x = cnt.end();
        x--;
        if(nw!=(x)->second)
        {
            nw = (x)->second;
        }
        else if(((id[in[i].second.first]-in[i].second.second==ma)&&(id[in[i].second.first]==(x)->first))||((id[in[i].second.first]-in[i].second.second!=ma)&&(id[in[i].second.first]!=(x)->first)))
        {
            ans--;
        }
        ma = (x)->first;
        ans++;
    }
    outfile << ans << endl;
}
