#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

int main()
{
    ifstream infile("superbull.in");
    ofstream outfile("superbull.out");
    int n;
    long long ans = 0;
    infile >> n;
    int id[n];
    bool v[n];
    for(int i = 0; i<n; i++)
    {
        infile >> id[i];
        v[i] = false;
    }
    priority_queue<pair<int,int> > q;
    q.push({0,0});
    while(!q.empty())
    {
        int a = q.top().second, b = q.top().first;
        q.pop();
        if(!v[a])
        {
            v[a] = true;
            ans+=b;
            for(int i = 0; i<n; i++)
            {
                if(!v[i])
                {
                    int k = id[a]^id[i];
                    q.push({k,i});
                }
            }
        }
    }
    outfile << ans << endl;
}
