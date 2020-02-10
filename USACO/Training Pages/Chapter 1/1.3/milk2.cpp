/*
ID: adityasund1
TASK: milk2
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int n, ans1, ans2;
pair<int,int> in[5000];
vector<pair<int,int> > vec;

int main()
{
    freopen("milk2.in","r",stdin);
    freopen("milk2.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> in[i].first >> in[i].second;
    sort(in,in+n);
    vec.push_back(in[0]);
    for(int i = 1; i<n; i++)
    {
        int st = in[i].first;
        if(in[i].second<=vec[vec.size()-1].second)
            continue;
        if(vec[vec.size()-1].second>=in[i].first)
            st = vec[vec.size()-1].first, vec.pop_back();
        vec.push_back({st,in[i].second});
    }
    ans1 = vec[0].second-vec[0].first;
    for(int i = 1; i<vec.size(); i++)
        ans1 = max(ans1,vec[i].second-vec[i].first), ans2 = max(ans2,vec[i].first-vec[i-1].second);
    cout << ans1 << " " << ans2 << endl;
}
