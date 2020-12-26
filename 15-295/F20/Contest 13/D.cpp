#include <bits/stdc++.h>

using namespace std;

int n, a[200000], ptr[200000], ans;
vector<int> g[200000], primes[200000], chains[200000];

void dfs(int x, int p)
{
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=p)
            dfs(g[x][i],x);
    for(int i = 0; i<g[x].size(); i++)
        ptr[i] = 0;
    for(auto pr: primes[x])
    {
        vector<int> pms;
        pms.push_back(0);
        for(int i = 0; i<g[x].size(); i++)
            if(g[x][i]!=p)
            {
                while(ptr[i]<primes[g[x][i]].size()&&primes[g[x][i]][ptr[i]]<pr)
                    ++ptr[i];
                if(ptr[i]<primes[g[x][i]].size()&&primes[g[x][i]][ptr[i]]==pr)
                    pms.push_back(chains[g[x][i]][ptr[i]]);
            }
        sort(pms.begin(),pms.end());
        ans = max(ans,pms.back()+1), chains[x].push_back(pms.back()+1);
        if(pms.size()>1)
            ans = max(ans,pms.back()+pms[pms.size()-2]+1);
    }
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    for(int i = 0, x, y; i<n-1; i++)
    {
        cin >> x >> y;
        g[x-1].push_back(y-1);
        g[y-1].push_back(x-1);
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 2; j*j<=a[i]; j++)
        {
            if(a[i]%j==0)
                primes[i].push_back(j);
            while(a[i]%j==0)
                a[i]/=j;
        }
        if(a[i]!=1)
            primes[i].push_back(a[i]);
    }
    dfs(0,0);
    cout << ans << endl;
}