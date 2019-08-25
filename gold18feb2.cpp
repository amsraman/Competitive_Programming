#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define INF 0xfffffffffffffff

using namespace std;

int n, x, y;
long long siz[100000], fc[100000], path[100000];
long long ans = INF;
bool fold[100000];
vector<pair<bool,int> > g[100000];

void fcount(int a)
{
    int z = 0;
    if(!fold[a]){z++;}
    for(int i = 0; i<g[a].size(); i++)
    {
        if(g[a][i].first)
        {
            fcount(g[a][i].second);
            z+=fc[g[a][i].second];
        }
    }
    fc[a] = z;
}

long long fpath(int a)
{
    long long z = siz[a]*fc[a];
    for(int i = 0; i<g[a].size(); i++)
    {
        if(g[a][i].first)
        {
            path[g[a][i].second] = fpath(g[a][i].second);
            z+=(path[g[a][i].second]+fc[g[a][i].second]);
        }
    }
    return z;
}

void fpath2(int prev, int a)
{
    if((a!=prev)&&(fold[a]))
    {
        path[a] = (fc[0]-fc[a])*3+path[prev]-fc[prev]-fc[prev]*siz[prev];
    }
    if(fold[a])
    {
        ans = min(ans,path[a]-siz[a]*fc[a]-fc[a]);
    }
    for(int i = 0; i<g[a].size(); i++)
    {
        if(g[a][i].first)
        {
            fpath2(a,g[a][i].second);
        }
    }
}

int main()
{
    ifstream infile("dirtraverse.in");
    ofstream outfile("dirtraverse.out");
    infile >> n;
    string a;
    for(int i = 0; i<n; i++)
    {
        infile >> a >> x;
        siz[i] = a.length();
        for(int j = 0; j<x; j++)
        {
            fold[i] = true;
            infile >> y;
            g[i].push_back({true,y-1});
            g[y-1].push_back({false,i});
        }
    }
    fcount(0);
    path[0] = fpath(0);
    fpath2(0,0);
    outfile << ans << endl;
}
