#include <bits/stdc++.h>

using namespace std;

int n, a, b, lim;
vector<int> g[100000];

bool rem(int x, vector<int> cur)
{
    int lb = ((x!=-1)^(cur.size()%2)), ub = cur.size()-1;
    while(lb<ub)
    {
        if(lb==x) lb++;
        if(ub==x) ub--;
        if((lb<ub)&&(cur[lb]+cur[ub]<lim))
            return false;
        lb++, ub--;
    }
    return true;
}

int dfs(int x, int p)
{
    vector<int> cur;
    for(int i = 0; i<g[x].size(); i++)
        if(g[x][i]!=p)
        {
            int k = dfs(g[x][i],x);
            if(k==-1)
                return -1;
            cur.push_back(k+1);
        }
    if(!cur.size())
        return 0;
    cur.push_back(0);
    sort(cur.begin(),cur.end());
    int lb = 1, ub = cur.size()-1;
    while(lb<ub)
    {
        int mid = (lb+ub+1)/2;
        if(rem(mid,cur)) lb = mid;
        else ub = mid-1;
    }
    bool works1 = rem(-1,cur), works2 = rem(ub,cur);
    if((!works1)&&(!works2))
        return -1;
    if(((x==0)||(!works2))&&(works1))
        return 0;
    return cur[ub];
}

bool ok(int x)
{
    lim = x;
    int k = dfs(0,0);
    if((k<lim)&&(k!=0))
        return false;
    return true;
}

int main()
{
    freopen("deleg.in","r",stdin);
    freopen("deleg.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n-1; i++)
    {
        cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    int lb = 1, ub = n;
    while(lb<ub)
    {
        int mid = (lb+ub+1)/2;
        if(ok(mid)) lb = mid;
        else ub = mid-1;
    }
    cout << ub << endl;
}
