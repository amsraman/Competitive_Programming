#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int link[2000], siz[2000];
int maxs = 0;

int f(int a)
{
    while(a!=link[a])
    {
        a = link[a];
    }
    return a;
}

bool same(int a, int b)
{
    return f(a)==f(b);
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
    maxs = max(maxs,siz[a]);
}

int main()
{
    ifstream infile("irrigation.in");
    ofstream outfile("irrigation.out");
    int n, c;
    infile >> n >> c;
    pair<int,int> in[n];
    vector<pair<int,pair<int,int> > > edges;
    for(int i = 0; i<n; i++)
    {
        infile >> in[i].first >> in[i].second;
        link[i] = i;
        siz[i] = 1;
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            if((in[j].first-in[i].first)*(in[j].first-in[i].first)+(in[j].second-in[i].second)*(in[j].second-in[i].second)>=c)
            {
                edges.push_back({(in[j].first-in[i].first)*(in[j].first-in[i].first)+(in[j].second-in[i].second)*(in[j].second-in[i].second),{i,j}});
            }
        }
    }
    long long ans = 0;
    sort(edges.begin(),edges.end());
    unite(edges[0].second.first,edges[0].second.second);
    ans+=edges[0].first;
    for(int i = 1; i<edges.size(); i++)
    {
        if(!same(edges[i].second.first,edges[i].second.second))
        {
            unite(edges[i].second.first,edges[i].second.second);
            ans+=edges[i].first;
        }
    }
    if(maxs!=n)
    {
        outfile << -1 << endl;
    }
    else
    {
        outfile << ans << endl;
    }
}
