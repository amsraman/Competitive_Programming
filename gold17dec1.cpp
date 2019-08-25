#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;

int bsearch(int l, int g, int k, pair<int,int> a[])
{
    if(l>=g)
    {
        return g;
    }
    int mid = (l+g)/2;
    if(a[mid].first<k)
    {
        return bsearch(mid+1,g,k,a);
    }
    if(a[mid].first>=k)
    {
        return bsearch(l,mid,k,a);
    }
}

int main()
{
    ifstream infile("piepie.in");
    ofstream outfile("piepie.out");
    int n, d;
    infile >> n >> d;
    pair<int,int> a[n], b[n], s1[2*n];
    int dis[2*n];
    for(int i = 0; i<n; i++)
    {
        dis[i] = INF;
        infile >> a[i].first >> a[i].second;
        s1[i] = {a[i].second,i};
    }
    for(int i = 0; i<n; i++)
    {
        dis[i+n] = INF;
        infile >> b[i].first >> b[i].second;
        s1[i+n] = {b[i].first,i+n};
    }
    sort(s1,s1+n);
    sort(s1+n,s1+2*n);
    pair<int,int> g[2*n];
    for(int i = 0; i<n; i++)
    {
        g[i] = {bsearch(n,2*n-1,a[i].first-d,s1),bsearch(n,2*n-1,a[i].first+1,s1)};
        if(s1[g[i].second].first>a[i].first){g[i].second--;}
        if(s1[g[i].first].first<a[i].first-d){g[i].first++;}
    }
    for(int i = 0; i<n; i++)
    {
        g[i+n] = {bsearch(0,n-1,b[i].second-d,s1),bsearch(0,n-1,b[i].second+1,s1)};
        if(s1[g[i+n].second].first>b[i].second){g[i+n].second--;}
        if(s1[g[i+n].first].first<b[i].second-d){g[i+n].first++;}
    }
    bool vis[2*n], z;
    for(int i = 0; i<2*n; i++)
    {
        if(i<n){z=(a[i].second==0);}
        else{z=(b[i-n].first==0);}
        if(z)
        {
            for(int j = 0; j<2*n; j++)
            {
                vis[j] = false;
            }
            queue<pair<int,int> > q;
            q.push({i,1});
            dis[i] = 1;
            while(!q.empty())
            {
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for(int j = g[x].first; j<=g[x].second; j++)
                {
                    if(!vis[s1[j].second])
                    {
                        vis[s1[j].second] = true;
                        dis[s1[j].second] = min(dis[s1[j].second],y+1);
                        q.push({s1[j].second,y+1});
                    }
                }
            }
        }
    }
    for(int i = 0; i<n; i++)
    {
        if(dis[i]==INF){outfile << -1 << endl;}
        else{outfile << dis[i] << endl;}
    }
}
