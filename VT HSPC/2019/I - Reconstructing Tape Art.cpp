#include <bits/stdc++.h>

using namespace std;

int n, c[100000];
pair<int,int> seq[100000];
pair<pair<int,int>,int> interval[100000];
bool vis[100000], in[100000], cyc;
vector<int> vec;

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        cin >> c[i];
        vis[c[i]-1] = true;
        interval[i].second = i;
        interval[c[i]-1].first.second = i+1;
    }
    for(int i = n-1; i>=0; i--) interval[c[i]-1].first.first = i+1;
    sort(interval,interval+n);
    int npc = 0;
    for(int i = 0; i<n; i++) if(!vis[i]) npc++;
    for(int i = 0; i<n; i++)
    {
        if(interval[i].first.first!=interval[i].first.second)
        {
            seq[interval[i].first.first-1] = {interval[i].second,1};
            seq[interval[i].first.second-1] = {interval[i].second,2};
        }
    }
    for(int i = 0; i<n; i++)
    {
        if(seq[i].second==1) vec.push_back(seq[i].first), in[seq[i].first] = true;
        if((seq[i].second==2)&&(seq[i].first!=vec[vec.size()-1])) cyc = true;
        if((in[c[i]-1])&&(c[i]!=vec[vec.size()-1]+1)) cyc = true;
        if((seq[i].second==2)&&(seq[i].first==vec[vec.size()-1])) vec.pop_back(), in[seq[i].first] = false;
    }
    if(cyc) cout << "IMPOSSIBLE" << endl;
    else
    {
        cout << n-npc << endl;
        for(int i = npc; i<n; i++)
        {
            cout << interval[i].first.first << " " << interval[i].first.second << " " << interval[i].second+1 << endl;
        }
    }
}
