/*
ID: adityasund1
TASK: job
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

int n, m1, m2, a[1000], b[1000];

int main()
{
    ifstream infile("job.in");
    ofstream outfile("job.out");
    int z, ans1 = 0, ans2 = 0;
    priority_queue<pair<int,int> > q1, q2;
    infile >> n >> m1 >> m2;
    for(int i = 0; i<m1; i++)
    {
        infile >> z;
        q1.push({-z,z});
    }
    for(int i = 0; i<m2; i++)
    {
        infile >> z;
        q2.push({-z,z});
    }
    for(int i = 0; i<n; i++)
    {
        a[i] = -q1.top().first;
        ans1 = max(ans1,a[i]);
        int x = q1.top().second;
        q1.pop();
        q1.push({-a[i]-x,x});
    }
    for(int i = 0; i<n; i++)
    {
        b[i] = -q2.top().first;
        int x = q2.top().second;
        q2.pop();
        q2.push({-b[i]-x,x});
    }
    for(int i = 0; i<n; i++)
    {
        ans2 = max(ans2,a[i]+b[n-1-i]);
    }
    outfile << ans1 << " " << ans2 << endl;
}
