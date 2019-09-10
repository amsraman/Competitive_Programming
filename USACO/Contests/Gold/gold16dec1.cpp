#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

int n;
vector<pair<int,int> > g[1000];

bool valid(int k)
{
    queue<int> q;
    q.push(0);
    bool v[n];
    for(int i = 0; i<n; i++){v[i]=false;}
    while(!q.empty())
    {
        int a = q.front();
        q.pop();
        v[a] = true;
        for(int i = 0; i<g[a].size(); i++)
        {
            if((g[a][i].first<=k)&&(!v[g[a][i].second]))
            {
                q.push(g[a][i].second);
                v[g[a][i].second] = true;
            }
        }
    }
    for(int i = 0; i<n; i++)
    {
        if(!v[i])
        {
            return false;
        }
    }
    return true;
}

int bsearch(int l, int g)
{
    if(l==g)
    {
        return l;
    }
    int mid = l+((g-l)/2);
    if(valid(mid))
    {
        return bsearch(l,mid);
    }
    else
    {
        return bsearch(mid+1,g);
    }
}

int main()
{
    ifstream infile("moocast.in");
    ofstream outfile("moocast.out");
    infile >> n;
    pair<int,int> p[n];
    for(int i = 0; i<n; i++)
    {
        infile >> p[i].first >> p[i].second;
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<i; j++)
        {
            g[i].push_back({(p[i].first-p[j].first)*(p[i].first-p[j].first)+(p[i].second-p[j].second)*(p[i].second-p[j].second),j});
            g[j].push_back({(p[i].first-p[j].first)*(p[i].first-p[j].first)+(p[i].second-p[j].second)*(p[i].second-p[j].second),i});
        }
    }
    outfile << bsearch(0,1250000000) << endl;
}
