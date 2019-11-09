#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n, m, a, b, in[200000], link[200000], siz[200000];
vector<int> g[200000];
bool open[200000], ans[200000];

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
    ifstream infile("closing.in");
    ofstream outfile("closing.out");
    infile >> n >> m;
    for(int i = 0; i<m; i++)
    {
        infile >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    for(int i = 0; i<n; i++)
    {
        link[i] = i;
        siz[i] = 1;
        infile >> in[i];
        in[i]--;
    }
    for(int i = n-1; i>=0; i--)
    {
        open[in[i]] = true;
        for(int j = 0; j<g[in[i]].size(); j++)
        {
            if((open[g[in[i]][j]])&&(f(g[in[i]][j])!=f(in[i])))
            {
                unite(in[i],g[in[i]][j]);
            }
        }
        if(siz[f(in[i])]==n-i)
        {
            ans[i] = true;
        }
    }
    for(int i = 0; i<n; i++)
    {
        if(ans[i])
        {
            outfile << "YES" << endl;
        }
        else
        {
            outfile << "NO" << endl;
        }
    }
}
