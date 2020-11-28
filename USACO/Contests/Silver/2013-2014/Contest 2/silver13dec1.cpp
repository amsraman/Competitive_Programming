#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    ifstream infile("msched.in");
    ofstream outfile("msched.out");
    int n, g, d, ans = 0;
    vector<int> t;
    priority_queue<int> q;
    infile >> n;
    pair<int,int> in[n];
    for(int i = 0; i<n; i++)
    {
        infile >> g >> d;
        in[i] = {d,g};
    }
    t.push_back(0);
    sort(in,in+n);
    for(int i = 0; i<n; i++)
    {
        if(in[i].first!=t[t.size()-1])
        {
            t.push_back(in[i].first);
        }
    }
    int counter = n-1;
    for(int i = t.size()-1; i>0; i--)
    {
        while(in[counter].first==t[i])
        {
            q.push(in[counter].second);
            counter--;
        }
        int k = q.size();
        for(int j = 0; j<min(k,t[i]-t[i-1]); j++)
        {
            ans+=(q.top());
            q.pop();
        }
    }
    outfile << ans << endl;
}
