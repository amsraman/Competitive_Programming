#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, a, tot, p[100000], siz[100000], id[100000], bit[100001], ans[100000];
pair<int,int> s[100000];
vector<int> g[100000];
bool v[100000];

int sum(int k)
{
    k++;
    int ret = 0;
    while(k>0)
    {
        ret+=bit[k];
        k-=(k&(-k));
    }
    return ret;
}

void update(int k)
{
    k++;
    while(k<=n)
    {
        bit[k]++;
        k+=(k&(-k));
    }
}

void dfs(int a)
{
    v[a] = true;
    siz[a] = 1;
    id[a] = tot;
    tot++;
    for(int i = 0; i<g[a].size(); i++)
    {
        if(!v[g[a][i]])
        {
            dfs(g[a][i]);
            siz[a]+=siz[g[a][i]];
        }
    }
}

int main()
{
    ifstream infile("promote.in");
    ofstream outfile("promote.out");
    infile >> n;
    for(int i = 0; i<n; i++)
    {
        infile >> p[i];
        s[i] = make_pair(p[i],i);
    }
    for(int i = 0; i<n-1; i++)
    {
        infile >> a;
        g[i+1].push_back(a-1);
        g[a-1].push_back(i+1);
    }
    sort(s,s+n);
    dfs(0);
    for(int i = n-1; i>=0; i--)
    {
        ans[s[i].second] = sum(id[s[i].second]+siz[s[i].second]-1)-sum(id[s[i].second]);
        update(id[s[i].second]);
    }
    for(int i = 0; i<n; i++)
    {
        outfile << ans[i] << endl;
    }
}
