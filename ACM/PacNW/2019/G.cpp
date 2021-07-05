#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n;
ll ans;
char type;
vector<int> intervals[2];
vector<pair<int,int>> pulses;

int num_under(int ind, int x)
{
    if(intervals[ind].empty())
        return 0;
    int lb = 0, ub = intervals[ind].size()-1;
    while(lb<ub)
    {
        int mid = (lb+ub+1)/2;
        if(intervals[ind][mid]<x)
            lb = mid;
        else
            ub = mid-1;
    }
    if(intervals[ind][ub]<x)
        ++ub;
    return ub;
}

int main()
{
    cin >> n;
    for(int i = 0, t, m, a; i<n; i++)
    {
        cin >> type >> t >> m >> a;
        if(type=='h')
            pulses.push_back({t-a,t-a+m});
        else
            intervals[0].push_back(t-a), intervals[1].push_back(t-a+m);
    }
    sort(intervals[0].begin(),intervals[0].end());
    sort(intervals[1].begin(),intervals[1].end());
    for(int i = 0; i<pulses.size(); i++)
        ans+=(num_under(0,pulses[i].s)-num_under(1,pulses[i].f+1));
    cout << ans << endl;
}