#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define INF 0xffffffff

using namespace std;

bool v[1000][1000] = {false};
int n, e;
long long d[1000][1000];
vector<int> g[1000];

void bfs(int a)
{
    queue<int> qu;
    v[a][a] = true;
    qu.push(a);
    for(int i = 0; i<n; i++)
    {
        d[a][i] = INF;
    }
    d[a][a] = 0;
    while(!qu.empty())
    {
        int cu = qu.front();
        qu.pop();
        for(int i = 0; i<g[cu].size(); i++)
        {
            if(!v[a][g[cu][i]])
            {
                d[a][g[cu][i]] = d[a][cu]+1;
                v[a][g[cu][i]] = true;
                qu.push(g[cu][i]);
            }
        }
    }
}

int main()
{
    ifstream infile("buffet.in");
    ofstream outfile("buffet.out");
    infile >> n >> e;
    int a, b;
    long long m[n], ans = 0;
    pair<int,int> s[n];
    for(int i = 0; i<n; i++)
    {
        infile >> s[i].first >> a;
        s[i].second = i;
        for(int j = 0; j<a; j++)
        {
            infile >> b;
            g[i].push_back(b-1);
        }
    }
    for(int i = 0; i<n; i++)
    {
        bfs(i);
    }
    sort(s,s+n);
    for(int i = 0; i<n; i++)
    {
        m[s[i].second] = s[i].first;
        for(int j = 0; j<i; j++)
        {
            if(s[j].first<s[i].first)
            {
                m[s[i].second] = max(m[s[i].second],m[s[j].second]-d[s[j].second][s[i].second]*e+s[i].first);
            }
        }
        ans = max(ans,m[s[i].second]);
    }
    outfile << ans << endl;
}
