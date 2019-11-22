#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int n, t, d[10000];

bool valid(int a)
{
    priority_queue<int> q;
    for(int i = 0; i<a; i++)
    {
        q.push(0);
    }
    for(int i = 0; i<n; i++)
    {
        int a = q.top();
        q.pop();
        q.push(a-d[i]);
    }
    int tm = 0;
    for(int i = 0; i<a; i++)
    {
        int a = q.top();
        a = -a;
        q.pop();
        tm = max(tm,a);
    }
    if(tm<=t)
    {
        return true;
    }
    return false;
}

int bsearch(int l, int g)
{
    int mid = (l+g)/2;
    if(l>=g)
    {
        return g;
    }
    if(valid(mid))
    {
        bsearch(l,mid);
    }
    else
    {
        bsearch(mid+1,g);
    }
}

int main()
{
    ifstream infile("cowdance.in");
    ofstream outfile("cowdance.out");
    infile >> n >> t;
    for(int i = 0; i<n; i++)
    {
        infile >> d[i];
    }
    outfile << bsearch(1,n) << endl;
}
