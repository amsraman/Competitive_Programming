#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

int main()
{
    ifstream infile("feast.in");
    ofstream outfile("feast.out");
    int t, a, b, ans = 0;
    infile >> t >> a >> b;
    bool v[t+1][2];
    for(int i = 0; i<=t; i++){v[i][0]=v[i][1]=false;}
    queue<pair<int,int> > q;
    q.push({0,0});
    while(!q.empty())
    {
        ans = max(ans,q.front().first);
        if(q.front().second==0)
        {
            q.push({q.front().first/2,1});
        }
        if((q.front().first+a<=t)&&(!v[(q.front().first+a)%(t+1)][q.front().second]))
        {
            q.push({q.front().first+a,q.front().second});
            v[q.front().first+a][q.front().second] = true;
        }
        if((q.front().first+b<=t)&&(!v[(q.front().first+b)%(t+1)][q.front().second]))
        {
            q.push({q.front().first+b,q.front().second});
            v[q.front().first+b][q.front().second] = true;
        }
        q.pop();
    }
    outfile << ans << endl;
}
