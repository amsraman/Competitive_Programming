#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int n, cnt, curt, ans;
pair<int,int> s[100000];
pair<int,pair<int,int> > in[100000];

int main()
{
    ifstream infile("convention2.in");
    ofstream outfile("convention2.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        in[i].first = n-i;
        infile >> in[i].second.first >> in[i].second.second;
        s[i].first = in[i].second.first;
        s[i].second = i;
    }
    sort(s,s+n);
    priority_queue<pair<int,pair<int,int> > > q;
    curt = s[0].first;
    cnt = 1;
    q.push(in[s[0].second]);
    while(!q.empty())
    {
        int x = q.top().second.first, y = q.top().second.second;
        q.pop();
        ans = max(ans,curt-x);
        curt+=y;
        while((s[cnt].first<=curt)&&(cnt<n))
        {
            q.push(in[s[cnt].second]);
            cnt++;
        }
        if((q.size()==0)&&(cnt!=n))
        {
            curt = s[cnt].first;
            q.push(in[s[cnt].second]);
            cnt++;
        }
    }
    outfile << ans << endl;
}
