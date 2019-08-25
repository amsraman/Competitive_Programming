#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m, pred[100000];
vector<int> top;
vector<pair<int,int> > g[100000];
bool ac, v[100000];

void topsort(int k)
{
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<g[i].size(); j++)
        {
            if(g[i][j].second<=k)
            {
                pred[g[i][j].first]++;
            }
        }
    }
    priority_queue<int> q;
    for(int i = 0; i<n; i++)
    {
        if(pred[i]==0)
        {
            v[i] = true;
            q.push(-i);
        }
    }
    while(!q.empty())
    {
        int a = -q.top();
        q.pop();
        top.push_back(a);
        for(int i = 0; i<g[a].size(); i++)
        {
            if(g[a][i].second<=k)
            {
                pred[g[a][i].first]--;
                if(pred[g[a][i].first]==0)
                {
                    v[g[a][i].first] = true;
                    q.push(-g[a][i].first);
                }
            }
        }
    }
    if(top.size()!=n){ac = false;}
}

int main()
{
    ifstream infile("milkorder.in");
    ofstream outfile("milkorder.out");
    infile >> n >> m;
    int a, b, c, l = 0, u = m-1;
    for(int i = 0; i<m; i++)
    {
        infile >> a >> b;
        for(int j = 1; j<a; j++)
        {
            infile >> c;
            g[b-1].push_back({c-1,i});
            b = c;
        }
    }
    while(l<u)
    {
        ac = true;
        int mid = (l+u+1)/2;
        for(int i = 0; i<n; i++)
        {
            pred[i] = 0;
            v[i] = false;
        }
        topsort(mid);
        top.clear();
        if(ac){l = mid;}
        else{u = mid-1;}
    }
    for(int i = 0; i<n; i++)
    {
        pred[i] = 0;
        v[i] = 0;
    }
    topsort(l);
    outfile << top[0]+1;
    for(int i = 1; i<n; i++)
    {
        outfile << " " << top[i]+1;
    }
    outfile << endl;
}
