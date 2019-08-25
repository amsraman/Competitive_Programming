#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int link[100000], siz[100000], ans[100000];

int f(int a)
{
    while(a!=link[a])
    {
        a = link[a];
    }
    return a;
}

void unite(int a, int b)
{
    a = f(a);
    b = f(b);
    if(siz[a]<siz[b])
    {
        int t = a;
        a = b;
        b = t;
    }
    link[b] = a;
    siz[a]+=siz[b];
}

int main()
{
    ifstream infile("mootube.in");
    ofstream outfile("mootube.out");
    int n, q, a, cure = 0;
    infile >> n >> q;
    pair<int,pair<int,int> > edge[n];
    pair<int,pair<int,int> > query[q];
    for(int i = 0; i<n-1; i++)
    {
        infile >> edge[i].second.first >> edge[i].second.second >> a;
        edge[i].first = -a;
        link[i] = i;
        siz[i] = 1;
    }
    edge[n-1] = {0,{0,0}};
    link[n-1] = n-1;
    siz[n-1] = 1;
    for(int i = 0; i<q; i++)
    {
        infile >> a >> query[i].second.first;
        query[i].first = -a;
        query[i].second.second = i;
    }
    sort(edge,edge+n);
    sort(query,query+q);
    for(int i = 0; i<q; i++)
    {
        while(edge[cure].first<=query[i].first)
        {
            unite(edge[cure].second.first,edge[cure].second.second);
            cure++;
        }
        ans[query[i].second.second] = siz[f(query[i].second.first)];
    }
    for(int i = 0; i<q; i++)
    {
        outfile << ans[i]-1 << endl;
    }
}
