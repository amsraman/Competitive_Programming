#include <fstream>
#include <iostream>
#include <vector>
#define MAXN (1<<17)

using namespace std;

int n, a, in[100000], pos[100001], seg[2*MAXN];
vector<pair<int,int> > v;

int query(int x)
{
    int low = MAXN, high = x+MAXN, ret = 0;
    while(low<=high)
    {
        if(high%2==0) ret = max(ret,seg[high]), high--;
        if(low%2==1) ret = max(ret,seg[low]), low++;
        low/=2, high/=2;
    }
    return ret;
}

void update(int k, int x)
{
    k+=MAXN, seg[k] = x;
    while(k>1)
    {
        k/=2;
        seg[k] = max(seg[2*k],seg[2*k+1]);
    }
}

int main()
{
    ifstream infile("nocross.in");
    ofstream outfile("nocross.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i];
    }
    for(int i = 0; i<n; i++)
    {
        infile >> a;
        pos[a] = i;
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = max(1,in[i]-4); j<min(n,in[i]+5); j++)
        {
            int k = 1+query(pos[j]-1);
            v.push_back(make_pair(pos[j],k));
        }
        while(v.size()!=0)
        {
            update(v[v.size()-1].first,v[v.size()-1].second);
            v.pop_back();
        }
    }
    outfile << query(n-1) << endl;
}
