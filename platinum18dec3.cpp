#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m, a, b, st, par[100000], nb[1000000], cnt;
bool pre[100000], v[100000], leaf[100000], ans[100000];
vector<int> g[100000], bef[100000];

void dfs(int x)
{
    ans[x] = true;
    for(int i = 0; i<g[x].size(); i++)
    {
        if((!ans[g[x][i]])&&(!pre[g[x][i]]))
        {
            dfs(g[x][i]);
        }
    }
}

int main()
{
    ifstream infile("gathering.in");
    ofstream outfile("gathering.out");
    infile >> n >> m;
    for(int i = 0; i<n-1; i++)
    {
        infile >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
        nb[a-1]++, nb[b-1]++;
    }
    for(int i = 0; i<m; i++)
    {
        infile >> a >> b;
        pre[a-1] = true;
        par[b-1]++;
        bef[a-1].push_back(b-1);
    }
    queue<int> q;
    for(int i = 0; i<n; i++)
    {
        if(g[i].size()==1)
        {
            leaf[i] = true;
            if(par[i]==0)
            {
                q.push(i);
                v[i] = true;
            }
        }
    }
    while(!q.empty())
    {
        st = q.front();
        q.pop();
        cnt++;
        for(int i = 0; i<bef[st].size(); i++)
        {
            par[bef[st][i]]--;
            if((par[bef[st][i]]==0)&&(leaf[bef[st][i]]))
            {
                q.push(bef[st][i]);
                v[bef[st][i]] = true;
            }
        }
        for(int i = 0; i<g[st].size(); i++)
        {
            nb[g[st][i]]--;
            if((!v[g[st][i]])&&(nb[g[st][i]]==1))
            {
                leaf[g[st][i]] = true;
                if(par[g[st][i]]==0)
                {
                    q.push(g[st][i]);
                    v[g[st][i]] = true;
                }
            }
        }
    }
    if(cnt==n)
    {
        dfs(st);
    }
    for(int i = 0; i<n; i++)
    {
        outfile << ans[i] << endl;
    }
}
