/*
ID: adityasund1
TASK: agrinet
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    ifstream infile("agrinet.in");
    ofstream outfile("agrinet.out");
    int n, a, ans = 0;
    infile >> n;
    vector<pair<int,int> > g[n];
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            infile >> a;
            if(a!=0)
            {
                g[i].push_back({j,a});
            }
        }
    }
    priority_queue<pair<int,int> > q;
    bool v[100] = {false};
    q.push({0,0});
    while(!q.empty())
    {
        int x = q.top().second;
        int y = q.top().first;
        q.pop();
        if(!v[x])
        {
            v[x] = true;
            ans-=y;
            for(int i = 0; i<g[x].size(); i++)
            {
                if(!v[g[x][i].first])
                {
                    q.push({-g[x][i].second,g[x][i].first});
                }
            }
        }
    }
    outfile << ans << endl;
}
