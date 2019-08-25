#include <fstream>
#include <iostream>
#include <deque>

using namespace std;

int n, k, pre[300001], dp[300001], p1, p2;
deque<pair<int,int> > dq;
string in;

int main()
{
    ifstream infile("redistricting.in");
    ofstream outfile("redistricting.out");
    infile >> n >> k >> in;
    for(int i = 0; i<n; i++)
    {
        pre[i+1] = pre[i]+(2*int(in[i]=='G')-1);
    }
    dq.push_back(make_pair(0,0));
    for(int i = 1; i<=n; i++)
    {
        dp[i] = dq[0].first+int(pre[i]+dq[0].second>=0);
        while((dq.size()>0)&&(dq[dq.size()-1]>make_pair(dp[i],-pre[i]))) dq.pop_back();
        dq.push_back(make_pair(dp[i],-pre[i]));
        if((i>=k)&&(dp[i-k]==dq[0].first)&&(pre[i-k]==-dq[0].second)) dq.pop_front();
    }
    outfile << dp[n] << endl;
}
